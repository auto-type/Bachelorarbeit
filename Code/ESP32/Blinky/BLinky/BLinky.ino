/* 
 
#define LED 2
#define TOUCH 4

void setup() {

  Serial.begin(115200);
  pinMode(LED,  OUTPUT);
  delay(1000); // give me time to bring up serial monitor

  Serial.println("Setting up for Touch sensitivity:\n");
}

void loop() {
  
  delay(1000);
  if(touchRead(TOUCH) < 15){
    digitalWrite(LED, HIGH);
    }
  else{
    digitalWrite(LED, LOW);
    }

  Serial.print("Touch sensor: ");
  Serial.println(touchRead(TOUCH));

  
}

*/
