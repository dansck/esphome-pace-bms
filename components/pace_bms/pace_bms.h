#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/uart/uart.h"

namespace esphome
{
  namespace pace_bms
  {

    class PaceBMS : public PollingComponent, public uart::UARTDevice
    {
    public:
      void setup() override;
      void loop() override;

      void set_voltage_sensor(sensor::Sensor *voltage_sensor) { voltage_sensor_ = voltage_sensor; }
      void set_current_sensor(sensor::Sensor *current_sensor) { current_sensor_ = current_sensor; }
      void set_temperature_sensor(sensor::Sensor *temperature_sensor) { temperature_sensor_ = temperature_sensor; }

    protected:
      sensor::Sensor *voltage_sensor_{nullptr};
      sensor::Sensor *current_sensor_{nullptr};
      sensor::Sensor *temperature_sensor_{nullptr};

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
