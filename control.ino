#include <Adafruit_MotorShield.h>
#include <hp_BH1750.h>
#define FRONT_LEFT_MOTOR_TERMINAL 4
#define FRONT_RIGHT_MOTOR_TERMINAL 3
#define BACK_RIGHT_MOTOR_TERMINAL 2
#define BACK_LEFT_MOTOR_TERMINAL 1
#define LEFT_IR_PIN A0
#define RIGHT_IR_PIN A1
#define LEFT_TURN_LED_PIN 6
#define RIGHT_TURN_LED_PIN 5
hp_BH1750 lightSensor;
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *F_L = AFMS.getMotor(FRONT_LEFT_MOTOR_TERMINAL);
Adafruit_DCMotor *F_R = AFMS.getMotor(FRONT_RIGHT_MOTOR_TERMINAL);
Adafruit_DCMotor *B_R = AFMS.getMotor(BACK_RIGHT_MOTOR_TERMINAL);
Adafruit_DCMotor *B_L = AFMS.getMotor(BACK_LEFT_MOTOR_TERMINAL);
int start= -1;
int lux = 0;

void setup() {
  // put your setup code here, to run once:
  lightSensor.begin(BH1750_TO_GROUND);
  pinMode(LEFT_TURN_LED_PIN,OUTPUT);
  pinMode(RIGHT_TURN_LED_PIN,OUTPUT);
  AFMS.begin();
  F_L->setSpeed(0);
  F_L->run(RELEASE);
  F_R->setSpeed(0);
  F_R->run(RELEASE);
  B_L->setSpeed(0);
  B_L->run(RELEASE);
  B_R->setSpeed(0);
  B_R->run(RELEASE);
}

void loop() {
  lightSensor.start();
     
  if (start==1){

    int L_IR = digitalRead(LEFT_IR_PIN); // if 1(black) then off track, if 0(white) then on track
    int R_IR = digitalRead(RIGHT_IR_PIN); 

    if (L_IR && R_IR){//both black stop
      digitalWrite(RIGHT_TURN_LED_PIN,LOW);
      digitalWrite(LEFT_TURN_LED_PIN,LOW);
      straight();
      /*
      if (dir == "L"){
        Serial.print("LEFT");
        turnLeft();
      }else if(dir == "R"){
        Serial.print("RIGHT");
        turnRight();
      }else if(dir == "S"){
        straight();
      }
      */
      }
      else if (R_IR && !L_IR){//if right goes on track
        turnRight();
      }
      else if (!L_IR && !R_IR){
        straight();
      }
      else if (L_IR && !R_IR){//if left goes on track
        turnLeft();
      }
    
  }else{

    changeSpeed(0);
    digitalWrite(RIGHT_TURN_LED_PIN,LOW);
    digitalWrite(LEFT_TURN_LED_PIN,LOW);
    lux = lightSensor.getLux(); 
    if (lux>3000){
      start = 1;  
    } 
    
    
  }
}

void turnLeft(){
  B_R->run(FORWARD);
  F_R->run(FORWARD); 
  B_R->setSpeed(255);
  F_R->setSpeed(255);
  B_L->run(BACKWARD);
  F_L->run(BACKWARD);

  B_L->setSpeed(255);
  F_L->setSpeed(255);
  digitalWrite(LEFT_TURN_LED_PIN,HIGH);
  digitalWrite(RIGHT_TURN_LED_PIN,LOW);
}
void turnRight(){
  B_L->run(FORWARD);
  F_L->run(FORWARD);
  B_L->setSpeed(255);
  F_L->setSpeed(255);
  B_R->run(BACKWARD);
  F_R->run(BACKWARD);
  B_R->setSpeed(255);
  F_R->setSpeed(255);
  digitalWrite(RIGHT_TURN_LED_PIN,HIGH);
  digitalWrite(LEFT_TURN_LED_PIN,LOW);
  
}

void straight(){
  changeSpeed(225);
  B_R->run(FORWARD);
  F_R->run(FORWARD);
  B_L->run(FORWARD);
  F_L->run(FORWARD);
  digitalWrite(RIGHT_TURN_LED_PIN,LOW);
  digitalWrite(LEFT_TURN_LED_PIN,LOW);
}
void changeSpeed(int speed){
  B_R->setSpeed(speed);
  F_R->setSpeed(speed);
  B_L->setSpeed(speed);
  F_L->setSpeed(speed);
}
