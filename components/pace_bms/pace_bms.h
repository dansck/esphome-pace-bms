#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome {
namespace pace_bms {

class PaceBMS : public Component, public UARTDevice {
 public:
  void setup() override;
  void update() override;

  sensor::Sensor *voltage_sensor{nullptr};
  sensor::Sensor *current_sensor{nullptr};
  sensor::Sensor *remaining_capacity_sensor{nullptr};
  sensor::Sensor *nominal_capacity_sensor{nullptr};
  sensor::Sensor *full_capacity_sensor{nullptr};
  sensor::Sensor *cycles_sensor{nullptr};
  sensor::Sensor *state_of_health_sensor{nullptr};
  sensor::Sensor *state_of_charge_sensor{nullptr};
  sensor::Sensor *cell_max_volt_diff_sensor{nullptr};
  sensor::Sensor *charge_fet_sensor{nullptr};
  sensor::Sensor *discharge_fet_sensor{nullptr};
  sensor::Sensor *ac_in_sensor{nullptr};
  sensor::Sensor *current_limit_sensor{nullptr};
  sensor::Sensor *heart_sensor{nullptr};
  sensor::Sensor *pack_indicate_sensor{nullptr};
  sensor::Sensor *protection_discharge_current_sensor{nullptr};
  sensor::Sensor *protection_charge_current_sensor{nullptr};
  sensor::Sensor *protection_short_circuit_sensor{nullptr};
  sensor::Sensor *reverse_sensor{nullptr};
  sensor::Sensor *temperature_sensor{nullptr};
  std::array<sensor::Sensor *, 16> cell_voltages_sensor{};
  std::array<sensor::Sensor *, 4> temperatures_sensor{};
  sensor::Sensor *balancing_1_sensor{nullptr};
  sensor::Sensor *balancing_2_sensor{nullptr};
  sensor::Sensor *warnings_sensor{nullptr};
  sensor::Sensor *design_capacity_sensor{nullptr};
  sensor::Sensor *pack_full_capacity_sensor{nullptr};
  sensor::Sensor *pack_remaining_capacity_sensor{nullptr};
  sensor::Sensor *pack_state_of_health_sensor{nullptr};
  sensor::Sensor *pack_state_of_charge_sensor{nullptr};
  sensor::Sensor *pack_number_sensor{nullptr};
  sensor::Sensor *pack_analog_data_sensor{nullptr};
  sensor::Sensor *software_version_sensor{nullptr};
  sensor::Sensor *serial_number_sensor{nullptr};
  sensor::Sensor *pack_capacity_sensor{nullptr};
  sensor::Sensor *warn_info_sensor{nullptr};

 protected:
  void publish_sensor_state(uint16_t value, sensor::Sensor *sensor, const char *sensor_name, int index = -1);
  uint16_t crc16(const uint8_t *data, size_t length);
  uint8_t lchksum_calc(const std::string &lenid);
  uint8_t chksum_calc(const std::vector<uint8_t> &data);
  void send_command(const std::vector<uint8_t> &command);
  std::vector<uint8_t> read_response();
  uint16_t decode_response(const std::vector<uint8_t> &response);
  std::vector<uint8_t> build_command(uint8_t cid1, uint8_t cid2, uint8_t idx = 0x00);
  uint16_t execute_command(uint8_t cid1, uint8_t cid2, uint8_t idx = 0x00);

  // Command methods
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
  uint16_t get_temperature(uint8_t idx);
  uint16_t get_cell_voltage(uint8_t idx);
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
