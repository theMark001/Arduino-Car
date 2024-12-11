#include <SoftwareSerial.h>
#include "GyverMotor.h"

#define MOTOR_MAX 255             
#define JOY_MAX 40         
#define minDuty 0                
#define RIGHT_MOTOR_DIRECTION NORMAL 
#define LEFT_MOTOR_DIRECTION NORMAL 
#define RIGHT_MOTOR_MODE HIGH       
#define LEFT_MOTOR_MODE HIGH 

#define LEFT_MOTOR_IN1 2
#define LEFT_MOTOR_IN2 4
#define LEFT_MOTOR_EN  3
#define RIGHT_MOTOR_IN3 7
#define RIGHT_MOTOR_IN4 8
#define RIGHT_MOTOR_EN  5
#define BT_TX 13
#define BT_RX 12

GMotor motorL(DRIVER3WIRE, LEFT_MOTOR_IN1, LEFT_MOTOR_IN2, LEFT_MOTOR_EN, LEFT_MOTOR_MODE);
GMotor motorR(DRIVER3WIRE, RIGHT_MOTOR_IN3, RIGHT_MOTOR_IN4, RIGHT_MOTOR_EN, RIGHT_MOTOR_MODE);
SoftwareSerial BTserial(BT_RX, BT_TX);

boolean doneParsing = false;
boolean startParsing = false;
int dataX = 0;
int dataY = 0;
String string_convert;

void setup() {
  motorR.setMode(AUTO);
  motorL.setMode(AUTO);

  motorR.setMinDuty(minDuty);
  motorL.setMinDuty(minDuty);

  motorR.setDirection(RIGHT_MOTOR_DIRECTION);
  motorL.setDirection(LEFT_MOTOR_DIRECTION);

  BTserial.begin(9600);
}

void loop() {
  parsing();
  if (doneParsing) {
    doneParsing = false;

    int joystickX = map(dataX, -JOY_MAX, JOY_MAX, -MOTOR_MAX / 2, MOTOR_MAX / 2);
    int joystickY = map(dataY, -JOY_MAX, JOY_MAX, -MOTOR_MAX, MOTOR_MAX);

    int dutyR = joystickY - joystickX;
    int dutyL = joystickY + joystickX; 

    dutyR = constrain(dutyR, -MOTOR_MAX, MOTOR_MAX);
    dutyL = constrain(dutyL, -MOTOR_MAX, MOTOR_MAX);

    motorR.setSpeed(dutyR);
    motorL.setSpeed(dutyL);
  }
}

void parsing() {
  if (BTserial.available() > 0) {
    char incomingChar = BTserial.read();
    if (startParsing) {
      if (incomingChar == ' ') {
        dataX = string_convert.toInt();
        string_convert = "";
      } else if (incomingChar == ';') {
        dataY = string_convert.toInt();
        string_convert = "";
        startParsing = false;
        doneParsing = true;
      } else {
        string_convert += incomingChar;
      }
    }
    if (incomingChar == '$') {
      startParsing = true;
      string_convert = "";
    }
  }
}