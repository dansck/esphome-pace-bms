#include "esphome.h"

class PaceBMS : public Component, public UARTDevice {
 public:
  PaceBMS(UARTComponent *parent) : UARTDevice(parent) {}

  // Základní informace
  Sensor *voltage_sensor = new Sensor();
  Sensor *current_sensor = new Sensor();
  Sensor *remaining_capacity_sensor = new Sensor();
  Sensor *nominal_capacity_sensor = new Sensor();
  Sensor *full_capacity_sensor = new Sensor();
  Sensor *cycles_sensor = new Sensor();
  Sensor *state_of_health_sensor = new Sensor();
  Sensor *state_of_charge_sensor = new Sensor();

  // Napětí článků (17 senzorů pro jednotlivé články)
  std::vector<Sensor *> cell_voltage_sensors;
  
  // Rozdíl napětí
  Sensor *cell_max_volt_diff_sensor = new Sensor();
  
  // Teplota (6 senzorů)
  std::vector<Sensor *> temperature_sensors;

  // Stav MOSFETů
  Sensor *charge_fet_sensor = new Sensor();
  Sensor *discharge_fet_sensor = new Sensor();

  // Balancování
  Sensor *balancing1_sensor = new Sensor();
  Sensor *balancing2_sensor = new Sensor();
  
  // Další stavy
  Sensor *ac_in_sensor = new Sensor();
  Sensor *current_limit_sensor = new Sensor();
  Sensor *heart_sensor = new Sensor();
  Sensor *pack_indicate_sensor = new Sensor();
  Sensor *protection_discharge_current_sensor = new Sensor();
  Sensor *protection_charge_current_sensor = new Sensor();
  Sensor *protection_short_circuit_sensor = new Sensor();
  Sensor *reverse_sensor = new Sensor();

  void setup() override {
    // Inicializace senzorů pro napětí článků
    for (int i = 0; i < 17; i++) {
      auto sensor = new Sensor();
      cell_voltage_sensors.push_back(sensor);
    }

    // Inicializace senzorů pro teplotu
    for (int i = 0; i < 6; i++) {
      auto sensor = new Sensor();
      temperature_sensors.push_back(sensor);
    }
  }

  void loop() override {
    // Čtení a zpracování dat v pravidelných intervalech
    if (millis() - last_read_time >= 5000) {  // Čtení dat každých 5 sekund
      last_read_time = millis();
      get_data_from_bms();
    }
  }

  uint8_t calculate_crc(const uint8_t *data, size_t length) {
    uint8_t crc = 0;
    for (size_t i = 0; i < length; i++) {
      crc += data[i];
    }
    return crc & 0xFF;
  }

  std::vector<uint8_t> bms_request(const uint8_t *command, size_t command_length, uint8_t address = 0x00) {
    size_t total_length = command_length + 4;
    std::vector<uint8_t> data(total_length);
    data[0] = 0xAA;
    data[1] = address;
    data[2] = command_length + 3;
    memcpy(&data[3], command, command_length);
    data[total_length - 1] = calculate_crc(data.data(), total_length - 1);
    return data;
  }

  void bms_send_data(const std::vector<uint8_t> &command) {
    // Odeslání příkazu na sériový port
    write_array(command.data(), command.size());
    flush();  // Ujistíme se, že jsou data odeslána
  }

  std::vector<uint8_t> bms_get_data(const uint8_t *command, size_t command_length) {
    std::vector<uint8_t> request = bms_request(command, command_length);
    bms_send_data(request);

    // Čekání na odpověď
    std::vector<uint8_t> response;
    delay(500);  // Počkáme na odpověď

    while (available() > 0) {
      response.push_back(read());
      delay(10);  // Krátká prodleva pro čekání na další byte
    }

    if (response.size() < 10) {
      ESP_LOGW("pace_bms", "Received data is too short or incomplete");
      return {};
    }

    return response;
  }

