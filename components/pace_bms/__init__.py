import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, uart
from esphome.const import (
    CONF_ID,
)
CODEOWNERS = ["dansck"]

DEPENDENCIES = ['uart']
AUTO_LOAD = ['sensor']

CONF_PACE_BMS_ID = "pace_bms_id"

pace_bms_ns = cg.esphome_ns.namespace('pace_bms')
PaceBMS = pace_bms_ns.class_('PaceBMS', cg.Component, uart.UARTDevice)

CONFIG_SCHEMA = cv.All(
    cv.Schema({
        cv.GenerateID(): cv.declare_id(PaceBMS),
        
    }).extend(cv.COMPONENT_SCHEMA).extend(uart.UART_DEVICE_SCHEMA)
)

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    cg.add(var.set_timeout(5000))


    cg.add(var.init())