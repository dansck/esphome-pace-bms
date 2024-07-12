import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart, sensor
from esphome.const import CONF_ID

CODEOWNERS = ["dansck"]

DEPENDENCIES = ['uart']

CONF_PACE_BMS_ID = "pace_bms_id"
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
CONF_BALANCING_1 = "balancing_1"
CONF_BALANCING_2 = "balancing_2"
CONF_WARNINGS = "warnings"
CONF_DESIGN_CAPACITY = "design_capacity"
CONF_PACK_FULL_CAPACITY = "pack_full_capacity"
CONF_PACK_REMAINING_CAPACITY = "pack_remaining_capacity"
CONF_PACK_STATE_OF_HEALTH = "pack_state_of_health"
CONF_PACK_STATE_OF_CHARGE = "pack_state_of_charge"

# Generate cell voltage and temperature configuration keys
CONF_CELL_VOLTAGES = ["cell_{}_voltage".format(i) for i in range(1, 16)]
CONF_TEMPERATURES = ["temperature_{}".format(i) for i in range(1, 7)]

CONF_PACK_NUMBER = "pack_number"
CONF_PACK_ANALOG_DATA = "pack_analog_data"
CONF_SOFTWARE_VERSION = "software_version"
CONF_SERIAL_NUMBER = "serial_number"
CONF_PACK_CAPACITY = "pack_capacity"
CONF_WARN_INFO = "warn_info"

AUTO_LOAD = ['sensor']
MULTI_CONF = True

pace_bms_ns = cg.esphome_ns.namespace('pace_bms')
PaceBMS = pace_bms_ns.class_('PaceBMS', cg.Component, uart.UARTDevice)

SENSOR_SCHEMA = sensor.sensor_schema()

CONFIG_SCHEMA = cv.All(
    cv.Schema({
        cv.GenerateID(CONF_ID): cv.declare_id(PaceBMS),
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
        **{cv.Optional(voltage): SENSOR_SCHEMA for voltage in CONF_CELL_VOLTAGES},
        **{cv.Optional(temp): SENSOR_SCHEMA for temp in CONF_TEMPERATURES},
        cv.Optional(CONF_BALANCING_1): SENSOR_SCHEMA,
        cv.Optional(CONF_BALANCING_2): SENSOR_SCHEMA,
        cv.Optional(CONF_WARNINGS): SENSOR_SCHEMA,
        cv.Optional(CONF_DESIGN_CAPACITY): SENSOR_SCHEMA,
        cv.Optional(CONF_PACK_FULL_CAPACITY): SENSOR_SCHEMA,
        cv.Optional(CONF_PACK_REMAINING_CAPACITY): SENSOR_SCHEMA,
        cv.Optional(CONF_PACK_STATE_OF_HEALTH): SENSOR_SCHEMA,
        cv.Optional(CONF_PACK_STATE_OF_CHARGE): SENSOR_SCHEMA,
        cv.Optional(CONF_PACK_NUMBER): SENSOR_SCHEMA,
        cv.Optional(CONF_PACK_ANALOG_DATA): SENSOR_SCHEMA,
        cv.Optional(CONF_SOFTWARE_VERSION): SENSOR_SCHEMA,
        cv.Optional(CONF_SERIAL_NUMBER): SENSOR_SCHEMA,
        cv.Optional(CONF_PACK_CAPACITY): SENSOR_SCHEMA,
        cv.Optional(CONF_WARN_INFO): SENSOR_SCHEMA,
    }).extend(cv.COMPONENT_SCHEMA).extend(uart.UART_DEVICE_SCHEMA)
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

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
    for voltage in CONF_CELL_VOLTAGES:
        if voltage in config:
            sens = await sensor.new_sensor(config[voltage])
            cg.add(getattr(var, f'set_{voltage}_sensor')(sens))
    for temp in CONF_TEMPERATURES:
        if temp in config:
            sens = await sensor.new_sensor(config[temp])
            cg.add(getattr(var, f'set_{temp}_sensor')(sens))
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
    if CONF_PACK_NUMBER in config:
        sens = await sensor.new_sensor(config[CONF_PACK_NUMBER])
        cg.add(var.set_pack_number_sensor(sens))
    if CONF_PACK_ANALOG_DATA in config:
        sens = await sensor.new_sensor(config[CONF_PACK_ANALOG_DATA])
        cg.add(var.set_pack_analog_data_sensor(sens))
    if CONF_SOFTWARE_VERSION in config:
        sens = await sensor.new_sensor(config[CONF_SOFTWARE_VERSION])
        cg.add(var.set_software_version_sensor(sens))
    if CONF_SERIAL_NUMBER in config:
        sens = await sensor.new_sensor(config[CONF_SERIAL_NUMBER])
        cg.add(var.set_serial_number_sensor(sens))
    if CONF_PACK_CAPACITY in config:
        sens = await sensor.new_sensor(config[CONF_PACK_CAPACITY])
        cg.add(var.set_pack_capacity_sensor(sens))
    if CONF_WARN_INFO in config:
        sens = await sensor.new_sensor(config[CONF_WARN_INFO])
        cg.add(var.set_warn_info_sensor(sens))
