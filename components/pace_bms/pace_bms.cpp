#include "pace_bms.h"
#include "esphome/core/log.h"

namespace esphome {
namespace pace_bms {

static const char *TAG = "pace_bms";

void PaceBMS::setup() {
  ESP_LOGCONFIG(TAG, "Setting up PaceBMS...");
  // Initialization code here
}

void PaceBMS::update() {
  ESP_LOGI(TAG, "Updating PaceBMS...");

  publish_sensor_state(get_voltage(), this->voltage_sensor, "Voltage");
  publish_sensor_state(get_current(), this->current_sensor, "Current");
  publish_sensor_state(get_remaining_capacity(), this->remaining_capacity_sensor, "Remaining Capacity");
  publish_sensor_state(get_nominal_capacity(), this->nominal_capacity_sensor, "Nominal Capacity");
  publish_sensor_state(get_full_capacity(), this->full_capacity_sensor, "Full Capacity");
  publish_sensor_state(get_cycles(), this->cycles_sensor, "Cycles");
  publish_sensor_state(get_state_of_health(), this->state_of_health_sensor, "State of Health");
  publish_sensor_state(get_state_of_charge(), this->state_of_charge_sensor, "State of Charge");
  publish_sensor_state(get_cell_max_volt_diff(), this->cell_max_volt_diff_sensor, "Cell Max Volt Diff");
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

  // Read cell voltages
  for (int i = 0; i < 16; i++) {
    publish_sensor_state(get_cell_voltage(i), this->cell_voltages_sensor[i], "Cell Voltage", i);
  }

  // Read temperatures
  for (int i = 0; i < 4; i++) {
    publish_sensor_state(get_temperature(i), this->temperatures_sensor[i], "Temperature", i);
  }

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
}

void PaceBMS::publish_sensor_state(uint16_t value, sensor::Sensor *sensor, const char *sensor_name, int index) {
  if (value != 0) {
    sensor->publish_state(value);
    if (index >= 0) {
      ESP_LOGI(TAG, "%s [%d]: %d", sensor_name, index, value);
    } else {
      ESP_LOGI(TAG, "%s: %d", sensor_name, value);
    }
  } else {
    if (index >= 0) {
      ESP_LOGW(TAG, "Failed to get %s [%d]", sensor_name, index);
    } else {
      ESP_LOGW(TAG, "Failed to get %s", sensor_name);
    }
  }
}

uint16_t PaceBMS::crc16(const uint8_t *data, size_t length) {
  uint16_t crc = 0xFFFF;
  while (length--) {
    crc ^= *data++;
    for (int i = 0; i < 8; i++) {
      if (crc & 0x01) {
        crc = (crc >> 1) ^ 0xA001;
      } else {
        crc >>= 1;
      }
    }
  }
  return crc;
}

uint8_t PaceBMS::lchksum_calc(const std::string &lenid) {
  uint8_t sum = 0;
  for (char c : lenid) {
    sum += c;
  }
  return (sum % 256);
}

uint8_t PaceBMS::chksum_calc(const std::vector<uint8_t> &data) {
  uint8_t sum = 0;
  for (uint8_t byte : data) {
    sum += byte;
  }
  return (sum % 256);
}

std::vector<uint8_t> PaceBMS::build_command(uint8_t cid1, uint8_t cid2, uint8_t idx) {
  std::vector<uint8_t> command;
  command.push_back(0x7E);  // Start byte
  command.push_back(0x32);  // Version byte 1
  command.push_back(0x35);  // Version byte 2
  command.push_back(0x30);  // Address byte 1
  command.push_back(0x31);  // Address byte 2
  command.push_back(cid1);
  command.push_back(cid2);
  std::string lenid = "000";
  command.push_back(lchksum_calc(lenid));
  command.insert(command.end(), lenid.begin(), lenid.end());
  command.push_back(chksum_calc(command));
  command.push_back(0x0D);  // End byte
  return command;
}

void PaceBMS::send_command(const std::vector<uint8_t> &command) {
  for (uint8_t byte : command) {
    this->write_byte(byte);
  }
}

std::vector<uint8_t> PaceBMS::read_response() {
  std::vector<uint8_t> response;
  while (this->available()) {
    response.push_back(this->read());
  }
  return response;
}

uint16_t PaceBMS::decode_response(const std::vector<uint8_t> &response) {
  // Assume the response is correct and decode it.
  // This function needs to be adjusted according to the actual response structure.
  if (response.size() < 5) return 0;  // Example check for minimum length
  return (response[3] << 8) | response[4];  // Example decoding
}

uint16_t PaceBMS::execute_command(uint8_t cid1, uint8_t cid2, uint8_t idx) {
  std::vector<uint8_t> command = build_command(cid1, cid2, idx);
  send_command(command);
  std::vector<uint8_t> response = read_response();
  return decode_response(response);
}

// Command methods implementation
uint16_t PaceBMS::get_voltage() {
  return execute_command(0x46, 0xC1);
}

uint16_t PaceBMS::get_current() {
  return execute_command(0x46, 0xC2);
}

uint16_t PaceBMS::get_remaining_capacity() {
  return execute_command(0x46, 0xC3);
}

uint16_t PaceBMS::get_nominal_capacity() {
  return execute_command(0x46, 0xC4);
}

uint16_t PaceBMS::get_full_capacity() {
  return execute_command(0x46, 0xC5);
}

uint16_t PaceBMS::get_cycles() {
  return execute_command(0x46, 0xC6);
}

uint16_t PaceBMS::get_state_of_health() {
  return execute_command(0x46, 0xC7);
}

uint16_t PaceBMS::get_state_of_charge() {
  return execute_command(0x46, 0xC8);
}

uint16_t PaceBMS::get_cell_max_volt_diff() {
  return execute_command(0x46, 0xC9);
}

uint16_t PaceBMS::get_charge_fet() {
  return execute_command(0x46, 0xCA);
}

uint16_t PaceBMS::get_discharge_fet() {
  return execute_command(0x46, 0xCB);
}

uint16_t PaceBMS::get_ac_in() {
  return execute_command(0x46, 0xCC);
}

uint16_t PaceBMS::get_current_limit() {
  return execute_command(0x46, 0xCD);
}

uint16_t PaceBMS::get_heart() {
  return execute_command(0x46, 0xCE);
}

uint16_t PaceBMS::get_pack_indicate() {
  return execute_command(0x46, 0xCF);
}

uint16_t PaceBMS::get_protection_discharge_current() {
  return execute_command(0x46, 0xD0);
}

uint16_t PaceBMS::get_protection_charge_current() {
  return execute_command(0x46, 0xD1);
}

uint16_t PaceBMS::get_protection_short_circuit() {
  return execute_command(0x46, 0xD2);
}

uint16_t PaceBMS::get_reverse() {
  return execute_command(0x46, 0xD3);
}

uint16_t PaceBMS::get_temperature(uint8_t idx) {
  return execute_command(0x46, 0xD4, idx);
}

uint16_t PaceBMS::get_cell_voltage(uint8_t idx) {
  return execute_command(0x46, 0xD5, idx);
}

uint16_t PaceBMS::get_balancing_1() {
  return execute_command(0x46, 0xD6);
}

uint16_t PaceBMS::get_balancing_2() {
  return execute_command(0x46, 0xD7);
}

uint16_t PaceBMS::get_warnings() {
  return execute_command(0x46, 0xD8);
}

uint16_t PaceBMS::get_design_capacity() {
  return execute_command(0x46, 0xD9);
}

uint16_t PaceBMS::get_pack_full_capacity() {
  return execute_command(0x46, 0xDA);
}

uint16_t PaceBMS::get_pack_remaining_capacity() {
  return execute_command(0x46, 0xDB);
}

uint16_t PaceBMS::get_pack_state_of_health() {
  return execute_command(0x46, 0xDC);
}

uint16_t PaceBMS::get_pack_state_of_charge() {
  return execute_command(0x46, 0xDD);
}

uint16_t PaceBMS::get_pack_number() {
  return execute_command(0x46, 0xDE);
}

uint16_t PaceBMS::get_pack_analog_data() {
  return execute_command(0x46, 0xDF);
}

uint16_t PaceBMS::get_software_version() {
  return execute_command(0x46, 0xE0);
}

uint16_t PaceBMS::get_serial_number() {
  return execute_command(0x46, 0xE1);
}

uint16_t PaceBMS::get_pack_capacity() {
  return execute_command(0x46, 0xE2);
}

uint16_t PaceBMS::get_warn_info() {
  return execute_command(0x46, 0xE3);
}

}  // namespace pace_bms
}  // namespace esphome
