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
CONF_CELL_VOLTAGES = "cell_voltages"
CONF_TEMPERATURES = "temperatures"
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
    cv.Optional(CONF_CELL_VOLTAGES): cv.All(
        cv.ensure_list(SENSOR_SCHEMA), cv.Length(min=1)
    ),
    cv.Optional(CONF_TEMPERATURES): cv.All(
        cv.ensure_list(SENSOR_SCHEMA), cv.Length(min=1)
    ),
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
    if CONF_CELL_VOLTAGES in config:
        sens = []
        for i in range(len(config[CONF_CELL_VOLTAGES])):
            s = await sensor.new_sensor(config[CONF_CELL_VOLTAGES][i])
            sens.append(s)
        cg.add(var.set_cell_voltage_sensors(sens))
    if CONF_TEMPERATURES in config:
        sens = []
        for i in range(len(config[CONF_TEMPERATURES])):
            s = await sensor.new_sensor(config[CONF_TEMPERATURES][i])
            sens.append(s)
        cg.add(var.set_temperature_sensors(sens))
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
