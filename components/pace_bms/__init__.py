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

SENSORS = [
    "voltage", "current", "remaining_capacity", "nominal_capacity",
    "full_capacity", "cycles", "state_of_health", "state_of_charge",
    "cell_max_volt_diff", "charge_fet", "discharge_fet", "ac_in",
    "current_limit", "heart", "pack_indicate", "protection_discharge_current",
    "protection_charge_current", "protection_short_circuit", "reverse",
    "temperature", "cell_1_voltage", "cell_2_voltage", "cell_3_voltage",
    "cell_4_voltage", "cell_5_voltage", "cell_6_voltage", "cell_7_voltage",
    "cell_8_voltage", "cell_9_voltage", "cell_10_voltage", "cell_11_voltage",
    "cell_12_voltage", "cell_13_voltage", "cell_14_voltage", "cell_15_voltage",
    "temperature_1", "temperature_2", "temperature_3", "temperature_4",
    "temperature_5", "temperature_6", "balancing_1", "balancing_2", "warnings",
    "design_capacity", "pack_full_capacity", "pack_remaining_capacity",
    "pack_state_of_health", "pack_state_of_charge"
]

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(PaceBMS),
    **{cv.Optional(sensor): sensor.sensor_schema() for sensor in SENSORS}
}).extend(cv.COMPONENT_SCHEMA).extend(uart.UART_DEVICE_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

    for sensor_name in SENSORS:
        if sensor_name in config:
            sens = await sensor.new_sensor(config[sensor_name])
            cg.add(getattr(var, f'set_{sensor_name}_sensor')(sens))
