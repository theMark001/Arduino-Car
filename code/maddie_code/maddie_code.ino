#include <SoftwareSerial.h>

#define _SMOOTH_PRD 50
#define NORMAL 0
#define REVERSE 1

enum GM_workMode {
    FORWARD,
    BACKWARD,
    STOP,
    BRAKE,
    AUTO = 0,
};

static const int8_t _GM_NC = -1;

class GMotor {
public:
    // Constructor for 3-wire driver: GMotor(dig_pin_A, dig_pin_B, PWM_pin, (LOW/HIGH))
    GMotor(int8_t param1 = _GM_NC, int8_t param2 = _GM_NC, int8_t param3 = _GM_NC, int8_t param4 = _GM_NC) {
        _digA = param1;
        _digB = param2;
        _pwmC = param3;	
        if (param4 != _GM_NC) _level = !param4;

        if (_digA != _GM_NC) pinMode(_digA, OUTPUT);
        if (_digB != _GM_NC) pinMode(_digB, OUTPUT);
        if (_pwmC != _GM_NC) pinMode(_pwmC, OUTPUT);
        
        setMode(STOP);
    }

    void setSpeed(int16_t duty) {
        if (_mode < 2) {  // mode < 2 means FORWARD or BACKWARD, AUTO=0, FORWARD=1, BACKWARD=2
            _duty = constrain(duty, -_maxDuty, _maxDuty);
            if (_maxDuty > 255 && abs(_duty) == 255) _duty++;
            
            if (duty == 0) run(STOP, 0);
            else {
                if (duty > 0) {
                    if (_minDuty != 0) _duty = _duty * _k + _minDuty;
                    run(_mode, _duty);
                } else {
                    if (_minDuty != 0) _duty = _duty * _k - _minDuty;
                    run(BACKWARD, -_duty);
                }
            }
        }
    }

    void setMode(GM_workMode mode) {	
        _mode = mode;
        run(mode, _duty);
    }

    void setDirection(bool direction) {
        _direction = direction;
    }

    void setMinDuty(int duty) {
        _minDuty = duty;
        _k = 1.0 - (float)_minDuty / _maxDuty;
    }

    void setResolution(byte bit) {
        _maxDuty = (1 << bit) - 1;	
        setMinDuty(_minDuty);		
    }

    void setDeadtime(uint16_t deadtime) {
        _deadtime = deadtime;
    }

    void setLevel(int8_t level) {
        _level = !level;
    }

    void smoothTick(int16_t duty) {
        if (millis() - _tmr >= _SMOOTH_PRD) {
            _tmr = millis();
            if (abs(_dutyS - duty) > _speed) _dutyS += (_dutyS < duty) ? _speed : -_speed;
            else _dutyS = duty;
            setSpeed(_dutyS);
        }
    }

    void setSmoothSpeed(uint8_t speed) {
        _speed = speed;
    }

    int getState() {
        return _state;
    }

    int16_t _duty = 0;

protected:
    void run(GM_workMode mode, int16_t duty = 0) {
        if (_deadtime > 0 && _lastMode != mode) {
            _lastMode = mode;
            setPins(_level, _level, 0);
            delayMicroseconds(_deadtime);
        }

        GM_workMode actualMode = mode;
        if (_direction) {
            if (mode == FORWARD) actualMode = BACKWARD;
            else if (mode == BACKWARD) actualMode = FORWARD;
        }

        switch (actualMode) {
        case FORWARD:	
            setPins(_level, !_level, duty); 
            _state = 1; 
            break;		
        case BACKWARD:	
            setPins(!_level, _level, duty); 
            _state = -1; 
            break;
        case BRAKE:		
            setPins(!_level, !_level, !_level * 255); 
            _state = 0; 
            break;	
        case STOP:		
            setPins(_level, _level, _level * 255); 
            _state = 0; 
            break;		
        }
    }

    void setPins(bool a, bool b, int c) {
        if (_digA != _GM_NC) digitalWrite(_digA, a);
        if (_digB != _GM_NC) digitalWrite(_digB, b);
        if (_pwmC != _GM_NC) analogWrite(_pwmC, c);
    }

    int16_t _dutyS = 0;
    int _minDuty = 0, _state = 0;
    int8_t _digA = _GM_NC, _digB = _GM_NC, _pwmC = _GM_NC;
    bool _direction = false;
    int8_t _level = LOW;
    int _maxDuty = 255;
    GM_workMode _mode = FORWARD, _lastMode = FORWARD;
    uint16_t _deadtime = 0;
    uint8_t _speed = 20;
    uint32_t _tmr = 0;
    float _k;
};

// Pins and constants for this particular setup
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

GMotor motorL(LEFT_MOTOR_IN1, LEFT_MOTOR_IN2, LEFT_MOTOR_EN, LEFT_MOTOR_MODE);
GMotor motorR(RIGHT_MOTOR_IN3, RIGHT_MOTOR_IN4, RIGHT_MOTOR_EN, RIGHT_MOTOR_MODE);
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

    int dutyR = constrain(joystickY - joystickX, -MOTOR_MAX, MOTOR_MAX);
    int dutyL = constrain(joystickY + joystickX, -MOTOR_MAX, MOTOR_MAX);

    motorR.setSpeed(dutyR);
    motorL.setSpeed(dutyL);
  }
}

void parsing() {
  while (BTserial.available() > 0) {
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