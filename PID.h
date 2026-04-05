#ifndef PID_H
#define PID_H

class PID {
private:
    float kp, ki, kd;
    float prevError;
    float integral;

public:
    PID(float kp_, float ki_, float kd_)
        : kp(kp_), ki(ki_), kd(kd_), prevError(0.0f), integral(0.0f) {}

    float Compute(float target, float actual, float dt) {
        float error = target - actual;
        integral += error * dt;
        float p = kp * error;
        float i = ki * integral;
        float d = kd * (error - prevError) / dt;
        prevError = error;
        return p + i + d;
    }
};

#endif