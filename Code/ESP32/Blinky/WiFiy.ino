//Imports
#include "esp_sleep.h"
#include <WiFi.h>

//Konstanten
#define LED 2
#define TOUCH 4
#define THRESHOLD 15

//Variablen die über Deep Sleep hinausgehen
RTC_DATA_ATTR int versuche = 0;


const char* host = "192.168.2.75";
const char* passwort = "tollesPasswort";

void setup(){
  touchSleepWakeUpEnable(TOUCH, THRESHOLD) ;
  pinMode(LED,  OUTPUT);

  Serial.begin(115200);
  delay(10);

  if (esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_TOUCHPAD) {
    Serial.println("Durch Berührung aufgewacht!");
    digitalWrite(LED, HIGH);
    delay(1000);
    digitalWrite(LED, LOW);
  }
  
  WiFi.begin("rad_kitchen", "fancy-flachdach.de");
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  
  Serial.print("\nVerbindung aufgebaut zu rad_kitchen mit ESP32-IP: ");
  Serial.println(WiFi.localIP());
  delay(200);
}

//Schauen ob Kabel berührt wird:
bool getTouch(){
  return (touchRead(TOUCH) < THRESHOLD);
}

void loop(){

  WiFiClient client;
  const int httpPort = 80;
  int erg;

  while(erg != 1){
    Serial.print("\nVerbindungsaufbau zu Server: ");
    Serial.print(host); 

     erg = client.connect(host, httpPort);
     if(!erg){
      versuche++;
      Serial.print("\nVerbindungsaufbau nicht möglich! Versuch Nr: ");
      Serial.print(versuche);
  
      if (versuche > 3) {
        Serial.print("\nVerbindungsaufbau nicht möglich. \nIch versuche es bei Berührung nochmal! ");
        client.stop();    
        WiFi.disconnect();
        esp_deep_sleep_start();
      }
    }
    delay(100);
  }

  String url = "/Touch/input/?pw=";
  url += passwort;
  url += "&wert=1";

  Serial.print("Folgende URL wird aufgerufen: ");
  Serial.println(host + url);

  client.print(String("GET ")+url+" HTTP/1.1\r\n"+"Host: "+host+"\r\n"+"Connection: close\r\n\r\n");

  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println("Timeout!");
      Serial.println("Uebergabe klappt nicht, ich versuche es bei der nächsten Berührung!");
      client.stop();
      WiFi.disconnect(); 
      esp_deep_sleep_start();
    }
  }

  while(client.available()){
    Serial.println("Rückgabe vom Server: ");
    Serial.print(client.readStringUntil('\r'));  
  }

  client.stop();
  WiFi.disconnect(); 
  Serial.println("\nVerbindung beendet");
  client.stop();
  WiFi.disconnect(); 
  Serial.println("\nVerbindung beendet");

   Serial.print("Schlafe jetzt bis zur nächsten Berührung.");
   esp_deep_sleep_start();
}
