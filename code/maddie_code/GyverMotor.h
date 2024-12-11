#ifndef GyverMotor_h
#define GyverMotor_h
#include <Arduino.h>
#define _SMOOTH_PRD 50  // smoothTick timer interval in ms

enum GM_driverType {
    DRIVER3WIRE, // three-wire driver (two direction pins + PWM)
};

#define NORMAL 0
#define REVERSE 1

enum GM_workMode {
    FORWARD,
    BACKWARD,
    STOP,
    BRAKE,
    AUTO = 0,
};

static const int8_t _GM_NC = -1;	// not connected

class GMotor {
public:
    // For a 3-wire driver, usage:
    // GMotor motor(DRIVER3WIRE, dig_pin_A, dig_pin_B, PWM_pin, (LOW/HIGH))
    GMotor(GM_driverType type, int8_t param1 = _GM_NC, int8_t param2 = _GM_NC, int8_t param3 = _GM_NC, int8_t param4 = _GM_NC);
    
    // Set speed (0 to maxDuty), supports negative speed for reverse when in AUTO mode
    void setSpeed(int16_t duty);
    
    // Set motor mode: FORWARD, BACKWARD, STOP, BRAKE, or AUTO (for setSpeed)
    void setMode(GM_workMode mode);
    
    // Set rotation direction (NORMAL or REVERSE)
    void setDirection(bool direction);
    
    // Set minimal duty cycle
    void setMinDuty(int duty);
    
    // Set PWM resolution in bits
    void setResolution(byte bit);
    
    // Set deadtime in microseconds (default 0)
    void setDeadtime(uint16_t deadtime);	
    
    // Set driver level (default LOW, logic is inverted internally)
    void setLevel(int8_t level);			
    
    // Smoothly adjust speed to the given duty. Call smoothTick periodically.
    void smoothTick(int16_t duty);
    
    // Set the speed change step for smoothTick
    void setSmoothSpeed(uint8_t speed);	
    
    // Returns -1 if BACKWARD, 1 if FORWARD, 0 if STOP/BRAKE
    int getState();

    // For compatibility with older versions
    void set8bitMode();		
    void set10bitMode();
    
    int16_t _duty = 0;
    
protected:
    void setPins(bool a, bool b, int c);	
    void run(GM_workMode mode, int16_t duty = 0);		
    int16_t _dutyS = 0;
    int _minDuty = 0, _state = 0;
    int8_t _digA = _GM_NC, _digB = _GM_NC, _pwmC = _GM_NC;
    bool _direction = false;
    int8_t _level = LOW;
    int _maxDuty = 255;
    GM_workMode _mode = FORWARD, _lastMode = FORWARD;
    GM_driverType _type;
    uint16_t _deadtime = 0;
    uint8_t _speed = 20;
    uint32_t _tmr = 0;
    float _k;
};
#endif