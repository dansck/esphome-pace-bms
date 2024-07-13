#include "pace_bms.h"
#include "esphome/core/log.h"

namespace esphome {
namespace pace_bms {

static const char *TAG = "pace_bms";

void PaceBMS::setup() {
  ESP_LOGCONFIG(TAG, "Setting up Pace BMS...");
}

void PaceBMS::update() {
  publish_sensor_state(get_voltage(), this->voltage_sensor, "Voltage");
  publish_sensor_state(get_current(), this->current_sensor, "Current");
  publish_sensor_state(get_remaining_capacity(), this->remaining_capacity_sensor, "Remaining Capacity");
  publish_sensor_state(get_nominal_capacity(), this->nominal_capacity_sensor, "Nominal Capacity");
  publish_sensor_state(get_full_capacity(), this->full_capacity_sensor, "Full Capacity");
  publish_sensor_state(get_cycles(), this->cycles_sensor, "Cycles");
  publish_sensor_state(get_state_of_health(), this->state_of_health_sensor, "State of Health");
  publish_sensor_state(get_state_of_charge(), this->state_of_charge_sensor, "State of Charge");
  publish_sensor_state(get_cell_max_volt_diff(), this->cell_max_volt_diff_sensor, "Cell Max Voltage Difference");
  publish_sensor_state(get_charge_fet(), this->charge_fet_sensor, "Charge FET");
  publish_sensor_state(get_discharge_fet(), this->discharge_fet_sensor, "Discharge FET");
  publish_sensor_state(get_ac_in(), this->ac_in_sensor, "AC In");
  publish_sensor_state(get_current_limit(), this->current_limit_sensor, "Current Limit");
  publish_sensor_state(get_heart(), this->heart_sensor, "Heart");
  publish_sensor_state(get_pack_indicate(), this->pack_indicate_sensor, "Pack Indicate");
  publish_sensor_state(get_protection_discharge_current(), this->protection_discharge_current_sensor, "Protection Discharge Current");
  publish_sensor_state(get_protection_charge_current(), this->protection_charge_current_sensor, "Protection Charge Current");
  publish_sensor_state(get_protection_short_circuit(), this->protection_short_circuit_sensor, "Protection Short Circuit");
  publish_sensor_state(get_reverse(), this->reverse_sensor, "Reverse");
  publish_sensor_state(get_balancing_1(), this->balancing_1_sensor, "Balancing 1");
  publish_sensor_state(get_balancing_2(), this->balancing_2_sensor, "Balancing 2");
  publish_sensor_state(get_warnings(), this->warnings_sensor, "Warnings");
  publish_sensor_state(get_design_capacity(), this->design_capacity_sensor, "Design Capacity");
  publish_sensor_state(get_pack_full_capacity(), this->pack_full_capacity_sensor, "Pack Full Capacity");
  publish_sensor_state(get_pack_remaining_capacity(), this->pack_remaining_capacity_sensor, "Pack Remaining Capacity");
  publish_sensor_state(get_pack_state_of_health(), this->pack_state_of_health_sensor, "Pack State of Health");
  publish_sensor_state(get_pack_state_of_charge(), this->pack_state_of_charge_sensor, "Pack State of Charge");
  publish_sensor_state(get_pack_number(), this->pack_number_sensor, "Pack Number");
  publish_sensor_state(get_pack_analog_data(), this->pack_analog_data_sensor, "Pack Analog Data");
  publish_sensor_state(get_software_version(), this->software_version_sensor, "Software Version");
  publish_sensor_state(get_serial_number(), this->serial_number_sensor, "Serial Number");
  publish_sensor_state(get_pack_capacity(), this->pack_capacity_sensor, "Pack Capacity");
  publish_sensor_state(get_warn_info(), this->warn_info_sensor, "Warn Info");

  for (size_t i = 0; i < this->cell_voltages_sensors.size(); i++) {
    publish_sensor_state(get_cell_voltage(i), this->cell_voltages_sensors[i], "Cell Voltage", i);
  }
  for (size_t i = 0; i < this->temperatures_sensors.size(); i++) {
    publish_sensor_state(get_temperature(i), this->temperatures_sensors[i], "Temperature", i);
  }
}

void PaceBMS::send_command(const std::vector<unsigned char> &command) {
  for (auto byte : command) {
    this->write_byte(byte);
  }
}

std::vector<unsigned char> PaceBMS::read_response() {
  std::vector<unsigned char> response;
  while (this->available()) {
    response.push_back(this->read());
  }
  return response;
}

void PaceBMS::publish_sensor_state(uint16_t value, sensor::Sensor *sensor, const char *sensor_name, int index) {
  if (sensor != nullptr) {
    sensor->publish_state(value);
  } else {
    if (index >= 0) {
      ESP_LOGW(TAG, "Sensor %s for index %d not set", sensor_name, index);
    } else {
      ESP_LOGW(TAG, "Sensor %s not set", sensor_name);
    }
  }
}

uint16_t PaceBMS::execute_command(uint8_t cid1, uint8_t cid2, uint8_t idx) {
  std::vector<unsigned char> command = {0xDD, 0xA5, cid1, cid2, idx, 0x00, 0xFF, 0xFD, 0x77};
  this->send_command(command);
  std::vector<unsigned char> response = this->read_response();
  if (response.size() < 5) {
    ESP_LOGW(TAG, "Invalid response size: %d", response.size());
    return 0;
  }
  return (response[3] << 8) | response[4];
}

uint16_t PaceBMS::get_voltage() { return execute_command(0x03, 0x00); }
uint16_t PaceBMS::get_current() { return execute_command(0x04, 0x00); }
uint16_t PaceBMS::get_remaining_capacity() { return execute_command(0x05, 0x00); }
uint16_t PaceBMS::get_nominal_capacity() { return execute_command(0x06, 0x00); }
uint16_t PaceBMS::get_full_capacity() { return execute_command(0x07, 0x00); }
uint16_t PaceBMS::get_cycles() { return execute_command(0x08, 0x00); }
uint16_t PaceBMS::get_state_of_health() { return execute_command(0x09, 0x00); }
uint16_t PaceBMS::get_state_of_charge() { return execute_command(0x0A, 0x00); }
uint16_t PaceBMS::get_cell_max_volt_diff() { return execute_command(0x0B, 0x00); }
uint16_t PaceBMS::get_charge_fet() { return execute_command(0x0C, 0x00); }
uint16_t PaceBMS::get_discharge_fet() { return execute_command(0x0D, 0x00); }
uint16_t PaceBMS::get_ac_in() { return execute_command(0x0E, 0x00); }
uint16_t PaceBMS::get_current_limit() { return execute_command(0x0F, 0x00); }
uint16_t PaceBMS::get_heart() { return execute_command(0x10, 0x00); }
uint16_t PaceBMS::get_pack_indicate() { return execute_command(0x11, 0x00); }
uint16_t PaceBMS::get_protection_discharge_current() { return execute_command(0x12, 0x00); }
uint16_t PaceBMS::get_protection_charge_current() { return execute_command(0x13, 0x00); }
uint16_t PaceBMS::get_protection_short_circuit() { return execute_command(0x14, 0x00); }
uint16_t PaceBMS::get_reverse() { return execute_command(0x15, 0x00); }
uint16_t PaceBMS::get_temperature(uint8_t idx) { return execute_command(0x16, 0x00, idx); }
uint16_t PaceBMS::get_cell_voltage(uint8_t idx) { return execute_command(0x17, 0x00, idx); }
uint16_t PaceBMS::get_balancing_1() { return execute_command(0x18, 0x00); }
uint16_t PaceBMS::get_balancing_2() { return execute_command(0x19, 0x00); }
uint16_t PaceBMS::get_warnings() { return execute_command(0x1A, 0x00); }
uint16_t PaceBMS::get_design_capacity() { return execute_command(0x1B, 0x00); }
uint16_t PaceBMS::get_pack_full_capacity() { return execute_command(0x1C, 0x00); }
uint16_t PaceBMS::get_pack_remaining_capacity() { return execute_command(0x1D, 0x00); }
uint16_t PaceBMS::get_pack_state_of_health() { return execute_command(0x1E, 0x00); }
uint16_t PaceBMS::get_pack_state_of_charge() { return execute_command(0x1F, 0x00); }
uint16_t PaceBMS::get_pack_number() { return execute_command(0x20, 0x00); }
uint16_t PaceBMS::get_pack_analog_data() { return execute_command(0x21, 0x00); }
uint16_t PaceBMS::get_software_version() { return execute_command(0x22, 0x00); }
uint16_t PaceBMS::get_serial_number() { return execute_command(0x23, 0x00); }
uint16_t PaceBMS::get_pack_capacity() { return execute_command(0x24, 0x00); }
uint16_t PaceBMS::get_warn_info() { return execute_command(0x25, 0x00); }

void PaceBMS::add_cell_voltage_sensors(const std::vector<sensor::Sensor *> &sensors) {
  for (auto *sensor : sensors) {
    this->add_cell_voltage_sensor(sensor);
  }
}
void PaceBMS::add_cell_voltage_sensor(sensor::Sensor *sensor) {
  cell_voltages_sensors.push_back(sensor);
}

void PaceBMS::add_temperature_sensors(const std::vector<sensor::Sensor *> &sensors) {
  for (auto *sensor : sensors) {
    this->add_temperature_sensor(sensor);
  }
}
void PaceBMS::add_temperature_sensor(sensor::Sensor *sensor) {
  temperatures_sensors.push_back(sensor);
}

}  // namespace pace_bms
}  // namespace esphome
