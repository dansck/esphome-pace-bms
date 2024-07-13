#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome {
namespace pace_bms {

class PaceBMS : public PollingComponent, public uart::UARTDevice {
 public:
  void setup() override;
  void update() override;
  void add_cell_voltage_sensors(const std::vector<sensor::Sensor *> &sensors);
  void add_temperature_sensors(const std::vector<sensor::Sensor *> &sensors); 
  void add_cell_voltage_sensor(sensor::Sensor *sensor);
  void add_temperature_sensor(sensor::Sensor *sensor);
  
  void set_voltage_sensor(sensor::Sensor *sensor) { voltage_sensor = sensor; }
  void set_current_sensor(sensor::Sensor *sensor) { current_sensor = sensor; }
  void set_remaining_capacity_sensor(sensor::Sensor *sensor) { remaining_capacity_sensor = sensor; }
  void set_nominal_capacity_sensor(sensor::Sensor *sensor) { nominal_capacity_sensor = sensor; }
  void set_full_capacity_sensor(sensor::Sensor *sensor) { full_capacity_sensor = sensor; }
  void set_cycles_sensor(sensor::Sensor *sensor) { cycles_sensor = sensor; }
  void set_state_of_health_sensor(sensor::Sensor *sensor) { state_of_health_sensor = sensor; }
  void set_state_of_charge_sensor(sensor::Sensor *sensor) { state_of_charge_sensor = sensor; }
  void set_cell_max_volt_diff_sensor(sensor::Sensor *sensor) { cell_max_volt_diff_sensor = sensor; }
  void set_charge_fet_sensor(sensor::Sensor *sensor) { charge_fet_sensor = sensor; }
  void set_discharge_fet_sensor(sensor::Sensor *sensor) { discharge_fet_sensor = sensor; }
  void set_ac_in_sensor(sensor::Sensor *sensor) { ac_in_sensor = sensor; }
  void set_current_limit_sensor(sensor::Sensor *sensor) { current_limit_sensor = sensor; }
  void set_heart_sensor(sensor::Sensor *sensor) { heart_sensor = sensor; }
  void set_pack_indicate_sensor(sensor::Sensor *sensor) { pack_indicate_sensor = sensor; }
  void set_protection_discharge_current_sensor(sensor::Sensor *sensor) { protection_discharge_current_sensor = sensor; }
  void set_protection_charge_current_sensor(sensor::Sensor *sensor) { protection_charge_current_sensor = sensor; }
  void set_protection_short_circuit_sensor(sensor::Sensor *sensor) { protection_short_circuit_sensor = sensor; }
  void set_reverse_sensor(sensor::Sensor *sensor) { reverse_sensor = sensor; }
  void set_balancing_1_sensor(sensor::Sensor *sensor) { balancing_1_sensor = sensor; }
  void set_balancing_2_sensor(sensor::Sensor *sensor) { balancing_2_sensor = sensor; }
  void set_warnings_sensor(sensor::Sensor *sensor) { warnings_sensor = sensor; }
  void set_design_capacity_sensor(sensor::Sensor *sensor) { design_capacity_sensor = sensor; }
  void set_pack_full_capacity_sensor(sensor::Sensor *sensor) { pack_full_capacity_sensor = sensor; }
  void set_pack_remaining_capacity_sensor(sensor::Sensor *sensor) { pack_remaining_capacity_sensor = sensor; }
  void set_pack_state_of_health_sensor(sensor::Sensor *sensor) { pack_state_of_health_sensor = sensor; }
  void set_pack_state_of_charge_sensor(sensor::Sensor *sensor) { pack_state_of_charge_sensor = sensor; }
  void set_pack_number_sensor(sensor::Sensor *sensor) { pack_number_sensor = sensor; }
  void set_pack_analog_data_sensor(sensor::Sensor *sensor) { pack_analog_data_sensor = sensor; }
  void set_software_version_sensor(sensor::Sensor *sensor) { software_version_sensor = sensor; }
  void set_serial_number_sensor(sensor::Sensor *sensor) { serial_number_sensor = sensor; }
  void set_pack_capacity_sensor(sensor::Sensor *sensor) { pack_capacity_sensor = sensor; }
  void set_warn_info_sensor(sensor::Sensor *sensor) { warn_info_sensor = sensor; }

 protected:
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
  std::vector<sensor::Sensor *> cell_voltages_sensors;
  std::vector<sensor::Sensor *> temperatures_sensors;

  void send_command(const std::vector<unsigned char> &command);
  std::vector<unsigned char> read_response();
  void publish_sensor_state(uint16_t value, sensor::Sensor *sensor, const char *sensor_name, int index = -1);

  uint16_t execute_command(uint8_t cid1, uint8_t cid2, uint8_t idx = 0x00);
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
