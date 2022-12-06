#define PIN_RECIVER 1
#define PIN_LED 0
#define REQUEST_DEVICE_ID 0x12
#define RELE1_PIN 4
#define RELE2_PIN 5
#define RELE3_PIN 6
#define RELE4_PIN 7

#define MOVE_SENSOR_PIN 14

#include <setting.h>
#include <RCSwitch.h>
//
//#define RELE_OFF HIGH
//#define RELE_ON LOW



RCSwitch mySwitch = RCSwitch();

bool onSensorMove = false;
bool flagSensorMove = false;
unsigned long sensorMoveTimer = 0;
uint32_t sensorMoveInterval = 10000;


void setup() {
  
  mySwitch.enableReceive(PIN_RECIVER);
  pinMode(RELE1_PIN, OUTPUT);
  pinMode(RELE2_PIN, OUTPUT);
  pinMode(MOVE_SENSOR_PIN, INPUT);
  digitalWrite(RELE1_PIN, RELE_OFF);
  digitalWrite(RELE2_PIN, RELE_OFF);
}

void loop() {
  
  uint32_t data;
  if(mySwitch.available()){
    digitalWrite(PIN_LED, HIGH);
    data = mySwitch.getReceivedValue();
    mySwitch.resetAvailable();
  
    if(byte(data >> 24) == REQUEST_SERVER_ID && byte(data >> 16) == REQUEST_DEVICE_ID){
      if(byte(data >> 8) == REQUEST_TYPE_RELE){
        if(byte(data) == REQUEST_RELE1_ON){
        
          if(digitalRead(RELE1_PIN) == RELE_OFF) digitalWrite(RELE1_PIN, RELE_ON);
          if(onSensorMove){
            flagSensorMove = true;
            sensorMoveTimer = millis();
          }
        }
        if(byte(data) == REQUEST_RELE1_OFF){
          if(digitalRead(RELE1_PIN) == RELE_ON) digitalWrite(RELE1_PIN, RELE_OFF);
          if(onSensorMove) flagSensorMove = false;
        }  

        //================================
        if(byte(data) == REQUEST_RELE2_ON){
        
          if(digitalRead(RELE2_PIN) == RELE_OFF) digitalWrite(RELE2_PIN, RELE_ON);
          if(onSensorMove){
            flagSensorMove = true;
            sensorMoveTimer = millis();
          }
        }
        if(byte(data) == REQUEST_RELE2_OFF){
          if(digitalRead(RELE2_PIN) == RELE_ON) digitalWrite(RELE2_PIN, RELE_OFF);
          if(onSensorMove) flagSensorMove = false;
        }      
        //================================
        
      }
      if(byte(data >> 8) == REQUEST_TYPE_MOVE_SENSOR){
        if(byte(data) == REQUEST_MOVE_SENSOR_ON) onSensorMove = true;
        else if(byte(data) == REQUEST_MOVE_SENSOR_OFF) onSensorMove = false;
        else sensorMoveInterval = uint32_t(byte(data)) * 1000;
      }
    }
    delay(50);
    digitalWrite(PIN_LED, LOW);
  }
  
  if(onSensorMove){
    if(!flagSensorMove && digitalRead(MOVE_SENSOR_PIN) == HIGH){
        if(digitalRead(RELE1_PIN) == RELE_OFF) digitalWrite(RELE1_PIN, RELE_ON);
        flagSensorMove = true;
        sensorMoveTimer = millis();
        delay(100);
        return;
    }
    if(flagSensorMove){
      if(millis() - sensorMoveTimer >= sensorMoveInterval){
        flagSensorMove = false;
        if(digitalRead(RELE1_PIN) == RELE_ON) digitalWrite(RELE1_PIN, RELE_OFF);
        delay(100);
        return;
      }
    }
  }
}
