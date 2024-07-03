#include "pace_bms.h"
#include "esphome/core/log.h"

namespace esphome {
namespace pace_bms {

static const char *TAG = "pace_bms";

void PaceBMS::setup() {
  // Nastavení časovače pro pravidelné čtení dat
  this->last_read_time = millis();
}

void PaceBMS::loop() {
  const uint32_t now = millis();
  // Čtení dat z BMS každých 5 sekund
  if (now - this->last_read_time >= 5000) {
    this->last_read_time = now;
    this->read_bms_data();
  }
}

void PaceBMS::read_bms_data() {
  // Vytvoření a odeslání požadavku na čtení dat
  std::vector<uint8_t> request = {0x10, 0x02, 0xF0, 0x0D}; // Požadavek může být odlišný v závislosti na BMS
  this->write_array(request);
  this->flush(); // Vyprázdnění bufferu pro čtení odpovědi

  std::vector<uint8_t> response(256);
  size_t len = this->read_array(response.data(), response.size());

  if (len > 0) {
    // Zpracování odpovědi
    this->decode_response(response);
  } else {
    ESP_LOGW(TAG, "No response from BMS");
  }
}

void PaceBMS::decode_response(const std::vector<uint8_t> &data) {
  if (data.size() < 5) {
    ESP_LOGW(TAG, "Received data is too short");
    return;
  }

  // Dekódování základních informací
  auto basic_info = this->decode_basic_info(data);
  this->publish_state(this->voltage_sensor_, basic_info["voltage"]);
  this->publish_state(this->current_sensor_, basic_info["current"]);
  this->publish_state(this->remaining_capacity_sensor_, basic_info["remaining_capacity"]);
  this->publish_state(this->nominal_capacity_sensor_, basic_info["nominal_capacity"]);
  this->publish_state(this->full_capacity_sensor_, basic_info["full_capacity"]);
  this->publish_state(this->cycles_sensor_, basic_info["cycles"]);
  this->publish_state(this->state_of_health_sensor_, basic_info["state_of_health"]);
  this->publish_state(this->state_of_charge_sensor_, basic_info["state_of_charge"]);

  // Dekódování napětí článků
  auto cell_voltages = this->decode_cell_voltage(data);
  for (size_t i = 0; i < cell_voltages.size(); i++) {
    this->publish_state(this->cell_voltage_sensors_[i], cell_voltages[i]);
  }

  // Dekódování maximálního rozdílu napětí článků
  float max_volt_diff = this->decode_cell_max_volt_diff(data);
  this->publish_state(this->cell_max_volt_diff_sensor_, max_volt_diff);

  // Dekódování teplot
  auto temperatures = this->decode_temperature(data);
  for (size_t i = 0; i < temperatures.size(); i++) {
    this->publish_state(this->temperature_sensors_[i], temperatures[i]);
  }

  // Dekódování stavu MOSFETů
  auto mosfet_status = this->decode_mosfet_status(data);
  this->publish_state(this->charge_fet_sensor_, mosfet_status["charge_fet"]);
  this->publish_state(this->discharge_fet_sensor_, mosfet_status["discharge_fet"]);

  // Dekódování stavu ochranných a funkčních parametrů
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

std::map<std::string, float> PaceBMS::decode_basic_info(const std::vector<uint8_t> &data) {
  std::map<std::string, float> result;
  result["voltage"] = ((data[4] << 8) | data[5]) / 100.0;  // Napětí v V
  result["current"] = ((data[6] << 8) | data[7]) / 10.0;  // Proud v A
  result["remaining_capacity"] = ((data[8] << 8) | data[9]);  // Zbývající kapacita v mAh
  result["nominal_capacity"] = ((data[10] << 8) | data[11]);  // Nominální kapacita v mAh
  result["full_capacity"] = ((data[14] << 8) | data[15]);  // Plná kapacita v mAh
  result["cycles"] = ((data[12] << 8) | data[13]);  // Počet cyklů
  result["state_of_health"] = data[16];  // Stav zdraví v procentech
  result["state_of_charge"] = ((data[17] << 8) | data[18]) / 100.0;  // Stav nabití v procentech
  return result;
}

std::vector<float> PaceBMS::decode_cell_voltage(const std::vector<uint8_t> &data) {
  std::vector<float> cell_voltages;
  for (int i = 0; i < 17; i++) {
    float voltage = ((data[4 + i * 2] << 8) | data[5 + i * 2]) / 1000.0;  // Napětí v V
    cell_voltages.push_back(voltage);
  }
  return cell_voltages;
}

float PaceBMS::decode_cell_max_volt_diff(const std::vector<uint8_t> &data) {
  return ((data[4] << 8) | data[5]) / 1000.0;  // Rozdíl napětí v mV
}

std::vector<float> PaceBMS::decode_temperature(const std::vector<uint8_t> &data) {
  std::vector<float> temperatures;
  for (int i = 0; i < 6; i++) {
    float temp = ((data[30 + i * 2] << 8) | data[31 + i * 2]) / 10.0;  // Teplota ve °C
    temperatures.push_back(temp);
  }
  return temperatures;
}

std::map<std::string, float> PaceBMS::decode_mosfet_status(const std::vector<uint8_t> &data) {
  std::map<std::string, float> result;
  result["charge_fet"] = data[24] & 0x01;  // Stav charge FET
  result["discharge_fet"] = data[24] & 0x02;  // Stav discharge FET
  return result;
}

std::map<std::string, float> PaceBMS::decode_status(const std::vector<uint8_t> &data) {
  std::map<std::string, float> result;
  result["ac_in"] = data[25];  // Stav AC In
  result["current_limit"] = data[26];  // Aktuální limit
  result["heart"] = data[27];  // Stav Heart
  result["pack_indicate"] = data[28];  // Stav Pack Indicate
  result["protection_discharge_current"] = data[29];  // Ochrana před výbojovým proudem
  result["protection_charge_current"] = data[30];  // Ochrana před nabíjecím proudem
  result["protection_short_circuit"] = data[31];  // Ochrana proti zkratu
  result["reverse"] = data[32];  // Ochrana proti obrácení polarity
  return result;
}

void PaceBMS::publish_state(Sensor *sensor, float value) {
  if (sensor != nullptr) {
    sensor->publish_state(value);
  }
}

}  // namespace pace_bms
}  // namespace esphome
