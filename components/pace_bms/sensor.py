import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import CONF_ID

from . import pace_bms_ns, PaceBMS

CONF_VOLTAGE = "voltage"
CONF_CURRENT = "current"
CONF_REMAINING_CAPACITY = "remaining_capacity"
CONF_NOMINAL_CAPACITY = "nominal_capacity"
CONF_FULL_CAPACITY = "full_capacity"
CONF_CYCLES = "cycles"
CONF_STATE_OF_HEALTH = "state_of_health"
CONF_STATE_OF_CHARGE = "state_of_charge"
CONF_CELL_MAX_VOLT_DIFF = "cell_max_volt_diff"
CONF_CHARGE_FET = "charge_fet"
CONF_DISCHARGE_FET = "discharge_fet"
CONF_AC_IN = "ac_in"
CONF_CURRENT_LIMIT = "current_limit"
CONF_HEART = "heart"
CONF_PACK_INDICATE = "pack_indicate"
CONF_PROTECTION_DISCHARGE_CURRENT = "protection_discharge_current"
CONF_PROTECTION_CHARGE_CURRENT = "protection_charge_current"
CONF_PROTECTION_SHORT_CIRCUIT = "protection_short_circuit"
CONF_REVERSE = "reverse"
CONF_TEMPERATURE = "temperature"
CONF_CELL_1_VOLTAGE = "cell_1_voltage"
CONF_CELL_2_VOLTAGE = "cell_2_voltage"
CONF_CELL_3_VOLTAGE = "cell_3_voltage"
CONF_CELL_4_VOLTAGE = "cell_4_voltage"
CONF_CELL_5_VOLTAGE = "cell_5_voltage"
CONF_CELL_6_VOLTAGE = "cell_6_voltage"
CONF_CELL_7_VOLTAGE = "cell_7_voltage"
CONF_CELL_8_VOLTAGE = "cell_8_voltage"
CONF_CELL_9_VOLTAGE = "cell_9_voltage"
CONF_CELL_10_VOLTAGE = "cell_10_voltage"
CONF_CELL_11_VOLTAGE = "cell_11_voltage"
CONF_CELL_12_VOLTAGE = "cell_12_voltage"
CONF_CELL_13_VOLTAGE = "cell_13_voltage"
CONF_CELL_14_VOLTAGE = "cell_14_voltage"
CONF_CELL_15_VOLTAGE = "cell_15_voltage"
CONF_TEMPERATURE_1 = "temperature_1"
CONF_TEMPERATURE_2 = "temperature_2"
CONF_TEMPERATURE_3 = "temperature_3"
CONF_TEMPERATURE_4 = "temperature_4"
CONF_TEMPERATURE_5 = "temperature_5"
CONF_TEMPERATURE_6 = "temperature_6"
CONF_BALANCING_1 = "balancing_1"
CONF_BALANCING_2 = "balancing_2"
CONF_WARNINGS = "warnings"
CONF_DESIGN_CAPACITY = "design_capacity"
CONF_PACK_FULL_CAPACITY = "pack_full_capacity"
CONF_PACK_REMAINING_CAPACITY = "pack_remaining_capacity"
CONF_PACK_STATE_OF_HEALTH = "pack_state_of_health"
CONF_PACK_STATE_OF_CHARGE = "pack_state_of_charge"

