import esphome.codegen as cg
from esphome.components import sensor
import esphome.config_validation as cv
from esphome.const import ( CONF_ID, 
    DEVICE_CLASS_VOLTAGE,
    ICON_EMPTY,
    UNIT_VOLTS,
    CONF_RESOLUTION,
    DEVICE_CLASS_TEMPERATURE,
    STATE_CLASS_MEASUREMENT,
    UNIT_CELSIUS,
)

from . import CONF_PACE_BMS_ID, PaceBMS

DEPENDENCIES = ["pace_bms"]


CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_PACE_BMS_ID): cv.use_id(PaceBMS),
        cv.Optional('voltage_sensor'): sensor.sensor_schema(
            unit_of_measurement=UNIT_VOLTS,
            icon=ICON_EMPTY,
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_VOLTAGE,
        ),
        cv.Optional('current_sensor'): sensor.sensor_schema(),
        cv.Optional('remaining_capacity_sensor'): sensor.sensor_schema(),
        cv.Optional('nominal_capacity_sensor'): sensor.sensor_schema(),
        cv.Optional('full_capacity_sensor'): sensor.sensor_schema(),
        cv.Optional('cycles_sensor'): sensor.sensor_schema(),
        cv.Optional('state_of_health_sensor'): sensor.sensor_schema(),
        cv.Optional('state_of_charge_sensor'): sensor.sensor_schema(),
        cv.Optional('cell_max_volt_diff_sensor'): sensor.sensor_schema(),
        cv.Optional('charge_fet_sensor'): sensor.sensor_schema(),
        cv.Optional('discharge_fet_sensor'): sensor.sensor_schema(),
        cv.Optional('balancing1_sensor'): sensor.sensor_schema(),
        cv.Optional('balancing2_sensor'): sensor.sensor_schema(),
        cv.Optional('ac_in_sensor'): sensor.sensor_schema(),
        cv.Optional('current_limit_sensor'): sensor.sensor_schema(),
        cv.Optional('heart_sensor'): sensor.sensor_schema(),
        cv.Optional('pack_indicate_sensor'): sensor.sensor_schema(),
        cv.Optional('protection_discharge_current_sensor'): sensor.sensor_schema(),
        cv.Optional('protection_charge_current_sensor'): sensor.sensor_schema(),
        cv.Optional('protection_short_circuit_sensor'): sensor.sensor_schema(),
        cv.Optional('reverse_sensor'): sensor.sensor_schema(),

        cv.Optional('cell_voltage_sensor_1'): sensor.sensor_schema(),
        cv.Optional('cell_voltage_sensor_2'): sensor.sensor_schema(),
        cv.Optional('cell_voltage_sensor_3'): sensor.sensor_schema(),
        cv.Optional('cell_voltage_sensor_4'): sensor.sensor_schema(),
        cv.Optional('cell_voltage_sensor_5'): sensor.sensor_schema(),
        cv.Optional('cell_voltage_sensor_6'): sensor.sensor_schema(),
        cv.Optional('cell_voltage_sensor_7'): sensor.sensor_schema(),
        cv.Optional('cell_voltage_sensor_8'): sensor.sensor_schema(),
        cv.Optional('cell_voltage_sensor_9'): sensor.sensor_schema(),
        cv.Optional('cell_voltage_sensor_10'): sensor.sensor_schema(),
        cv.Optional('cell_voltage_sensor_11'): sensor.sensor_schema(),
        cv.Optional('cell_voltage_sensor_12'): sensor.sensor_schema(),
        cv.Optional('cell_voltage_sensor_13'): sensor.sensor_schema(),
        cv.Optional('cell_voltage_sensor_14'): sensor.sensor_schema(),
        cv.Optional('cell_voltage_sensor_15'): sensor.sensor_schema(),
        cv.Optional('cell_voltage_sensor_16'): sensor.sensor_schema(),
        cv.Optional('cell_voltage_sensor_17'): sensor.sensor_schema(),

        cv.Optional('temperature_sensor_1'): sensor.sensor_schema(),
        cv.Optional('temperature_sensor_2'): sensor.sensor_schema(),
        cv.Optional('temperature_sensor_3'): sensor.sensor_schema(),
        cv.Optional('temperature_sensor_4'): sensor.sensor_schema(),
        cv.Optional('temperature_sensor_5'): sensor.sensor_schema(),
        cv.Optional('temperature_sensor_6'): sensor.sensor_schema(),
    }
)


async def to_code(config):
    hub = await cg.get_variable(config[CONF_SOLAX_METER_GATEWAY_ID])
    if CONF_POWER_DEMAND in config:
        sens = await sensor.new_sensor(config[CONF_POWER_DEMAND])
        cg.add(hub.set_power_demand_sensor(sens))