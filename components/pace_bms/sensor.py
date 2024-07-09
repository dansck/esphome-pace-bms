import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import CONF_ID, UNIT_VOLTAGE, UNIT_CURRENT, UNIT_TEMPERATURE, ICON_THERMOMETER

pace_bms_ns = cg.esphome_ns.namespace('pace_bms')
PaceBms = pace_bms_ns.class_('PaceBms', cg.PollingComponent)

CONF_PACE_BMS_ID = 'pace_bms_id'
CONF_VOLTAGE = 'voltage'
CONF_CURRENT = 'current'
CONF_TEMPERATURE = 'temperature'

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(PaceBms),
    cv.Optional(CONF_VOLTAGE): sensor.sensor_schema(UNIT_VOLTAGE, ICON_THERMOMETER, 1),
    cv.Optional(CONF_CURRENT): sensor.sensor_schema(UNIT_CURRENT, ICON_THERMOMETER, 1),
    cv.Optional(CONF_TEMPERATURE): sensor.sensor_schema(UNIT_TEMPERATURE, ICON_THERMOMETER, 1),
}).extend(cv.polling_component_schema('60s'))

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    if CONF_VOLTAGE in config:
        cg.add(var.set_voltage_sensor(config[CONF_VOLTAGE]))
    if CONF_CURRENT in config:
        cg.add(var.set_current_sensor(config[CONF_CURRENT]))
    if CONF_TEMPERATURE in config:
        cg.add(var.set_temperature_sensor(config[CONF_TEMPERATURE]))
    cg.register_component(var, config)
