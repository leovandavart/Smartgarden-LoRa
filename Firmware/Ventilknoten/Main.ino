#include <SPI.h>
#include <LoRa.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define NODE_ID 1   // ⚠️ Ändern je Ventilknoten: 1, 2, 3 etc.

#define SOIL_PIN 34          // analog
#define RELAIS_PIN 25        // digital
#define REGENSENSOR_PIN 33   // digital (optional)
#define FROSTSENSOR_PIN 32   // digital (DS18B20)

#define LORA_SCK 18
#define LORA_MISO 19
#define LORA_MOSI 23
#define LORA_SS 5
#define LORA_RST 14
#define LORA_IRQ 26

OneWire oneWire(FROSTSENSOR_PIN);
DallasTemperature frostSensor(&oneWire);

// Struktur für die Datenübertragung
struct SensorData {
  uint8_t id;
  int feuchtigkeit;
  bool regen;
  bool frost;
  int akkuspannung;
};

void setup() {
  Serial.begin(115200);
  delay(500);

  pinMode(RELAIS_PIN, OUTPUT);
  digitalWrite(RELAIS_PIN, LOW); // Sicher starten

  pinMode(REGENSENSOR_PIN, INPUT);

  frostSensor.begin();

  // LoRa starten
  SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_SS);
  LoRa.setPins(LORA_SS, LORA_RST, LORA_IRQ);
  LoRa.begin(433E6);
  LoRa.setSpreadingFactor(12);

  delay(100);

  // Sensordaten vorbereiten
  SensorData data;
  data.id = NODE_ID;
  data.feuchtigkeit = analogRead(SOIL_PIN);
  data.regen = !digitalRead(REGENSENSOR_PIN); // FC-37 aktiv LOW
  frostSensor.requestTemperatures();
  float tempC = frostSensor.getTempCByIndex(0);
  data.frost = (tempC < 1.0); // unter 1°C = Frost
  data.akkuspannung = analogRead(35) * (3.3 / 4095.0) * 2 * 1000; // Spannungsteiler

  // Senden
  LoRa.beginPacket();
  LoRa.write((uint8_t *)&data, sizeof(data));
  LoRa.endPacket();

  Serial.println("Daten gesendet.");

  // Warten auf Antwort (max. 5 Sek.)
  unsigned long start = millis();
  while (millis() - start < 5000) {
    int packetSize = LoRa.parsePacket();
    if (packetSize == 2) {
      uint8_t targetID = LoRa.read();
      uint8_t command = LoRa.read();
      if (targetID == NODE_ID) {
        digitalWrite(RELAIS_PIN, command == 1 ? HIGH : LOW);
        delay(command == 1 ? 60000 : 1000); // z. B. 60 Sek. offen
        digitalWrite(RELAIS_PIN, LOW); // sicher schließen
        break;
      }
    }
  }

  Serial.println("Gehe in DeepSleep...");
  esp_sleep_enable_timer_wakeup(10 * 60 * 1000000ULL); // alle 10 Min
  esp_deep_sleep_start();
}

void loop() {}
