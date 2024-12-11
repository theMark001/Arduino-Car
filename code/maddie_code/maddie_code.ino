/*
  Проект: Bluetooth-машинка на Arduino
  Настроен под использование драйвера L298N (DRIVER3WIRE) и Bluetooth-модуля.
  Исходная логика взята из примера AlexGyver (BluetoothCar), адаптирована под L298N.
  
  Схема и логику см. в описании выше.
  Работает так:
  - Ардуино принимает через Bluetooth команды от джойстика в формате: "$X Y;"
  - X и Y - целочисленные значения координат джойстика.
  - По принятым X/Y рассчитываются скорости моторов и отправляются в драйвер через GyverMotor.
*/

#include <Arduino.h>
#include <SoftwareSerial.h>
#include "GyverMotor.h"

/*============= НАСТРОЙКИ =============*/
#define MOTOR_MAX 255                 // максимальный ШИМ сигнал на мотор (0-255)
#define JOY_MAX 40                    // максимальное значение джойстика по X и Y от приложения
#define minDuty 0                     // минимальный ШИМ, с которого мотор начинает крутиться
#define RIGHT_MOTOR_DIRECTION NORMAL  // направление правого мотора (NORMAL или REVERSE)
#define LEFT_MOTOR_DIRECTION NORMAL   // направление левого мотора (NORMAL или REVERSE)
#define RIGHT_MOTOR_MODE HIGH         // смени HIGH на LOW, если нужно инвертировать уровень драйвера
#define LEFT_MOTOR_MODE HIGH          // смени HIGH на LOW, если нужно инвертировать уровень драйвера

/*=============== ПИНЫ ===============*/
// Левый мотор (подключен к выходам OUT1/OUT2 L298N)
#define LEFT_MOTOR_IN1 2
#define LEFT_MOTOR_IN2 4
#define LEFT_MOTOR_EN  3  // ШИМ пин для ENA

// Правый мотор (подключен к выходам OUT3/OUT4 L298N)
#define RIGHT_MOTOR_IN3 7
#define RIGHT_MOTOR_IN4 8
#define RIGHT_MOTOR_EN  5  // ШИМ пин для ENB

// Пины для Bluetooth (HC-05 / HC-06)
#define BT_TX 13
#define BT_RX 12

// Инициализация моторов через GyverMotor (DRIVER3WIRE)
GMotor motorL(DRIVER3WIRE, LEFT_MOTOR_IN1, LEFT_MOTOR_IN2, LEFT_MOTOR_EN, LEFT_MOTOR_MODE);
GMotor motorR(DRIVER3WIRE, RIGHT_MOTOR_IN3, RIGHT_MOTOR_IN4, RIGHT_MOTOR_EN, RIGHT_MOTOR_MODE);

// Инициализация SoftwareSerial для Bluetooth
SoftwareSerial BTserial(BT_RX, BT_TX);

boolean doneParsing = false, startParsing = false;
int dataX = 0, dataY = 0;
String string_convert;

void setup() {
  // Запускаем Bluetooth на 9600 бод
  BTserial.begin(9600);

  // Настройка моторов
  motorR.setMode(AUTO);
  motorL.setMode(AUTO);
  motorR.setMinDuty(minDuty);
  motorL.setMinDuty(minDuty);
  motorR.setDirection(RIGHT_MOTOR_DIRECTION);
  motorL.setDirection(LEFT_MOTOR_DIRECTION);

  // При желании можно настроить более высокую частоту ШИМ для D3 и D5
  // Для Nano (таймер 2 - D3, D11):
  // TCCR2B = 0b00000001; // повышение частоты ~62.5kHz на пине 3/11
  // TCCR2A = 0b00000011;
  
  // Для пина D5 (таймер 0), можно настроить иначе, но по умолчанию частота тоже подойдет.
}

void loop() {
  parsing();         // функция парсинга
  if (doneParsing) { // если получены данные
    doneParsing = false;

    int joystickX = map(dataX, -JOY_MAX, JOY_MAX, -MOTOR_MAX / 2, MOTOR_MAX / 2);
    int joystickY = map(dataY, -JOY_MAX, JOY_MAX, -MOTOR_MAX, MOTOR_MAX);

    int dutyR = joystickY - joystickX; // поменяли местами X при вычислении dutyR и dutyL
    int dutyL = joystickY + joystickX; 

    dutyR = constrain(dutyR, -MOTOR_MAX, MOTOR_MAX);
    dutyL = constrain(dutyL, -MOTOR_MAX, MOTOR_MAX);

    motorR.setSpeed(dutyR);
    motorL.setSpeed(dutyL);
  }
}

void parsing() {
  // Непрерывно слушаем последовательный порт Bluetooth
  if (BTserial.available() > 0) {
    char incomingChar = BTserial.read();
    if (startParsing) {
      if (incomingChar == ' ') {
        // Прочитали значение X
        dataX = string_convert.toInt();
        string_convert = "";
      } else if (incomingChar == ';') {
        // Прочитали значение Y
        dataY = string_convert.toInt();
        string_convert = "";
        startParsing = false;
        doneParsing = true; // готово к обработке
      } else {
        // Набираем символы в строку, пока не встретим разделитель
        string_convert += incomingChar;
      }
    }
    if (incomingChar == '$') {
      // Начало пакета
      startParsing = true;
      string_convert = "";
    }
  }
}