SENSOR_SCHEMA = sensor.sensor_schema()

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(CONF_ID): cv.use_id(PaceBMS),
    cv.Optional(CONF_VOLTAGE): SENSOR_SCHEMA,
    cv.Optional(CONF_CURRENT): SENSOR_SCHEMA,
    cv.Optional(CONF_REMAINING_CAPACITY): SENSOR_SCHEMA,
    cv.Optional(CONF_NOMINAL_CAPACITY): SENSOR_SCHEMA,
    cv.Optional(CONF_FULL_CAPACITY): SENSOR_SCHEMA,
    cv.Optional(CONF_CYCLES): SENSOR_SCHEMA,
    cv.Optional(CONF_STATE_OF_HEALTH): SENSOR_SCHEMA,
    cv.Optional(CONF_STATE_OF_CHARGE): SENSOR_SCHEMA,
    cv.Optional(CONF_CELL_MAX_VOLT_DIFF): SENSOR_SCHEMA,
    cv.Optional(CONF_CHARGE_FET): SENSOR_SCHEMA,
    cv.Optional(CONF_DISCHARGE_FET): SENSOR_SCHEMA,
    cv.Optional(CONF_AC_IN): SENSOR_SCHEMA,
    cv.Optional(CONF_CURRENT_LIMIT): SENSOR_SCHEMA,
    cv.Optional(CONF_HEART): SENSOR_SCHEMA,
    cv.Optional(CONF_PACK_INDICATE): SENSOR_SCHEMA,
    cv.Optional(CONF_PROTECTION_DISCHARGE_CURRENT): SENSOR_SCHEMA,
    cv.Optional(CONF_PROTECTION_CHARGE_CURRENT): SENSOR_SCHEMA,
    cv.Optional(CONF_PROTECTION_SHORT_CIRCUIT): SENSOR_SCHEMA,
    cv.Optional(CONF_REVERSE): SENSOR_SCHEMA,
    cv.Optional(CONF_TEMPERATURE): SENSOR_SCHEMA,
    cv.Optional(CONF_CELL_1_VOLTAGE): SENSOR_SCHEMA,
    cv.Optional(CONF_CELL_2_VOLTAGE): SENSOR_SCHEMA,
    cv.Optional(CONF_CELL_3_VOLTAGE): SENSOR_SCHEMA,
    cv.Optional(CONF_CELL_4_VOLTAGE): SENSOR_SCHEMA,
    cv.Optional(CONF_CELL_5_VOLTAGE): SENSOR_SCHEMA,
    cv.Optional(CONF_CELL_6_VOLTAGE): SENSOR_SCHEMA,
    cv.Optional(CONF_CELL_7_VOLTAGE): SENSOR_SCHEMA,
    cv.Optional(CONF_CELL_8_VOLTAGE): SENSOR_SCHEMA,
    cv.Optional(CONF_CELL_9_VOLTAGE): SENSOR_SCHEMA,
    cv.Optional(CONF_CELL_10_VOLTAGE): SENSOR_SCHEMA,
    cv.Optional(CONF_CELL_11_VOLTAGE): SENSOR_SCHEMA,
    cv.Optional(CONF_CELL_12_VOLTAGE): SENSOR_SCHEMA,
    cv.Optional(CONF_CELL_13_VOLTAGE): SENSOR_SCHEMA,
    cv.Optional(CONF_CELL_14_VOLTAGE): SENSOR_SCHEMA,
    cv.Optional(CONF_CELL_15_VOLTAGE): SENSOR_SCHEMA,
    cv.Optional(CONF_TEMPERATURE_1): SENSOR_SCHEMA,
    cv.Optional(CONF_TEMPERATURE_2): SENSOR_SCHEMA,
    cv.Optional(CONF_TEMPERATURE_3): SENSOR_SCHEMA,
    cv.Optional(CONF_TEMPERATURE_4): SENSOR_SCHEMA,
    cv.Optional(CONF_TEMPERATURE_5): SENSOR_SCHEMA,
    cv.Optional(CONF_TEMPERATURE_6): SENSOR_SCHEMA,
    cv.Optional(CONF_BALANCING_1): SENSOR_SCHEMA,
    cv.Optional(CONF_BALANCING_2): SENSOR_SCHEMA,
    cv.Optional(CONF_WARNINGS): SENSOR_SCHEMA,
    cv.Optional(CONF_DESIGN_CAPACITY): SENSOR_SCHEMA,
    cv.Optional(CONF_PACK_FULL_CAPACITY): SENSOR_SCHEMA,
    cv.Optional(CONF_PACK_REMAINING_CAPACITY): SENSOR_SCHEMA,
    cv.Optional(CONF_PACK_STATE_OF_HEALTH): SENSOR_SCHEMA,
    cv.Optional(CONF_PACK_STATE_OF_CHARGE): SENSOR_SCHEMA,
})

