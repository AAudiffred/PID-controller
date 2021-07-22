#ifndef _PID_H
#define _PID_H

enum gain
{
    P,
    I,
    D
};

class PID
{
public:
    PID();
    ~PID();
    void setup(float kp, float ki, float kd, float reference, float saturation_value = 100, float acceptable_error = 0.0f);
    void setGains(float kp, float ki, float kd);
    float calculate(float measurement, float dt);
    float getError();
    float getGain(gain type);
    float reference;

private:
    float saturate(float integral);
    float _kp;
    float _ki;
    float _kd;
    float _error_prev;
    float _error;
    float _integral;
    float _saturation;
    float _acceptable_error;
};

#endif // _PID_H
