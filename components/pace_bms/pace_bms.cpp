#include "pace_bms.h"
#include "esphome/core/log.h"

namespace esphome
{
  namespace pace_bms
  {

    static const char *TAG = "pace_bms";

    void PaceBMS::setup()
    {
      // Setup timer for regular data reading
      this->last_read_time = millis();
    }

    void PaceBMS::loop()
    {
      const uint32_t now = millis();
      // Read data from BMS every 5 seconds
      if (now - this->last_read_time >= 5000)
      {
        this->last_read_time = now;
        this->read_bms_data();
      }
    }

    void PaceBMS::read_bms_data()
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
        this->decode_response(response);
      }
      else
      {
        ESP_LOGW(TAG, "No response from BMS");
      }
    }

    void PaceBMS::decode_response(const std::vector<uint8_t> &data)
    {
      if (data.size() < 5)
      {
        ESP_LOGW(TAG, "Received data is too short");
        return;
      }

      // Decode basic information
      auto basic_info = this->decode_basic_info(data);
      this->publish_state(this->voltage_sensor_, basic_info["voltage"]);
      this->publish_state(this->current_sensor_, basic_info["current"]);
      this->publish_state(this->remaining_capacity_sensor_, basic_info["remaining_capacity"]);
      this->publish_state(this->nominal_capacity_sensor_, basic_info["nominal_capacity"]);
      this->publish_state(this->full_capacity_sensor_, basic_info["full_capacity"]);
      this->publish_state(this->cycles_sensor_, basic_info["cycles"]);
      this->publish_state(this->state_of_health_sensor_, basic_info["state_of_health"]);
      this->publish_state(this->state_of_charge_sensor_, basic_info["state_of_charge"]);

      // Decode cell voltages
      auto cell_voltages = this->decode_cell_voltage(data);
      for (size_t i = 0; i < cell_voltages.size(); i++)
      {
        this->publish_state(this->cell_voltage_sensors_[i], cell_voltages[i]);
      }

      // Decode max cell voltage difference
      float max_volt_diff = this->decode_cell_max_volt_diff(data);
      this->publish_state(this->cell_max_volt_diff_sensor_, max_volt_diff);

      // Decode temperatures
      auto temperatures = this->decode_temperature(data);
      for (size_t i = 0; i < temperatures.size(); i++)
      {
        this->publish_state(this->temperature_sensors_[i], temperatures[i]);
      }

      // Decode MOSFET status
      auto mosfet_status = this->decode_mosfet_status(data);
      this->publish_state(this->charge_fet_sensor_, mosfet_status["charge_fet"]);
      this->publish_state(this->discharge_fet_sensor_, mosfet_status["discharge_fet"]);

      // Decode protection and functional status
      auto status = this->decode_status(data);
      this->publish_state(this->ac_in_sensor_, status["ac_in"]);
      this->publish_state(this->current_limit_sensor_, status["current_limit"]);
      this->publish_state(this->heart_sensor_, status["heart"]);
      this->publish_state(this->pack_indicate_sensor_, status["pack_indicate"]);
      this->publish_state(this->protection_discharge_current_sensor_, status["protection_discharge_current"]);
      this->publish_state(this->protection_charge_current_sensor_, status["protection_charge_current"]);
      this->publish_state(this->protection_short_circuit_sensor_, status["protection_short_circuit"]);
      this->publish_state(this->reverse_sensor_, status["reverse"]);
    }

    std::map<std::string, float> PaceBMS::decode_basic_info(const std::vector<uint8_t> &data)
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

    std::vector<float> PaceBMS::decode_cell_voltage(const std::vector<uint8_t> &data)
    {
      std::vector<float> cell_voltages;
      for (int i = 0; i < 17; i++)
      {
        float voltage = ((data[4 + i * 2] << 8) | data[5 + i * 2]) / 1000.0; // Voltage in V
        cell_voltages.push_back(voltage);
      }
      return cell_voltages;
    }

    float PaceBMS::decode_cell_max_volt_diff(const std::vector<uint8_t> &data)
    {
      return ((data[4] << 8) | data[5]) / 1000.0; // Voltage difference in mV
    }

    std::vector<float> PaceBMS::decode_temperature(const std::vector<uint8_t> &data)
    {
      std::vector<float> temperatures;
      for (int i = 0; i < 6; i++)
      {
        float temp = ((data[30 + i * 2] << 8) | data[31 + i * 2]) / 10.0; // Temperature in °C
        temperatures.push_back(temp);
      }
      return temperatures;
    }

    std::map<std::string, float> PaceBMS::decode_mosfet_status(const std::vector<uint8_t> &data)
    {
      std::map<std::string, float> result;
      result["charge_fet"] = data[24] & 0x01;    // Charge FET status
      result["discharge_fet"] = data[24] & 0x02; // Discharge FET status
      return result;
    }

    std::map<std::string, float> PaceBMS::decode_status(const std::vector<uint8_t> &data)
    {
      std::map<std::string, float> result;
      result["ac_in"] = data[25];                        // AC In status
      result["current_limit"] = data[26];                // Current limit
      result["heart"] = data[27];                        // Heart status
      result["pack_indicate"] = data[28];                // Pack Indicate status
      result["protection_discharge_current"] = data[29]; // Protection discharge current
      result["protection_charge_current"] = data[30];    // Protection charge current
      result["protection_short_circuit"] = data[31];     // Short circuit protection
      result["reverse"] = data[32];                      // Reverse polarity protection
      return result;
    }

    void PaceBMS::publish_state(Sensor *sensor, float value)
    {
      if (sensor != nullptr)
      {
        sensor->publish_state(value);
      }
    }

  } // namespace pace_bms
} // namespace esphome
