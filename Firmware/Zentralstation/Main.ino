#include <SPI.h>
#include <LoRa.h>
#include <BluetoothSerial.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

BluetoothSerial SerialBT;

#define LORA_SCK 18
#define LORA_MISO 19
#define LORA_MOSI 23
#define LORA_SS 5
#define LORA_RST 14
#define LORA_IRQ 26

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Beispieldaten
struct SensorData {
  uint8_t id;             // Knoten-ID
  int feuchtigkeit;       // 0-1023
  bool regen;
  bool frost;
  int akkuspannung;       // in mV
};

void setup() {
  Serial.begin(115200);
  SerialBT.begin("SmartGarden-Zentrale");

  // Display init
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("Smart Garden");
  display.display();

  // LoRa init
  SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_SS);
  LoRa.setPins(LORA_SS, LORA_RST, LORA_IRQ);

  if (!LoRa.begin(433E6)) {
    display.print("LoRa Init failed");
    display.display();
    while (1);
  }

  LoRa.setSpreadingFactor(12);
  display.println("LoRa OK");
  display.display();
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    SensorData data;
    LoRa.readBytes((uint8_t *)&data, sizeof(data));

    // Anzeige
    display.clearDisplay();
    display.setCursor(0,0);
    display.printf("ID: %d\nFeuchte: %d\nRegen: %d\nFrost: %d\nAkku: %d mV",
                   data.id, data.feuchtigkeit, data.regen, data.frost, data.akkuspannung);
    display.display();

    // Steuerlogik (einfach)
    if (data.feuchtigkeit < 600 && !data.regen && !data.frost) {
      LoRa.beginPacket();
      LoRa.write(data.id);  // Empfänger-ID
      LoRa.write(1);        // 1 = Ventil öffnen
      LoRa.endPacket();
    } else {
      LoRa.beginPacket();
      LoRa.write(data.id);
      LoRa.write(0);        // 0 = Ventil schließen
      LoRa.endPacket();
    }

    // Log an App
    SerialBT.printf("Node %d: Feuchte=%d, Regen=%d, Frost=%d, Akku=%d\n",
                    data.id, data.feuchtigkeit, data.regen, data.frost, data.akkuspannung);
  }

  delay(500); // etwas Pufferzeit
}
