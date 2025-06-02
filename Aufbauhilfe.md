# 🛠️ Aufbauhilfe – Smart Garden LoRa

## 📍 Systemübersicht

Das System besteht aus 3 Hauptknoten:

1. **Zentrale (Haus)**
   - Empfängt LoRa-Daten von den Ventilknoten
   - Sendet Steuerbefehle zurück
   - Optional: zeigt Status auf OLED-Display
   - Per App (Bluetooth) steuerbar

2. **Ventilknoten (z. B. Gewächshaus, Feld links, Feld rechts)**
   - Misst Bodenfeuchte
   - Öffnet 12V-Magnetventil bei Bedarf
   - Sendet Daten per LoRa zur Zentrale
   - Empfängt Steuerbefehle

3. **Wetterknoten (einmal im Feld)**
   - Misst Regen und Temperatur (Frost)
   - Wird wie ein Ventilknoten betrieben

---

## 🔌 Anschlussplan pro Ventilknoten

### ESP32 → LoRa SX1278 Modul

| LoRa Pin     | ESP32 Pin |
|--------------|------------|
| VCC          | 3.3V       |
| GND          | GND        |
| MISO         | 19         |
| MOSI         | 23         |
| SCK          | 18         |
| NSS (CS)     | 5          |
| RESET        | 14         |
| DIO0         | 26         |

---

### ESP32 → Bodenfeuchtesensor (analog)

| Sensor Pin | ESP32 Pin |
|------------|------------|
| VCC        | 3.3V       |
| GND        | GND        |
| SIG (analog) | 34       |

---

### ESP32 → 1-Kanal Relaismodul

| Relaismodul Pin | ESP32 Pin |
|------------------|-----------|
| IN               | 25        |
| VCC              | 5V        |
| GND              | GND       |

→ Das Relais schaltet das **12V Magnetventil** direkt.

---

### Stromversorgung (Akku & Solar)

- 12V Batterie an Relaismodul & Ventil
- 12V → 5V Buck Converter → ESP32 & Sensoren
- Solar-Laderegler schützt Akku vor Überladung

---

### Zusatzsensoren (optional)

**Regensensor FC-37 / YL-83**  
→ Digital Out an ESP32 Pin **33**

**Frostsensor (DS18B20, digital 1-Wire)**  
→ Data an Pin **32**, Pullup 4.7kΩ

---

## 💡 Hinweis zur Energie

- DeepSleep wird im Code verwendet, um Batterielaufzeit zu verlängern.
- Der LoRa-Funk erfolgt nur 1× pro Messung (z. B. alle 10 Min.)