  void get_data_from_bms() {
    // Získání základních informací z BMS
    uint8_t basic_info_command[] = {0x03, 0x01};
    std::vector<uint8_t> basic_info_data = bms_get_data(basic_info_command, sizeof(basic_info_command));

    if (!basic_info_data.empty()) {
      auto basic_info = decode_basic_info(basic_info_data);
      publish_state(voltage_sensor, basic_info["voltage"]);
      publish_state(current_sensor, basic_info["current"]);
      publish_state(remaining_capacity_sensor, basic_info["remaining_capacity"]);
      publish_state(nominal_capacity_sensor, basic_info["nominal_capacity"]);
      publish_state(full_capacity_sensor, basic_info["full_capacity"]);
      publish_state(cycles_sensor, basic_info["cycles"]);
      publish_state(state_of_health_sensor, basic_info["state_of_health"]);
      publish_state(state_of_charge_sensor, basic_info["state_of_charge"]);
    }

    // Získání napětí jednotlivých článků
    uint8_t cell_voltage_command[] = {0x04, 0x01};
    std::vector<uint8_t> cell_voltage_data = bms_get_data(cell_voltage_command, sizeof(cell_voltage_command));

    if (!cell_voltage_data.empty()) {
      auto cell_voltages = decode_cell_voltage(cell_voltage_data);
      for (size_t i = 0; i < cell_voltages.size() && i < cell_voltage_sensors.size(); i++) {
        publish_state(cell_voltage_sensors[i], cell_voltages[i]);
      }
    }

    // Rozdíl napětí mezi články
    uint8_t cell_diff_voltage_command[] = {0x04, 0x02};  // Příklad příkazu
    std::vector<uint8_t> cell_diff_voltage_data = bms_get_data(cell_diff_voltage_command, sizeof(cell_diff_voltage_command));

    if (!cell_diff_voltage_data.empty()) {
      float max_volt_diff = decode_cell_max_volt_diff(cell_diff_voltage_data);
      publish_state(cell_max_volt_diff_sensor, max_volt_diff);
    }

    // Získání teplot
    uint8_t temperature_command[] = {0x05, 0x01};
    std::vector<uint8_t> temperature_data = bms_get_data(temperature_command, sizeof(temperature_command));

    if (!temperature_data.empty()) {
      auto temperatures = decode_temperature(temperature_data);
      for (size_t i = 0; i < temperatures.size() && i < temperature_sensors.size(); i++) {
        publish_state(temperature_sensors[i], temperatures[i]);
      }
    }

    // Získání stavu MOSFETu
    uint8_t mosfet_status_command[] = {0x06, 0x01};
    std::vector<uint8_t> mosfet_status_data = bms_get_data(mosfet_status_command, sizeof(mosfet_status_command));

    if (!mosfet_status_data.empty()) {
      auto mosfet_status = decode_mosfet_status(mosfet_status_data);
      publish_state(charge_fet_sensor, mosfet_status["charge_fet"]);
      publish_state(discharge_fet_sensor, mosfet_status["discharge_fet"]);
    }

    // Další stavy a ochrany
    uint8_t status_command[] = {0x07, 0x01};  // Příklad příkazu
    std::vector<uint8_t> status_data = bms_get_data(status_command, sizeof(status_command));

    if (!status_data.empty()) {
      auto statuses = decode_status(status_data);
      publish_state(ac_in_sensor, statuses["ac_in"]);
      publish_state(current_limit_sensor, statuses["current_limit"]);
      publish_state(heart_sensor, statuses["heart"]);
      publish_state(pack_indicate_sensor, statuses["pack_indicate"]);
      publish_state(protection_discharge_current_sensor, statuses["protection_discharge_current"]);
      publish_state(protection_charge_current_sensor, statuses["protection_charge_current"]);
      publish_state(protection_short_circuit_sensor, statuses["protection_short_circuit"]);
      publish_state(reverse_sensor, statuses["reverse"]);
    }
  }

  std::map<std::string, float> decode_basic_info(const std::vector<uint8_t> &data) {
    std::map<std::string, float> result;
    result["voltage"] = ((data[4] << 8) | data[5]) / 10.0;  // Napětí v V
    result["current"] = ((data[6] << 8) | data[7]) / 10.0;  // Proud v A
    result["remaining_capacity"] = ((data[8] << 8) | data[9]);  // Zbývající kapacita v mAh
    result["nominal_capacity"] = ((data[10] << 8) | data[11]);  // Nominální kapacita v mAh
    result["full_capacity"] = ((data[14] << 8) | data[15]);  // Plná kapacita v mAh
    result["cycles"] = ((data[12] << 8) | data[13]);  // Počet cyklů
    result["state_of_health"] = data[16];  // Stav zdraví v procentech
    result["state_of_charge"] = ((data[17] << 8) | data[18]) / 100.0;  // Stav nabití v procentech
    return result;
  }

  std::vector<float> decode_cell_voltage(const std::vector<uint8_t> &data) {
    std::vector<float> cell_voltages;
    for (int i = 0; i < 17; i++) {
      float voltage = ((data[4 + i * 2] << 8) | data[5 + i * 2]) / 1000.0;  // Napětí v V
      cell_voltages.push_back(voltage);
    }
    return cell_voltages;
  }

  float decode_cell_max_volt_diff(const std::vector<uint8_t> &data) {
    return ((data[4] << 8) | data[5]) / 1000.0;  // Rozdíl napětí v mV
  }

  std::vector<float> decode_temperature(const std::vector<uint8_t> &data) {
    std::vector<float> temperatures;
    for (int i = 0; i < 6; i++) {
      float temp = ((data[30 + i * 2] << 8) | data[31 + i * 2]) / 10.0;  // Teplota ve °C
      temperatures.push_back(temp);
    }
    return temperatures;
  }

  std::map<std::string, float> decode_mosfet_status(const std::vector<uint8_t> &data) {
    std::map<std::string, float> result;
    result["charge_fet"] = data[24] & 0x01;  // Stav charge FET
    result["discharge_fet"] = data[24] & 0x02;  // Stav discharge FET
    return result;
  }

  std::map<std::string, float> decode_status(const std::vector<uint8_t> &data) {
    std::map<std::string, float> result;
    result["ac_in"] = data[25];  // Stav AC In
    result["current_limit"] = data[26];  // Aktuální limit
    result["heart"] = data[27];  // Stav Heart
    result["pack_indicate"] = data[28];  // Stav Pack Indicate
    result["protection_discharge_current"] = data[29];  // Ochrana před výbojovým proudem
    result["protection_charge_current"] = data[30];  // Ochrana před nabíjecím proudem
    result["protection_short_circuit"] = data[31];  // Ochrana proti zkratu
    result["reverse"] = data[32];  // Ochrana proti obrácení polarity
    return result;
  }

 private:
  uint32_t last_read_time = 0;

  void publish_state(Sensor *sensor, float value) {
    if (sensor != nullptr) {
      sensor->publish_state(value);
    }
  }
};
