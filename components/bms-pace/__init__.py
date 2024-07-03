import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import pins
from esphome.components import sensor, uart
from esphome.const import CONF_ID, CONF_SENSOR

# Vytvoření referencí pro naše vlastní komponenty
pace_bms_ns = cg.esphome_ns.namespace('pace_bms')
PaceBMS = pace_bms_ns.class_('PaceBMS', cg.Component, uart.UARTDevice)

# Definice všech senzorů, které bude naše komponenta podporovat
SENSOR_KEYS = [
    "voltage_sensor",
    "current_sensor",
    "remaining_capacity_sensor",
    "nominal_capacity_sensor",
    "full_capacity_sensor",
    "cycles_sensor",
    "state_of_health_sensor",
    "state_of_charge_sensor",
    "cell_max_volt_diff_sensor",
    "charge_fet_sensor",
    "discharge_fet_sensor",
    "balancing1_sensor",
    "balancing2_sensor",
    "ac_in_sensor",
    "current_limit_sensor",
    "heart_sensor",
    "pack_indicate_sensor",
    "protection_discharge_current_sensor",
    "protection_charge_current_sensor",
    "protection_short_circuit_sensor",
    "reverse_sensor",
]

CELL_VOLTAGE_KEYS = [f"cell_voltage_sensor_{i}" for i in range(1, 18)]
TEMPERATURE_KEYS = [f"temperature_sensor_{i}" for i in range(1, 7)]

# Kombinace všech senzorů
ALL_SENSOR_KEYS = SENSOR_KEYS + CELL_VOLTAGE_KEYS + TEMPERATURE_KEYS

# Konfigurace pro YAML
CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(PaceBMS),
    cv.Optional(CONF_SENSOR, default={}): cv.Schema({
        cv.Optional(key): sensor.sensor_schema() for key in ALL_SENSOR_KEYS
    })
}).extend(uart.UART_DEVICE_SCHEMA)

# Funkce pro konfiguraci
def to_code(config):
    # Vytvoření instance naší komponenty
    var = cg.new_Pvariable(config[CONF_ID])
    cg.add(var.set_uart_parent(uart.UARTDevice(config[CONF_ID])))
    
    # Přidání všech senzorů z YAML do komponenty
    for key in ALL_SENSOR_KEYS:
        if key in config[CONF_SENSOR]:
            sensor_conf = config[CONF_SENSOR][key]
            sens = yield sensor.new_sensor(sensor_conf)
            cg.add(getattr(var, f"set_{key}")(sens))

    # Zaregistrování komponenty
    cg.add(var.register_component())

# Registrace konfigurace a inicializační funkce
async def to_code(config):
    # Inicializace UART
    uart_var = await cg.get_variable(config[CONF_ID])
    cg.add(uart_var.set_uart_parent(uart_var))
    
    # Přidání všech senzorů
    for key in SENSOR_KEYS:
        if key in config[CONF_SENSOR]:
            sens = await sensor.new_sensor(config[CONF_SENSOR][key])
            cg.add(getattr(uart_var, f"set_{key}")(sens))
    
    # Přidání senzorů pro napětí článků
    for i, key in enumerate(CELL_VOLTAGE_KEYS):
        if key in config[CONF_SENSOR]:
            sens = await sensor.new_sensor(config[CONF_SENSOR][key])
            cg.add(uart_var.set_cell_voltage_sensor(i, sens))
    
    # Přidání teplotních senzorů
    for i, key in enumerate(TEMPERATURE_KEYS):
        if key in config[CONF_SENSOR]:
            sens = await sensor.new_sensor(config[CONF_SENSOR][key])
            cg.add(uart_var.set_temperature_sensor(i, sens))

# Registrace komponenty v ESPHome
async def to_code(config):
    # Vytvoření instance naší komponenty
    var = cg.new_Pvariable(config[CONF_ID])
    
    # Připojení UART komponenty
    uart_component = await cg.get_variable(config[CONF_ID])
    cg.add(var.set_uart_parent(uart_component))

    # Přidání všech senzorů z YAML do komponenty
    for key in ALL_SENSOR_KEYS:
        if key in config[CONF_SENSOR]:
            sensor_conf = config[CONF_SENSOR][key]
            sens = await sensor.new_sensor(sensor_conf)
            cg.add(getattr(var, f"set_{key}")(sens))

    # Zaregistrování komponenty
    cg.add(var.register_component())

# Registrace naší komponenty v ESPHome
async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

    for key in SENSOR_KEYS:
        if key in config[CONF_SENSOR]:
            sens = await sensor.new_sensor(config[CONF_SENSOR][key])
            cg.add(getattr(var, f"set_{key}")(sens))
    
    for i, key in enumerate(CELL_VOLTAGE_KEYS):
        if key in config[CONF_SENSOR]:
            sens = await sensor.new_sensor(config[CONF_SENSOR][key])
            cg.add(var.set_cell_voltage_sensor(i, sens))
    
    for i, key in enumerate(TEMPERATURE_KEYS):
        if key in config[CONF_SENSOR]:
            sens = await sensor.new_sensor(config[CONF_SENSOR][key])
            cg.add(var.set_temperature_sensor(i, sens))
