#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"
#include <vector>

namespace esphome {
namespace pace_bms {

class PaceBMS : public Component, public uart::UARTDevice {
 public:
  PaceBMS(uart::UARTComponent *parent) : uart::UARTDevice(parent) {}

  // Initialize the sensors
  void set_voltage_sensor(sensor::Sensor *voltage_sensor) { this->voltage_sensor_ = voltage_sensor; }
  void set_current_sensor(sensor::Sensor *current_sensor) { this->current_sensor_ = current_sensor; }
  void set_remaining_capacity_sensor(sensor::Sensor *remaining_capacity_sensor) { this->remaining_capacity_sensor_ = remaining_capacity_sensor; }
  void set_nominal_capacity_sensor(sensor::Sensor *nominal_capacity_sensor) { this->nominal_capacity_sensor_ = nominal_capacity_sensor; }
  void set_full_capacity_sensor(sensor::Sensor *full_capacity_sensor) { this->full_capacity_sensor_ = full_capacity_sensor; }
  void set_cycles_sensor(sensor::Sensor *cycles_sensor) { this->cycles_sensor_ = cycles_sensor; }
  void set_state_of_health_sensor(sensor::Sensor *state_of_health_sensor) { this->state_of_health_sensor_ = state_of_health_sensor; }
  void set_state_of_charge_sensor(sensor::Sensor *state_of_charge_sensor) { this->state_of_charge_sensor_ = state_of_charge_sensor; }
  void set_cell_max_volt_diff_sensor(sensor::Sensor *cell_max_volt_diff_sensor) { this->cell_max_volt_diff_sensor_ = cell_max_volt_diff_sensor; }
  void set_charge_fet_sensor(sensor::Sensor *charge_fet_sensor) { this->charge_fet_sensor_ = charge_fet_sensor; }
  void set_discharge_fet_sensor(sensor::Sensor *discharge_fet_sensor) { this->discharge_fet_sensor_ = discharge_fet_sensor; }
  void set_balancing1_sensor(sensor::Sensor *balancing1_sensor) { this->balancing1_sensor_ = balancing1_sensor; }
  void set_balancing2_sensor(sensor::Sensor *balancing2_sensor) { this->balancing2_sensor_ = balancing2_sensor; }
  void set_ac_in_sensor(sensor::Sensor *ac_in_sensor) { this->ac_in_sensor_ = ac_in_sensor; }
  void set_current_limit_sensor(sensor::Sensor *current_limit_sensor) { this->current_limit_sensor_ = current_limit_sensor; }
  void set_heart_sensor(sensor::Sensor *heart_sensor) { this->heart_sensor_ = heart_sensor; }
  void set_pack_indicate_sensor(sensor::Sensor *pack_indicate_sensor) { this->pack_indicate_sensor_ = pack_indicate_sensor; }
  void set_protection_discharge_current_sensor(sensor::Sensor *protection_discharge_current_sensor) { this->protection_discharge_current_sensor_ = protection_discharge_current_sensor; }
  void set_protection_charge_current_sensor(sensor::Sensor *protection_charge_current_sensor) { this->protection_charge_current_sensor_ = protection_charge_current_sensor; }
  void set_protection_short_circuit_sensor(sensor::Sensor *protection_short_circuit_sensor) { this->protection_short_circuit_sensor_ = protection_short_circuit_sensor; }
  void set_reverse_sensor(sensor::Sensor *reverse_sensor) { this->reverse_sensor_ = reverse_sensor; }

  void set_cell_voltage_sensor(int index, sensor::Sensor *cell_voltage_sensor) {
    if (index >= cell_voltage_sensors_.size()) {
      cell_voltage_sensors_.resize(index + 1);
    }
    cell_voltage_sensors_[index] = cell_voltage_sensor;
  }

  void set_temperature_sensor(int index, sensor::Sensor *temperature_sensor) {
    if (index >= temperature_sensors_.size()) {
      temperature_sensors_.resize(index + 1);
    }
    temperature_sensors_[index] = temperature_sensor;
  }

  void setup() override {
    // Initialization code
  }

  void loop() override {
    // Main logic code to read from the BMS and update sensors
  }

  void dump_config() override {
    // Optional function to dump component configuration
  }

  void update() override {
    // Called periodically according to the update interval
  }

 protected:
  sensor::Sensor *voltage_sensor_;
  sensor::Sensor *current_sensor_;
  sensor::Sensor *remaining_capacity_sensor_;
  sensor::Sensor *nominal_capacity_sensor_;
  sensor::Sensor *full_capacity_sensor_;
  sensor::Sensor *cycles_sensor_;
  sensor::Sensor *state_of_health_sensor_;
  sensor::Sensor *state_of_charge_sensor_;
  sensor::Sensor *cell_max_volt_diff_sensor_;
  sensor::Sensor *charge_fet_sensor_;
  sensor::Sensor *discharge_fet_sensor_;
  sensor::Sensor *balancing1_sensor_;
  sensor::Sensor *balancing2_sensor_;
  sensor::Sensor *ac_in_sensor_;
  sensor::Sensor *current_limit_sensor_;
  sensor::Sensor *heart_sensor_;
  sensor::Sensor *pack_indicate_sensor_;
  sensor::Sensor *protection_discharge_current_sensor_;
  sensor::Sensor *protection_charge_current_sensor_;
  sensor::Sensor *protection_short_circuit_sensor_;
  sensor::Sensor *reverse_sensor_;

  std::vector<sensor::Sensor *> cell_voltage_sensors_;
  std::vector<sensor::Sensor *> temperature_sensors_;
};

}  // namespace pace_bms
}  // namespace esphome
