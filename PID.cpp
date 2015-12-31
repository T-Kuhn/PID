/*
  PID.cpp - a simple PID Controller library for the Arduino platform 
  Created by Tobias Kuhn. Sapporo, December 30, 2015.
  Released into the public domain.
*/

#include "Arduino.h"
#include "PID.h"
#include <math.h>

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
    _kpQuant = _kp * _errorVal;
    _kiQuant += _ki * _errorVal;
    _kdQuant = _errorVal - _errorValOLD;
    res = (int)round(_kpQuant + _kiQuant + _kdQuant);
    //res = (int)round(_kpQuant);
    if(res > 255){
        res =  255;
    }else if(res < -255){
        res = -255;
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





