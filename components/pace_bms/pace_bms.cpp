#include "pace_bms.h"
#include "esphome/core/log.h"
#include <map>
#include <vector>

namespace esphome
{
  namespace pace_bms
  {

    static const char *TAG = "pace_bms";

    void PaceBMS::setup()
    {
      // Setup timer for regular data reading
      this->set_timeout(5000, [this]()
                        { this->read_bms_data_(); });
    }

    void PaceBMS::update()
    {
      this->read_bms_data_();
    }

    void PaceBMS::read_bms_data_()
    {
      // Create and send the request to read data
      std::vector<uint8_t> request = {0x10, 0x02, 0xF0, 0x0D}; // Request may differ depending on BMS
      this->write_array(request);
      this->flush(); // Clear the buffer for reading the response

      std::vector<uint8_t> response(256);
      size_t len = this->read_array(response.data(), response.size());

      if (len > 0)
      {
        // Process the response
        this->decode_response_(response);
      }
      else
      {
        ESP_LOGW(TAG, "No response from BMS");
      }
    }

    void PaceBMS::decode_response_(const std::vector<uint8_t> &data)
    {
      if (data.size() < 5)
      {
        ESP_LOGW(TAG, "Received data is too short");
        return;
      }

      // Decode basic information
      auto basic_info = this->decode_basic_info_(data);
      this->publish_state_(this->voltage_sensor_, basic_info["voltage"]);
      this->publish_state_(this->current_sensor_, basic_info["current"]);
      this->publish_state_(this->remaining_capacity_sensor_, basic_info["remaining_capacity"]);
      this->publish_state_(this->nominal_capacity_sensor_, basic_info["nominal_capacity"]);
      this->publish_state_(this->full_capacity_sensor_, basic_info["full_capacity"]);
      this->publish_state_(this->cycles_sensor_, basic_info["cycles"]);
      this->publish_state_(this->state_of_health_sensor_, basic_info["state_of_health"]);
      this->publish_state_(this->state_of_charge_sensor_, basic_info["state_of_charge"]);

      // Decode cell voltages
      auto cell_voltages = this->decode_cell_voltage_(data);
      for (size_t i = 0; i < cell_voltages.size(); i++)
      {
        this->publish_state_(this->cell_voltage_sensors_[i], cell_voltages[i]);
      }

      // Decode max cell voltage difference
      float max_volt_diff = this->decode_cell_max_volt_diff_(data);
      this->publish_state_(this->cell_max_volt_diff_sensor_, max_volt_diff);

      // Decode temperatures
      auto temperatures = this->decode_temperature_(data);
      for (size_t i = 0; i < temperatures.size(); i++)
      {
        this->publish_state_(this->temperature_sensors_[i], temperatures[i]);
      }

      // Decode MOSFET status
      auto mosfet_status = this->decode_mosfet_status_(data);
      this->publish_state_(this->charge_fet_sensor_, mosfet_status["charge_fet"]);
      this->publish_state_(this->discharge_fet_sensor_, mosfet_status["discharge_fet"]);

      // Decode protection and functional status
      auto status = this->decode_status_(data);
      this->publish_state_(this->ac_in_sensor_, status["ac_in"]);
      this->publish_state_(this->current_limit_sensor_, status["current_limit"]);
      this->publish_state_(this->heart_sensor_, status["heart"]);
      this->publish_state_(this->pack_indicate_sensor_, status["pack_indicate"]);
      this->publish_state_(this->protection_discharge_current_sensor_, status["protection_discharge_current"]);
      this->publish_state_(this->protection_charge_current_sensor_, status["protection_charge_current"]);
      this->publish_state_(this->protection_short_circuit_sensor_, status["protection_short_circuit"]);
      this->publish_state_(this->reverse_sensor_, status["reverse"]);

      // Decode additional sensors
      this->publish_state_(this->balancing_1_sensor_, status["balancing_1"]);
      this->publish_state_(this->balancing_2_sensor_, status["balancing_2"]);
      this->publish_state_(this->warnings_sensor_, status["warnings"]);
      this->publish_state_(this->design_capacity_sensor_, status["design_capacity"]);
      this->publish_state_(this->pack_full_capacity_sensor_, status["pack_full_capacity"]);
      this->publish_state_(this->pack_remaining_capacity_sensor_, status["pack_remaining_capacity"]);
      this->publish_state_(this->pack_state_of_health_sensor_, status["pack_state_of_health"]);
      this->publish_state_(this->pack_state_of_charge_sensor_, status["pack_state_of_charge"]);
      
      // nove sensory
      this->publish_state_(this->pack_number_sensor_, status["pack_number"]);
      this->publish_state_(this->pack_analog_data_sensor_, status["pack_analog_data"]);
      this->publish_state_(this->software_version_sensor_, status["software_version"]);
      this->publish_state_(this->serial_number_sensor_, status["serial_number"]);
      this->publish_state_(this->pack_capacity_sensor_, status["pack_capacity"]);
      this->publish_state_(this->warn_info_sensor_, status["warn_info"]);
}
    }

