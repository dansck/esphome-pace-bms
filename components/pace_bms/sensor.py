import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import (
    ICON_EMPTY,
    DEVICE_CLASS_TEMPERATURE,
    STATE_CLASS_MEASUREMENT,
    CONF_UNIT_OF_MEASUREMENT,
    CONF_DEVICE_CLASS,
    UNIT_CELSIUS,
    UNIT_PERCENT,
    DEVICE_CLASS_VOLTAGE,
    UNIT_VOLT
)
from . import CONF_PACE_BMS_ID, PaceBMS
CODEOWNERS = ["dansck"]

DEPENDENCIES = []


CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_PACE_BMS_ID): cv.use_id(PaceBMS),
        cv.Optional('voltage_sensor'): sensor.sensor_schema(
            unit_of_measurement=UNIT_VOLT,
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
    }#.extend(cv.COMPONENT_SCHEMA).extend(uart.UART_DEVICE_SCHEMA)
)

async def to_code(config):
    var = await cg.get_variable(config[CONF_PACE_BMS_ID])
    #cg.new_Pvariable(config[CONF_ID])
    #cg.add(var.set_timeout(5000))

    if 'voltage_sensor' in config:
        sens = yield sensor.new_sensor(config['voltage_sensor'])
        cg.add(var.set_voltage_sensor(sens))

    if 'current_sensor' in config:
        sens = yield sensor.new_sensor(config['current_sensor'])
        cg.add(var.set_current_sensor(sens))

    if 'remaining_capacity_sensor' in config:
        sens = yield sensor.new_sensor(config['remaining_capacity_sensor'])
        cg.add(var.set_remaining_capacity_sensor(sens))

    if 'nominal_capacity_sensor' in config:
        sens = yield sensor.new_sensor(config['nominal_capacity_sensor'])
        cg.add(var.set_nominal_capacity_sensor(sens))

    if 'full_capacity_sensor' in config:
        sens = yield sensor.new_sensor(config['full_capacity_sensor'])
        cg.add(var.set_full_capacity_sensor(sens))

    if 'cycles_sensor' in config:
        sens = yield sensor.new_sensor(config['cycles_sensor'])
        cg.add(var.set_cycles_sensor(sens))

    if 'state_of_health_sensor' in config:
        sens = yield sensor.new_sensor(config['state_of_health_sensor'])
        cg.add(var.set_state_of_health_sensor(sens))

    if 'state_of_charge_sensor' in config:
        sens = yield sensor.new_sensor(config['state_of_charge_sensor'])
        cg.add(var.set_state_of_charge_sensor(sens))

    if 'cell_max_volt_diff_sensor' in config:
        sens = yield sensor.new_sensor(config['cell_max_volt_diff_sensor'])
        cg.add(var.set_cell_max_volt_diff_sensor(sens))

    if 'charge_fet_sensor' in config:
        sens = yield sensor.new_sensor(config['charge_fet_sensor'])
        cg.add(var.set_charge_fet_sensor(sens))

    if 'discharge_fet_sensor' in config:
        sens = yield sensor.new_sensor(config['discharge_fet_sensor'])
        cg.add(var.set_discharge_fet_sensor(sens))

    if 'balancing1_sensor' in config:
        sens = yield sensor.new_sensor(config['balancing1_sensor'])
        cg.add(var.set_balancing1_sensor(sens))

    if 'balancing2_sensor' in config:
        sens = yield sensor.new_sensor(config['balancing2_sensor'])
        cg.add(var.set_balancing2_sensor(sens))

    if 'ac_in_sensor' in config:
        sens = yield sensor.new_sensor(config['ac_in_sensor'])
        cg.add(var.set_ac_in_sensor(sens))

    if 'current_limit_sensor' in config:
        sens = yield sensor.new_sensor(config['current_limit_sensor'])
        cg.add(var.set_current_limit_sensor(sens))

    if 'heart_sensor' in config:
        sens = yield sensor.new_sensor(config['heart_sensor'])
        cg.add(var.set_heart_sensor(sens))

    if 'pack_indicate_sensor' in config:
        sens = yield sensor.new_sensor(config['pack_indicate_sensor'])
        cg.add(var.set_pack_indicate_sensor(sens))

    if 'protection_discharge_current_sensor' in config:
        sens = yield sensor.new_sensor(config['protection_discharge_current_sensor'])
        cg.add(var.set_protection_discharge_current_sensor(sens))

    if 'protection_charge_current_sensor' in config:
        sens = yield sensor.new_sensor(config['protection_charge_current_sensor'])
        cg.add(var.set_protection_charge_current_sensor(sens))

    if 'protection_short_circuit_sensor' in config:
        sens = yield sensor.new_sensor(config['protection_short_circuit_sensor'])
        cg.add(var.set_protection_short_circuit_sensor(sens))

    if 'reverse_sensor' in config:
        sens = yield sensor.new_sensor(config['reverse_sensor'])
        cg.add(var.set_reverse_sensor(sens))

    # Nastavení senzorů pro napětí jednotlivých článků
    for i in range(1, 18):
        key = f'cell_voltage_sensor_{i}'
        if key in config:
            sens = yield sensor.new_sensor(config[key])
            cg.add(var.set_cell_voltage_sensor(i - 1, sens))  # Indexované od 0

    # Nastavení teplotních senzorů
    for i in range(1, 7):
        key = f'temperature_sensor_{i}'
        if key in config:
            sens = yield sensor.new_sensor(config[key])
            cg.add(var.set_temperature_sensor(i - 1, sens))  # Indexované od 0

    cg.add(var.init())
