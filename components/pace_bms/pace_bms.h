#include "esphome.h"

namespace esphome
{
  namespace pace_bms
  {

    class PaceBms : public PollingComponent
    {
    public:
      Sensor *voltage_sensor = nullptr;
      Sensor *current_sensor = nullptr;
      Sensor *temperature_sensor = nullptr;

      void set_voltage_sensor(Sensor *voltage_sensor) { this->voltage_sensor = voltage_sensor; }
      void set_current_sensor(Sensor *current_sensor) { this->current_sensor = current_sensor; }
      void set_temperature_sensor(Sensor *temperature_sensor) { this->temperature_sensor = temperature_sensor; }

      void update() override
      {
        // Read from Modbus and update sensors
      }
    };

  } // namespace pace_bms
} // namespace esphome
