#include "pace_bms.h"
#include "esphome/core/log.h"

namespace esphome {
namespace pace_bms {

static const char *TAG = "pace_bms";

void PaceBMS::update() {
  ESP_LOGD(TAG, "Updating Pace BMS...");

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
    publish_sensor_state(get_cell_voltage(i + 1), this->cell_voltages_sensors[i], "Cell Voltage", i + 1);
  }

  for (size_t i = 0; i < this->temperatures_sensors.size(); i++) {
    publish_sensor_state(get_temperature(i + 1), this->temperatures_sensors[i], "Temperature", i + 1);
  }
}

void PaceBMS::publish_sensor_state(uint16_t value, sensor::Sensor *sensor, const char *sensor_name, int index) {
  if (sensor != nullptr) {
    ESP_LOGD(TAG, "Publishing %s%s: %d", sensor_name, (index >= 0) ? std::to_string(index).c_str() : "", value);
    sensor->publish_state(value);
  }
}

uint16_t PaceBMS::execute_command(uint8_t cid1, uint8_t cid2, uint8_t idx) {
  std::vector<unsigned char> command = {0x7e, 0x32, 0x35, 0x30, 0x31, cid1, cid2, 0x00, 0x30, 0x30, 0x30};

  if (idx != 0) {
    command[10] = 0x30 + idx;
  }

  uint16_t checksum = 0;
  for (size_t i = 1; i < command.size(); i++) {
    checksum += command[i];
  }
  command.push_back((checksum >> 8) & 0xFF);
  command.push_back(checksum & 0xFF);
  command.push_back(0x0d);

  send_command(command);
  auto response = read_response();

  if (response.size() > 8) {
    return (response[7] << 8) | response[8];
  }

  return 0;
}

uint16_t PaceBMS::get_voltage() {
  return execute_command(0x34, 0x56);
}

uint16_t PaceBMS::get_current() {
  return execute_command(0x34, 0x57);
}

uint16_t PaceBMS::get_remaining_capacity() {
  return execute_command(0x34, 0x58);
}

uint16_t PaceBMS::get_nominal_capacity() {
  return execute_command(0x34, 0x59);
}

uint16_t PaceBMS::get_full_capacity() {
  return execute_command(0x34, 0x5A);
}

uint16_t PaceBMS::get_cycles() {
  return execute_command(0x34, 0x5B);
}

uint16_t PaceBMS::get_state_of_health() {
  return execute_command(0x34, 0x5C);
}

uint16_t PaceBMS::get_state_of_charge() {
  return execute_command(0x34, 0x5D);
}

uint16_t PaceBMS::get_cell_max_volt_diff() {
  return execute_command(0x34, 0x5E);
}

uint16_t PaceBMS::get_charge_fet() {
  return execute_command(0x34, 0x5F);
}

uint16_t PaceBMS::get_discharge_fet() {
  return execute_command(0x34, 0x60);
}

uint16_t PaceBMS::get_ac_in() {
  return execute_command(0x34, 0x61);
}

uint16_t PaceBMS::get_current_limit() {
  return execute_command(0x34, 0x62);
}

uint16_t PaceBMS::get_heart() {
  return execute_command(0x34, 0x63);
}

uint16_t PaceBMS::get_pack_indicate() {
  return execute_command(0x34, 0x64);
}

uint16_t PaceBMS::get_protection_discharge_current() {
  return execute_command(0x34, 0x65);
}

uint16_t PaceBMS::get_protection_charge_current() {
  return execute_command(0x34, 0x66);
}

uint16_t PaceBMS::get_protection_short_circuit() {
  return execute_command(0x34, 0x67);
}

uint16_t PaceBMS::get_reverse() {
  return execute_command(0x34, 0x68);
}

uint16_t PaceBMS::get_temperature(uint8_t idx) {
  return execute_command(0x34, 0x69, idx);
}

uint16_t PaceBMS::get_cell_voltage(uint8_t idx) {
  return execute_command(0x34, 0x6A, idx);
}

uint16_t PaceBMS::get_balancing_1() {
  return execute_command(0x34, 0x6B);
}

uint16_t PaceBMS::get_balancing_2() {
  return execute_command(0x34, 0x6C);
}

uint16_t PaceBMS::get_warnings() {
  return execute_command(0x34, 0x6D);
}

uint16_t PaceBMS::get_design_capacity() {
  return execute_command(0x34, 0x6E);
}

uint16_t PaceBMS::get_pack_full_capacity() {
  return execute_command(0x34, 0x6F);
}

uint16_t PaceBMS::get_pack_remaining_capacity() {
  return execute_command(0x34, 0x70);
}

uint16_t PaceBMS::get_pack_state_of_health() {
  return execute_command(0x34, 0x71);
}

uint16_t PaceBMS::get_pack_state_of_charge() {
  return execute_command(0x34, 0x72);
}

uint16_t PaceBMS::get_pack_number() {
  return execute_command(0x34, 0x73);
}

uint16_t PaceBMS::get_pack_analog_data() {
  return execute_command(0x34, 0x74);
}

uint16_t PaceBMS::get_software_version() {
  return execute_command(0x34, 0x75);
}

uint16_t PaceBMS::get_serial_number() {
  return execute_command(0x34, 0x76);
}

uint16_t PaceBMS::get_pack_capacity() {
  return execute_command(0x34, 0x77);
}

uint16_t PaceBMS::get_warn_info() {
  return execute_command(0x34, 0x78);
}

}  // namespace pace_bms
}  // namespace esphome
