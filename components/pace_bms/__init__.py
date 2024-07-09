import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, uart
from esphome.const import (
    CONF_ID,
    UNIT_VOLT,
    UNIT_AMPERE,
    UNIT_MILLIAMPERE_HOUR,
    UNIT_PERCENT,
    UNIT_CELSIUS,
    ICON_FLASH,
    ICON_THERMOMETER,
    ICON_CURRENT_AC,
    ICON_BATTERY,
    ICON_BATTERY_CHARGING,
    ICON_POWER,
    UNIT_MILLIVOLT,
)

CODEOWNERS = ["@dansck"]
DEPENDENCIES = ['uart']

CONF_PACE_BMS_ID = "pace_bms_id"

pace_bms_ns = cg.esphome_ns.namespace('pace_bms')
PaceBMS = pace_bms_ns.class_('PaceBMS', cg.Component, uart.UARTDevice)

# Sensor configuration definitions
SENSORS = [
    ("voltage", UNIT_VOLT, ICON_FLASH),
    ("current", UNIT_AMPERE, ICON_FLASH),
    ("remaining_capacity", UNIT_MILLIAMPERE_HOUR, ICON_BATTERY),
    ("nominal_capacity", UNIT_MILLIAMPERE_HOUR, ICON_BATTERY),
    ("full_capacity", UNIT_MILLIAMPERE_HOUR, ICON_BATTERY),
    ("cycles", None, ICON_POWER),
    ("state_of_health", UNIT_PERCENT, ICON_BATTERY_CHARGING),
    ("state_of_charge", UNIT_PERCENT, ICON_BATTERY),
    ("cell_max_volt_diff", UNIT_MILLIVOLT, ICON_FLASH),
    ("charge_fet", None, ICON_FLASH),
    ("discharge_fet", None, ICON_FLASH),
    ("ac_in", None, ICON_CURRENT_AC),
    ("current_limit", None, ICON_POWER),
    ("heart", None, ICON_HEART),
    ("pack_indicate", None, ICON_POWER),
    ("protection_discharge_current", None, ICON_FLASH),
    ("protection_charge_current", None, ICON_FLASH),
    ("protection_short_circuit", None, ICON_FLASH),
    ("reverse", None, ICON_FLASH),
    ("temperature", UNIT_CELSIUS, ICON_THERMOMETER),
    ("cell_1_voltage", UNIT_VOLT, ICON_FLASH),
    ("cell_2_voltage", UNIT_VOLT, ICON_FLASH),
    ("cell_3_voltage", UNIT_VOLT, ICON_FLASH),
    ("cell_4_voltage", UNIT_VOLT, ICON_FLASH),
    ("cell_5_voltage", UNIT_VOLT, ICON_FLASH),
    ("cell_6_voltage", UNIT_VOLT, ICON_FLASH),
    ("cell_7_voltage", UNIT_VOLT, ICON_FLASH),
    ("cell_8_voltage", UNIT_VOLT, ICON_FLASH),
    ("cell_9_voltage", UNIT_VOLT, ICON_FLASH),
    ("cell_10_voltage", UNIT_VOLT, ICON_FLASH),
    ("cell_11_voltage", UNIT_VOLT, ICON_FLASH),
    ("cell_12_voltage", UNIT_VOLT, ICON_FLASH),
    ("cell_13_voltage", UNIT_VOLT, ICON_FLASH),
    ("cell_14_voltage", UNIT_VOLT, ICON_FLASH),
    ("cell_15_voltage", UNIT_VOLT, ICON_FLASH),
    ("temperature_1", UNIT_CELSIUS, ICON_THERMOMETER),
    ("temperature_2", UNIT_CELSIUS, ICON_THERMOMETER),
    ("temperature_3", UNIT_CELSIUS, ICON_THERMOMETER),
    ("temperature_4", UNIT_CELSIUS, ICON_THERMOMETER),
    ("temperature_5", UNIT_CELSIUS, ICON_THERMOMETER),
    ("temperature_6", UNIT_CELSIUS, ICON_THERMOMETER),
    ("balancing_1", None, ICON_FLASH),
    ("balancing_2", None, ICON_FLASH),
    ("warnings", None, ICON_FLASH),
    ("design_capacity", UNIT_MILLIAMPERE_HOUR, ICON_BATTERY),
    ("pack_full_capacity", UNIT_MILLIAMPERE_HOUR, ICON_BATTERY),
    ("pack_remaining_capacity", UNIT_MILLIAMPERE_HOUR, ICON_BATTERY),
    ("pack_state_of_health", UNIT_PERCENT, ICON_BATTERY_CHARGING),
    ("pack_state_of_charge", UNIT_PERCENT, ICON_BATTERY),
]

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(PaceBMS),
    **{
        cv.Optional(sensor[0]): sensor.sensor_schema(
            unit_of_measurement=sensor[1],
            icon=sensor[2]
        ) for sensor in SENSORS
    }
}).extend(cv.COMPONENT_SCHEMA).extend(uart.UART_DEVICE_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

    for sensor_name, unit, icon in SENSORS:
        if sensor_name in config:
            sens = await sensor.new_sensor(config[sensor_name])
            cg.add(getattr(var, f'set_{sensor_name}_sensor')(sens))
