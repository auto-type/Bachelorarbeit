Teil von [1][Vorgehensweise#^d22303]

1. Arduino IDE runterladen:  https://docs.arduino.cc/software/ide/
2. Entsprechende Pinouts sind auf der [Herstellerseite](https://joy-it.net/en/products/SBC-NodeMCU-ESP32-C) zu finden (*falls nötig*)
3. Tutorial für Basic Setup auf deutsch: https://www.mikrocontroller-elektronik.de/nodemcu-esp8266-tutorial-wlan-board-arduino-ide/
		Man muss natürlich beachten, dass das Tutorial für ein NodeMCU geschrieben ist also für einen ESP8266 Chip, die meisten Funktionen lassen sich jedoch sehr einfach übertragen. Außerdem wird in dem Tutorial ein Temperaturmessgerät implementiert. 
4.  Entsprechende Befehle zum Beispiel hier: [deep blue embedded](https://deepbluembedded.com/esp32-wifi-library-examples-tutorial-arduino/) oder in den jeweiligen Docs zu finden
5. `pip install fastapi` als API zum abrufen der vom ESP32 gesendeten Daten
6.  `pip install "uvicorn[standard]"` als Server auf dem die FastApi läuft
7. `main.py` schreiben als Skript für den Server
8. `uvicorn main:app --reload` startet den Server
9. Im Browser kann man über die ip `127.0.0.1:8000/docs` die API Informationen abrufen; bzw wie in Postman requests an die API abschicken
10. [fastapi docs](https://fastapi.tiangolo.com/tutorial/body/) und Tutorial
