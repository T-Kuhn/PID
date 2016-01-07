/*
  PID.h - a simple PID Controller library for the Arduino platform 
  Created by Tobias Kuhn. Sapporo, December 30, 2015.
  Released into the public domain.
*/

#ifndef PID_h
#define PID_h
#include "Arduino.h"

// - - - - - - - - - - - - - - - - - - -
// - - - - - - - PID CLASS - - - - - - -
// - - - - - - - - - - - - - - - - - - -
class PID
{
    public:
        void begin(float kp, float ki, float kd);
        int update(float pv, bool following);
        void setSetPoint(float sp);
    private:
        float _kp;
        float _kpQuant;
        float _ki;
        float _kiQuant;
        float _kd;
        float _kdQuant;
        float _errorVal;
        float _errorValOLD;
        float _setPoint;
        float _controlVar;
};

#endif














