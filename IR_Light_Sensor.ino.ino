#include <hp_BH1750.h>
#define LED_PIN_RED 6
#define LED_PIN_BLUE 9
#define IR_PIN A0
hp_BH1750 lightSensor;
void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN_BLUE, OUTPUT);
  pinMode(LED_PIN_RED, OUTPUT);
  pinMode(IR_PIN,INPUT);
  Serial.begin(9600);
  lightSensor.begin(BH1750_TO_GROUND);
}

void loop() {
  // put your main code here, to run repeatedly:
  lightSensor.start();
  int lux = lightSensor.getLux();
  int IR_DETECT = digitalRead(IR_PIN) * 1000;
  Serial.print("Lux:");
  Serial.print(lux);
  Serial.print(",IR:");
  Serial.println(IR_DETECT);
/*
  if(!IR_DETECT){
    digitalWrite(LED_PIN_RED,HIGH);
    delay(100);
    digitalWrite(LED_PIN_RED,LOW);
    digitalWrite(LED_PIN_BLUE,HIGH);
    delay(100);
    digitalWrite(LED_PIN_BLUE,LOW);
  }*/
  
}
