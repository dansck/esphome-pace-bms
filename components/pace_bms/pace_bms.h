#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"
#include <vector>
#include <string>

namespace esphome {
namespace pace_bms {

class PaceBMS : public PollingComponent, public uart::UARTDevice {
 public:
  void setup() override;
  void update() override;

  // Declare all sensors
  sensor::Sensor *voltage_sensor = new sensor::Sensor();
  sensor::Sensor *current_sensor = new sensor::Sensor();
  sensor::Sensor *remaining_capacity_sensor = new sensor::Sensor();
  sensor::Sensor *nominal_capacity_sensor = new sensor::Sensor();
  sensor::Sensor *full_capacity_sensor = new sensor::Sensor();
  sensor::Sensor *cycles_sensor = new sensor::Sensor();
  sensor::Sensor *state_of_health_sensor = new sensor::Sensor();
  sensor::Sensor *state_of_charge_sensor = new sensor::Sensor();
  sensor::Sensor *cell_max_volt_diff_sensor = new sensor::Sensor();
  sensor::Sensor *charge_fet_sensor = new sensor::Sensor();
  sensor::Sensor *discharge_fet_sensor = new sensor::Sensor();
  sensor::Sensor *ac_in_sensor = new sensor::Sensor();
  sensor::Sensor *current_limit_sensor = new sensor::Sensor();
  sensor::Sensor *heart_sensor = new sensor::Sensor();
  sensor::Sensor *pack_indicate_sensor = new sensor::Sensor();
  sensor::Sensor *protection_discharge_current_sensor = new sensor::Sensor();
  sensor::Sensor *protection_charge_current_sensor = new sensor::Sensor();
  sensor::Sensor *protection_short_circuit_sensor = new sensor::Sensor();
  sensor::Sensor *reverse_sensor = new sensor::Sensor();
  sensor::Sensor *temperature_sensor = new sensor::Sensor();
  sensor::Sensor *cell_voltages_sensor = new sensor::Sensor();
  sensor::Sensor *temperatures_sensor = new sensor::Sensor();
  sensor::Sensor *balancing_1_sensor = new sensor::Sensor();
  sensor::Sensor *balancing_2_sensor = new sensor::Sensor();
  sensor::Sensor *warnings_sensor = new sensor::Sensor();
  sensor::Sensor *design_capacity_sensor = new sensor::Sensor();
  sensor::Sensor *pack_full_capacity_sensor = new sensor::Sensor();
  sensor::Sensor *pack_remaining_capacity_sensor = new sensor::Sensor();
  sensor::Sensor *pack_state_of_health_sensor = new sensor::Sensor();
  sensor::Sensor *pack_state_of_charge_sensor = new sensor::Sensor();
  sensor::Sensor *pack_number_sensor = new sensor::Sensor();
  sensor::Sensor *pack_analog_data_sensor = new sensor::Sensor();
  sensor::Sensor *software_version_sensor = new sensor::Sensor();
  sensor::Sensor *serial_number_sensor = new sensor::Sensor();
  sensor::Sensor *pack_capacity_sensor = new sensor::Sensor();
  sensor::Sensor *warn_info_sensor = new sensor::Sensor();

 protected:
  std::pair<bool, std::vector<uint8_t>> bms_request(const uint8_t *ver, const uint8_t *adr, const uint8_t *cid1, const uint8_t *cid2, const std::vector<uint8_t> &info);
  
  uint16_t crc16(const uint8_t *data, size_t length);
  uint8_t lchksum_calc(const std::string &lenid);
  uint8_t chksum_calc(const std::vector<uint8_t> &data);
  void send_command(const uint8_t *command, size_t length);
  std::vector<uint8_t> read_response();
  uint16_t decode_response(const std::vector<uint8_t> &response);

  // Methods to retrieve sensor data
  uint16_t get_voltage();
  uint16_t get_current();
  uint16_t get_remaining_capacity();
  uint16_t get_nominal_capacity();
  uint16_t get_full_capacity();
  uint16_t get_cycles();
  uint16_t get_state_of_health();
  uint16_t get_state_of_charge();
  uint16_t get_cell_max_volt_diff();
  uint16_t get_charge_fet();
  uint16_t get_discharge_fet();
  uint16_t get_ac_in();
  uint16_t get_current_limit();
  uint16_t get_heart();
  uint16_t get_pack_indicate();
  uint16_t get_protection_discharge_current();
  uint16_t get_protection_charge_current();
  uint16_t get_protection_short_circuit();
  uint16_t get_reverse();
  uint16_t get_temperature();
  uint16_t get_cell_voltages();
  uint16_t get_temperatures();
  uint16_t get_balancing_1();
  uint16_t get_balancing_2();
  uint16_t get_warnings();
  uint16_t get_design_capacity();
  uint16_t get_pack_full_capacity();
  uint16_t get_pack_remaining_capacity();
  uint16_t get_pack_state_of_health();
  uint16_t get_pack_state_of_charge();
  uint16_t get_pack_number();
  uint16_t get_pack_analog_data();
  uint16_t get_software_version();
  uint16_t get_serial_number();
  uint16_t get_pack_capacity();
  uint16_t get_warn_info();
};

}  // namespace pace_bms
}  // namespace esphome
