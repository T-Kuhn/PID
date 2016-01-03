/*
  PID.cpp - a simple PID Controller library for the Arduino platform 
  Created by Tobias Kuhn. Sapporo, December 30, 2015.
  Released into the public domain.
*/

#include "Arduino.h"
#include "PID.h"
#include <math.h>
#define PI 3.14159265

// - - - - - - - - - - - - - - - - - - -
// - - - - - - PID BEGIN - - - - - - - -
// - - - - - - - - - - - - - - - - - - -
void PID::begin(float kp, float ki, float kd)
{
    _kp = kp;
    _ki = ki;
    _kd = kd;
}

// - - - - - - - - - - - - - - - - - - -
// - - - - - - PID UPDATE  - - - - - - -
// - - - - - - - - - - - - - - - - - - -
int PID::update(float pv)
// @return: Value from -255~255 for PWM 
{
    int res;
    _errorVal = _setPoint - pv;
    if(abs(_errorVal) > 0.05f){
        if(abs(_errorVal) < 4.0f && abs(_errorVal) > 0.2f){
            if(_errorVal < 0){   //if _errorval is negativ
                _kpQuant = sin(((_errorVal - 3.0f) / 14.0f) * PI) * 50.0f;
                _kiQuant = 0;
                _kdQuant = _kd * (_errorVal - _errorValOLD);
            }else{  //if _errorval is positiv
                _kpQuant = sin(((_errorVal + 3.0f) / 14.0f) * PI) * 50.0f;
                _kiQuant = 0;
                _kdQuant = _kd * (_errorVal - _errorValOLD);
            }
        }else{
            _kpQuant = _kp * _errorVal;
            _kiQuant += _ki * _errorVal;
            _kdQuant = _kd * (_errorVal - _errorValOLD);
        }
        res = (int)round(_kpQuant + _kiQuant + _kdQuant);
        //res = (int)round(_kpQuant);
        if(res > 255){
            res =  255;
        }else if(res < -255){
            res = -255;
        }
    }else{
        res = 0.0f;
    }
    _errorValOLD = _errorVal;
    return res;
}

// - - - - - - - - - - - - - - - - - - -
// - - - - - PID SETSETPOINT - - - - - -
// - - - - - - - - - - - - - - - - - - -
void PID::setSetPoint(float sp)
{
    _setPoint = sp;
}