    std::map<std::string, float> PaceBMS::decode_basic_info_(const std::vector<uint8_t> &data)
    {
      std::map<std::string, float> result;
      result["voltage"] = ((data[4] << 8) | data[5]) / 100.0;           // Voltage in V
      result["current"] = ((data[6] << 8) | data[7]) / 10.0;            // Current in A
      result["remaining_capacity"] = ((data[8] << 8) | data[9]);        // Remaining capacity in mAh
      result["nominal_capacity"] = ((data[10] << 8) | data[11]);        // Nominal capacity in mAh
      result["full_capacity"] = ((data[14] << 8) | data[15]);           // Full capacity in mAh
      result["cycles"] = ((data[12] << 8) | data[13]);                  // Cycle count
      result["state_of_health"] = data[16];                             // State of health in percent
      result["state_of_charge"] = ((data[17] << 8) | data[18]) / 100.0; // State of charge in percent
      return result;
    }

    std::vector<float> PaceBMS::decode_cell_voltage_(const std::vector<uint8_t> &data)
    {
      std::vector<float> cell_voltages;
      for (int i = 0; i < 15; i++)
      {                                                                      // Adjusted to match 15 cells
        float voltage = ((data[4 + i * 2] << 8) | data[5 + i * 2]) / 1000.0; // Voltage in V
        cell_voltages.push_back(voltage);
      }
      return cell_voltages;
    }

    float PaceBMS::decode_cell_max_volt_diff_(const std::vector<uint8_t> &data)
    {
      return ((data[34] << 8) | data[35]) / 1000.0; // Voltage difference in mV
    }

    std::vector<float> PaceBMS::decode_temperature_(const std::vector<uint8_t> &data)
    {
      std::vector<float> temperatures;
      for (int i = 0; i < 6; i++)
      {
        float temp = ((data[36 + i * 2] << 8) | data[37 + i * 2]) / 10.0; // Temperature in °C
        temperatures.push_back(temp);
      }
      return temperatures;
    }

    std::map<std::string, float> PaceBMS::decode_mosfet_status_(const std::vector<uint8_t> &data)
    {
      std::map<std::string, float> result;
      result["charge_fet"] = data[48] & 0x01;    // Charge FET status
      result["discharge_fet"] = data[48] & 0x02; // Discharge FET status
      return result;
    }

    std::map<std::string, float> PaceBMS::decode_status_(const std::vector<uint8_t> &data)
    {
      std::map<std::string, float> result;
      result["ac_in"] = data[49];                        // AC In status
      result["current_limit"] = data[50];                // Current limit
      result["heart"] = data[51];                        // Heart status
      result["pack_indicate"] = data[52];                // Pack Indicate status
      result["protection_discharge_current"] = data[53]; // Protection discharge current
      result["protection_charge_current"] = data[54];    // Protection charge current
      result["protection_short_circuit"] = data[55];     // Short circuit protection
      result["reverse"] = data[56];                      // Reverse polarity protection
      result["balancing_1"] = data[57];                  // Balancing 1 status
      result["balancing_2"] = data[58];                  // Balancing 2 status
      result["warnings"] = data[59];                     // Warnings
      result["design_capacity"] = data[60];              // Design capacity
      result["pack_full_capacity"] = data[61];           // Pack full capacity
      result["pack_remaining_capacity"] = data[62];      // Pack remaining capacity
      result["pack_state_of_health"] = data[63];         // Pack state of health
      result["pack_state_of_charge"] = data[64];         // Pack state of charge
      return result;
    }

    void PaceBMS::publish_state_(sensor::Sensor *sensor, float value)
    {
      if (sensor != nullptr)
      {
        sensor->publish_state(value);
      }
    }

  } // namespace pace_bms
} // namespace esphome
