#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/uart/uart.h"
#include <map>
#include <vector>

namespace esphome {
  namespace pace_bms {

    class PaceBMS : public PollingComponent, public uart::UARTDevice {
    public:
      void setup() override;
      void update() override;

      void set_voltage_sensor(sensor::Sensor *voltage_sensor) { voltage_sensor_ = voltage_sensor; }
      void set_current_sensor(sensor::Sensor *current_sensor) { current_sensor_ = current_sensor; }
      void set_temperature_sensor(sensor::Sensor *temperature_sensor) { temperature_sensor_ = temperature_sensor; }

      void set_remaining_capacity_sensor(sensor::Sensor *sensor) { remaining_capacity_sensor_ = sensor; }
      void set_nominal_capacity_sensor(sensor::Sensor *sensor) { nominal_capacity_sensor_ = sensor; }
      void set_full_capacity_sensor(sensor::Sensor *sensor) { full_capacity_sensor_ = sensor; }
      void set_cycles_sensor(sensor::Sensor *sensor) { cycles_sensor_ = sensor; }
      void set_state_of_health_sensor(sensor::Sensor *sensor) { state_of_health_sensor_ = sensor; }
      void set_state_of_charge_sensor(sensor::Sensor *sensor) { state_of_charge_sensor_ = sensor; }
      void set_cell_max_volt_diff_sensor(sensor::Sensor *sensor) { cell_max_volt_diff_sensor_ = sensor; }
      void set_charge_fet_sensor(sensor::Sensor *sensor) { charge_fet_sensor_ = sensor; }
      void set_discharge_fet_sensor(sensor::Sensor *sensor) { discharge_fet_sensor_ = sensor; }
      void set_ac_in_sensor(sensor::Sensor *sensor) { ac_in_sensor_ = sensor; }
      void set_current_limit_sensor(sensor::Sensor *sensor) { current_limit_sensor_ = sensor; }
      void set_heart_sensor(sensor::Sensor *sensor) { heart_sensor_ = sensor; }
      void set_pack_indicate_sensor(sensor::Sensor *sensor) { pack_indicate_sensor_ = sensor; }
      void set_protection_discharge_current_sensor(sensor::Sensor *sensor) { protection_discharge_current_sensor_ = sensor; }
      void set_protection_charge_current_sensor(sensor::Sensor *sensor) { protection_charge_current_sensor_ = sensor; }
      void set_protection_short_circuit_sensor(sensor::Sensor *sensor) { protection_short_circuit_sensor_ = sensor; }
      void set_reverse_sensor(sensor::Sensor *sensor) { reverse_sensor_ = sensor; }

      void set_cell_voltage_sensors(const std::vector<sensor::Sensor *> &sensors) { cell_voltage_sensors_ = sensors; }
      void set_temperature_sensors(const std::vector<sensor::Sensor *> &sensors) { temperature_sensors_ = sensors; }

      void set_balancing_1_sensor(sensor::Sensor *sensor) { balancing_1_sensor_ = sensor; }
      void set_balancing_2_sensor(sensor::Sensor *sensor) { balancing_2_sensor_ = sensor; }
      void set_warnings_sensor(sensor::Sensor *sensor) { warnings_sensor_ = sensor; }
      void set_design_capacity_sensor(sensor::Sensor *sensor) { design_capacity_sensor_ = sensor; }
      void set_pack_full_capacity_sensor(sensor::Sensor *sensor) { pack_full_capacity_sensor_ = sensor; }
      void set_pack_remaining_capacity_sensor(sensor::Sensor *sensor) { pack_remaining_capacity_sensor_ = sensor; }
      void set_pack_state_of_health_sensor(sensor::Sensor *sensor) { pack_state_of_health_sensor_ = sensor; }
      void set_pack_state_of_charge_sensor(sensor::Sensor *sensor) { pack_state_of_charge_sensor_ = sensor; }

    protected:
      sensor::Sensor *voltage_sensor_{nullptr};
      sensor::Sensor *current_sensor_{nullptr};
      sensor::Sensor *temperature_sensor_{nullptr};
      sensor::Sensor *remaining_capacity_sensor_{nullptr};
      sensor::Sensor *nominal_capacity_sensor_{nullptr};
      sensor::Sensor *full_capacity_sensor_{nullptr};
      sensor::Sensor *cycles_sensor_{nullptr};
      sensor::Sensor *state_of_health_sensor_{nullptr};
      sensor::Sensor *state_of_charge_sensor_{nullptr};
      sensor::Sensor *cell_max_volt_diff_sensor_{nullptr};
      sensor::Sensor *charge_fet_sensor_{nullptr};
      sensor::Sensor *discharge_fet_sensor_{nullptr};
      sensor::Sensor *ac_in_sensor_{nullptr};
      sensor::Sensor *current_limit_sensor_{nullptr};
      sensor::Sensor *heart_sensor_{nullptr};
      sensor::Sensor *pack_indicate_sensor_{nullptr};
      sensor::Sensor *protection_discharge_current_sensor_{nullptr};
      sensor::Sensor *protection_charge_current_sensor_{nullptr};
      sensor::Sensor *protection_short_circuit_sensor_{nullptr};
      sensor::Sensor *reverse_sensor_{nullptr};
      std::vector<sensor::Sensor *> cell_voltage_sensors_;
      std::vector<sensor::Sensor *> temperature_sensors_;
      sensor::Sensor *balancing_1_sensor_{nullptr};
      sensor::Sensor *balancing_2_sensor_{nullptr};
      sensor::Sensor *warnings_sensor_{nullptr};
      sensor::Sensor *design_capacity_sensor_{nullptr};
      sensor::Sensor *pack_full_capacity_sensor_{nullptr};
      sensor::Sensor *pack_remaining_capacity_sensor_{nullptr};
      sensor::Sensor *pack_state_of_health_sensor_{nullptr};
      sensor::Sensor *pack_state_of_charge_sensor_{nullptr};

      void read_bms_data_();
      void decode_response_(const std::vector<uint8_t> &data);
      std::map<std::string, float> decode_basic_info_(const std::vector<uint8_t> &data);
      std::vector<float> decode_cell_voltage_(const std::vector<uint8_t> &data);
      float decode_cell_max_volt_diff_(const std::vector<uint8_t> &data);
      std::vector<float> decode_temperature_(const std::vector<uint8_t> &data);
      std::map<std::string, float> decode_mosfet_status_(const std::vector<uint8_t> &data);
      std::map<std::string, float> decode_status_(const std::vector<uint8_t> &data);
      void publish_state_(sensor::Sensor *sensor, float value);
    };

  } // namespace pace_bms
} // namespace esphome
