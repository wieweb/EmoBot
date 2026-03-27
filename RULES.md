# RoboterTobias Rules

Diese Datei hält den dauerhaften Projektkontext fest, damit zukünftige Arbeit am Projekt konsistent bleibt.

## Projektziel

`RoboterTobias` ist ein kleiner, freundlicher Roboter fuer Tobias.
Der Fokus liegt auf einem sympathischen Charakter, modularer Technik und einer schrittweisen Entwicklung von einem animierten Kopf zu einem interaktiven Roboter.

## Kernidee

- Der Roboter soll freundlich, ruhig und kindgerecht wirken.
- Das Gesicht auf dem LCD ist ein zentrales Ausdrucksmittel.
- Mechanik, Elektronik und Software sollen modular aufgebaut werden.
- Entscheidungen mit langfristigem Nutzen sind wichtiger als schnelle, unstrukturierte Hacks.

## Systemarchitektur

Das Projekt ist auf zwei Controller ausgelegt:

1. `Brain`
   High-Level-Logik, Sensorik, Entscheidungen, spaetere AI-Anbindung
2. `Head Controller`
   Display, Gesichtsanimationen, Servos, zeitkritische Hardwaresteuerung

Kommunikation zwischen beiden Controllern erfolgt ueber `UART`.

## Hardware-Annahmen

- Main Controller: `ESP32-S3 DevKitC-1`
- Head Controller: `ESP32-S3 Super Mini` oder aehnlich kompakte ESP32-S3-Platine
- Display: `1.69" ST7789`, `240x280`, `SPI`
- Servos werden extern mit `5V` versorgt, niemals direkt aus GPIO-Pins
- Alle Komponenten muessen eine gemeinsame `GND`-Verbindung haben

## Aktueller Fokus

Der aktuelle Schwerpunkt liegt auf dem Kopfmodul:

- Gesicht auf LCD anzeigen
- Idle-Animationen fuer Augen und Mund
- spaeter verschiedene Emotions- und Reaktionszustande
- Vorbereitung fuer Servo- und Kommandoansteuerung

## Code-Regeln

- Die Codebasis soll modular bleiben.
- Code-Sprache ist english
- `RoboHead.ino` soll nur die Steuerung und Initialisierung enthalten.
- Display-bezogene Logik gehoert in `display.*`.
- Gesichtsanimationen gehoeren in eigene Module wie `face_idle.*`, spaeter z. B. `face_happy.*`.
- Hardware-Konstanten gehoeren in zentrale Header wie `pins.h` und `colors.h`.
- Keine Pin- oder Farbwerte mehrfach hart im Code verteilen.
- Neue Features sollen bestehende Struktur erweitern, nicht wieder zu einer grossen Monolith-Datei fuehren.

## Verhaltensregeln fuer das Gesicht

- Animationen sollen weich, lesbar und sympathisch wirken.
- Bewegungen eher ruhig als hektisch.
- Idle-Verhalten soll lebendig wirken, aber nicht nervoes.
- Gesichtsausdruecke sollen technisch einfach, aber emotional klar sein.

## Entwicklungsregeln

- Kleine, klar getrennte Schritte bevorzugen.
- Bestehende Hardware-Annahmen nicht stillschweigend aendern.
- Vor neuen Pins, Servos oder Displays zuerst zentrale Konfigurationsdateien anpassen.
- Bei neuen Gesichtsmodi immer pruefen, ob sie als eigenes Modul statt als Sonderfall in bestehendem Code umgesetzt werden sollten.
- Timing fuer Display und Animationen moeglichst nicht mit blockierendem `delay()` loesen.

## Langfristige Richtung

Das Projekt soll in dieser Reihenfolge wachsen:

1. Stabiles LCD-Gesicht
2. Kopfbewegung mit Servos
3. Kommandos zwischen Brain und Head Controller
4. Sensorik wie Kamera und Mikrofone
5. Interaktives Verhalten und spaetere AI-Funktionen

## Bei zukuenftigen Aenderungen immer beachten

- Das Projekt ist ein persoenlicher Roboter fuer Tobias, kein generisches Demo-Projekt.
- Freundlicher Charakter und Wartbarkeit sind wichtiger als moeglichst komplexe Features.
- Neue Struktur soll auf dem vorhandenen modularen Aufbau aufsetzen.