async def to_code(config):
    var = await cg.get_variable(config[CONF_ID])
    if CONF_VOLTAGE in config:
        sens = await sensor.new_sensor(config[CONF_VOLTAGE])
        cg.add(var.set_voltage_sensor(sens))
    if CONF_CURRENT in config:
        sens = await sensor.new_sensor(config[CONF_CURRENT])
        cg.add(var.set_current_sensor(sens))
    if CONF_REMAINING_CAPACITY in config:
        sens = await sensor.new_sensor(config[CONF_REMAINING_CAPACITY])
        cg.add(var.set_remaining_capacity_sensor(sens))
    if CONF_NOMINAL_CAPACITY in config:
        sens = await sensor.new_sensor(config[CONF_NOMINAL_CAPACITY])
        cg.add(var.set_nominal_capacity_sensor(sens))
    if CONF_FULL_CAPACITY in config:
        sens = await sensor.new_sensor(config[CONF_FULL_CAPACITY])
        cg.add(var.set_full_capacity_sensor(sens))
    if CONF_CYCLES in config:
        sens = await sensor.new_sensor(config[CONF_CYCLES])
        cg.add(var.set_cycles_sensor(sens))
    if CONF_STATE_OF_HEALTH in config:
        sens = await sensor.new_sensor(config[CONF_STATE_OF_HEALTH])
        cg.add(var.set_state_of_health_sensor(sens))
    if CONF_STATE_OF_CHARGE in config:
        sens = await sensor.new_sensor(config[CONF_STATE_OF_CHARGE])
        cg.add(var.set_state_of_charge_sensor(sens))
    if CONF_CELL_MAX_VOLT_DIFF in config:
        sens = await sensor.new_sensor(config[CONF_CELL_MAX_VOLT_DIFF])
        cg.add(var.set_cell_max_volt_diff_sensor(sens))
    if CONF_CHARGE_FET in config:
        sens = await sensor.new_sensor(config[CONF_CHARGE_FET])
        cg.add(var.set_charge_fet_sensor(sens))
    if CONF_DISCHARGE_FET in config:
        sens = await sensor.new_sensor(config[CONF_DISCHARGE_FET])
        cg.add(var.set_discharge_fet_sensor(sens))
    if CONF_AC_IN in config:
        sens = await sensor.new_sensor(config[CONF_AC_IN])
        cg.add(var.set_ac_in_sensor(sens))
    if CONF_CURRENT_LIMIT in config:
        sens = await sensor.new_sensor(config[CONF_CURRENT_LIMIT])
        cg.add(var.set_current_limit_sensor(sens))
    if CONF_HEART in config:
        sens = await sensor.new_sensor(config[CONF_HEART])
        cg.add(var.set_heart_sensor(sens))
    if CONF_PACK_INDICATE in config:
        sens = await sensor.new_sensor(config[CONF_PACK_INDICATE])
        cg.add(var.set_pack_indicate_sensor(sens))
    if CONF_PROTECTION_DISCHARGE_CURRENT in config:
        sens = await sensor.new_sensor(config[CONF_PROTECTION_DISCHARGE_CURRENT])
        cg.add(var.set_protection_discharge_current_sensor(sens))
    if CONF_PROTECTION_CHARGE_CURRENT in config:
        sens = await sensor.new_sensor(config[CONF_PROTECTION_CHARGE_CURRENT])
        cg.add(var.set_protection_charge_current_sensor(sens))
    if CONF_PROTECTION_SHORT_CIRCUIT in config:
        sens = await sensor.new_sensor(config[CONF_PROTECTION_SHORT_CIRCUIT])
        cg.add(var.set_protection_short_circuit_sensor(sens))
    if CONF_REVERSE in config:
        sens = await sensor.new_sensor(config[CONF_REVERSE])
        cg.add(var.set_reverse_sensor(sens))
    if CONF_TEMPERATURE in config:
        sens = await sensor.new_sensor(config[CONF_TEMPERATURE])
        cg.add(var.set_temperature_sensor(sens))
    if CONF_CELL_1_VOLTAGE in config:
        sens = await sensor.new_sensor(config[CONF_CELL_1_VOLTAGE])
        cg.add(var.set_cell_1_voltage_sensor(sens))
    if CONF_CELL_2_VOLTAGE in config:
        sens = await sensor.new_sensor(config[CONF_CELL_2_VOLTAGE])
        cg.add(var.set_cell_2_voltage_sensor(sens))
    if CONF_CELL_3_VOLTAGE in config:
        sens = await sensor.new_sensor(config[CONF_CELL_3_VOLTAGE])
        cg.add(var.set_cell_3_voltage_sensor(sens))
    if CONF_CELL_4_VOLTAGE in config:
        sens = await sensor.new_sensor(config[CONF_CELL_4_VOLTAGE])
        cg.add(var.set_cell_4_voltage_sensor(sens))
    if CONF_CELL_5_VOLTAGE in config:
        sens = await sensor.new_sensor(config[CONF_CELL_5_VOLTAGE])
        cg.add(var.set_cell_5_voltage_sensor(sens))
    if CONF_CELL_6_VOLTAGE in config:
        sens = await sensor.new_sensor(config[CONF_CELL_6_VOLTAGE])
        cg.add(var.set_cell_6_voltage_sensor(sens))
    if CONF_CELL_7_VOLTAGE in config:
        sens = await sensor.new_sensor(config[CONF_CELL_7_VOLTAGE])
        cg.add(var.set_cell_7_voltage_sensor(sens))
    if CONF_CELL_8_VOLTAGE in config:
        sens = await sensor.new_sensor(config[CONF_CELL_8_VOLTAGE])
        cg.add(var.set_cell_8_voltage_sensor(sens))
    if CONF_CELL_9_VOLTAGE in config:
        sens = await sensor.new_sensor(config[CONF_CELL_9_VOLTAGE])
        cg.add(var.set_cell_9_voltage_sensor(sens))
    if CONF_CELL_10_VOLTAGE in config:
        sens = await sensor.new_sensor(config[CONF_CELL_10_VOLTAGE])
        cg.add(var.set_cell_10_voltage_sensor(sens))
    if CONF_CELL_11_VOLTAGE in config:
        sens = await sensor.new_sensor(config[CONF_CELL_11_VOLTAGE])
        cg.add(var.set_cell_11_voltage_sensor(sens))
    if CONF_CELL_12_VOLTAGE in config:
        sens = await sensor.new_sensor(config[CONF_CELL_12_VOLTAGE])
        cg.add(var.set_cell_12_voltage_sensor(sens))
    if CONF_CELL_13_VOLTAGE in config:
        sens = await sensor.new_sensor(config[CONF_CELL_13_VOLTAGE])
        cg.add(var.set_cell_13_voltage_sensor(sens))
    if CONF_CELL_14_VOLTAGE in config:
        sens = await sensor.new_sensor(config[CONF_CELL_14_VOLTAGE])
        cg.add(var.set_cell_14_voltage_sensor(sens))
    if CONF_CELL_15_VOLTAGE in config:
        sens = await sensor.new_sensor(config[CONF_CELL_15_VOLTAGE])
        cg.add(var.set_cell_15_voltage_sensor(sens))
    if CONF_TEMPERATURE_1 in config:
        sens = await sensor.new_sensor(config[CONF_TEMPERATURE_1])
        cg.add(var.set_temperature_1_sensor(sens))
    if CONF_TEMPERATURE_2 in config:
        sens = await sensor.new_sensor(config[CONF_TEMPERATURE_2])
        cg.add(var.set_temperature_2_sensor(sens))
    if CONF_TEMPERATURE_3 in config:
        sens = await sensor.new_sensor(config[CONF_TEMPERATURE_3])
        cg.add(var.set_temperature_3_sensor(sens))
    if CONF_TEMPERATURE_4 in config:
        sens = await sensor.new_sensor(config[CONF_TEMPERATURE_4])
        cg.add(var.set_temperature_4_sensor(sens))
    if CONF_TEMPERATURE_5 in config:
        sens = await sensor.new_sensor(config[CONF_TEMPERATURE_5])
        cg.add(var.set_temperature_5_sensor(sens))
    if CONF_TEMPERATURE_6 in config:
        sens = await sensor.new_sensor(config[CONF_TEMPERATURE_6])
        cg.add(var.set_temperature_6_sensor(sens))
    if CONF_BALANCING_1 in config:
        sens = await sensor.new_sensor(config[CONF_BALANCING_1])
        cg.add(var.set_balancing_1_sensor(sens))
    if CONF_BALANCING_2 in config:
        sens = await sensor.new_sensor(config[CONF_BALANCING_2])
        cg.add(var.set_balancing_2_sensor(sens))
    if CONF_WARNINGS in config:
        sens = await sensor.new_sensor(config[CONF_WARNINGS])
        cg.add(var.set_warnings_sensor(sens))
    if CONF_DESIGN_CAPACITY in config:
        sens = await sensor.new_sensor(config[CONF_DESIGN_CAPACITY])
        cg.add(var.set_design_capacity_sensor(sens))
    if CONF_PACK_FULL_CAPACITY in config:
        sens = await sensor.new_sensor(config[CONF_PACK_FULL_CAPACITY])
        cg.add(var.set_pack_full_capacity_sensor(sens))
    if CONF_PACK_REMAINING_CAPACITY in config:
        sens = await sensor.new_sensor(config[CONF_PACK_REMAINING_CAPACITY])
        cg.add(var.set_pack_remaining_capacity_sensor(sens))
    if CONF_PACK_STATE_OF_HEALTH in config:
        sens = await sensor.new_sensor(config[CONF_PACK_STATE_OF_HEALTH])
        cg.add(var.set_pack_state_of_health_sensor(sens))
    if CONF_PACK_STATE_OF_CHARGE in config:
        sens = await sensor.new_sensor(config[CONF_PACK_STATE_OF_CHARGE])
        cg.add(var.set_pack_state_of_charge_sensor(sens))
