
🌿 Smarte Bewässerung Garten

Ein modular aufgebautes, offline-fähiges Bewässerungssystem zur Steuerung von Gewächshaus und Gartenfeldern – mit LoRa-Kommunikation, Bodenfeuchtesensoren, Wetter-Logik und App-Steuerung per Bluetooth.


---

🔧 Systemübersicht

🌱 3 Bewässerungszonen: Gewächshaus, Feld links, Feld rechts

💧 12 V Magnetventile mit LoRa-fähiger Steuerung

🌡️ Sensoren: Bodenfeuchte, Regen, Frost, Akkustand

🔋 Autarke Knoten mit 12 V-Akku + Solarpanel

📶 Zentrale im Haus mit ESP32 & Bluetooth

📱 Mobile App (Android): Steuerung, Zeitpläne, Status



---

📦 Projektstruktur

smarte-bewaesserung-garten/
├── firmware/
│   ├── zentralstation/         # LoRa-Empfänger (ESP32)
│   └── ventilknoten/           # Sensorknoten & Ventilsteuerung (ESP32)
├── flutter_app/                # Mobile App (Bluetooth)
│   └── lib/
│       └── main.dart
├── docs/
│   └── wiring_schematic.png    # Schaltplan
└── README.md


---

🧠 Funktionsweise

Zentrale (im Haus):

Empfängt Messdaten über LoRa (Feuchte, Akku, Regen, Frost)

Gibt Schaltbefehle über LoRa an die Knoten weiter

Kommuniziert per Bluetooth mit der App


Ventilknoten (je Zone):

Messen Bodenfeuchte (analog)

Steuern 12 V Magnetventile

Haben Akkuspannungsüberwachung & Regen-/Frostsensor

Versorgt über 12 V 18 Ah Akku + Solar-Laderegler




---

📱 App-Funktionen

Übersicht aller Zonen

Feuchtigkeitswerte & Ventilstatus

Akkuspannung je Knoten

Zeitplan pro Bereich

Manueller/automatischer Betrieb

Kein Internet erforderlich



---

⚙️ Konfiguration

ID & Zonenname pro Knoten über App festlegen

Zeitplan je Bereich anpassbar

Optional: Regensperre & Frostschutz

Designfarben & Icons pro Bereich



---

💡 Voraussetzungen

Komponente	Details

Ventile	12 V Magnetventile
Steuerung	ESP32 Devkit V1
Kommunikation	LoRa SX1278 Module
Stromversorgung	12 V / 18 Ah Bleiakku + Solar
App	Flutter (Android Debug APK)



---

🚀 Start

1. Knoten bestromen & LoRa einschalten


2. App installieren (smart_garden_app.apk)


3. Per Bluetooth mit Zentrale koppeln


4. Zonen verwalten & Zeitpläne einrichten


---



 
