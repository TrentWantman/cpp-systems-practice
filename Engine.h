#ifndef ENGINE_H
#define ENGINE_H

#include "DoubleCircularBuffer.h"
#include "FuelTank.h"

class Engine
{
private:

    const float maxThrust = 70000000;
    float throttle;
    DoubleCircularBuffer& buffer;
    FuelTank& fuelTank;
    float burnRate = 21450;

public:

    Engine(DoubleCircularBuffer& buffer_, FuelTank& fuelTank_ ): buffer(buffer_), fuelTank(fuelTank_), throttle(0.f){}
    Engine(DoubleCircularBuffer& buffer_, FuelTank& fuelTank_, float throttle_): buffer(buffer_), fuelTank(fuelTank_), throttle(throttle_){}


    void Update(float dt) {
        ReadCommands();
        float fuelNeeded = burnRate * throttle * dt;
        float fuelConsumed = fuelTank.Consume(fuelNeeded);
        if (fuelConsumed < fuelNeeded) {
            throttle = 0.0f;
        }
    }

    void ReadCommands() {
        float cmd;
        if (buffer.read(cmd)) {
            SetThrottle(cmd);
        }
    }

    void SetThrottle(float t){
        if (t >= 1.0f){
            throttle = 1.0;
        }
        else if(t <= 0.0f){
            throttle = 0;
        }
        else{
            throttle = t;
        }
    }

    void SetThrust(float thrust) { 
        if (thrust >= maxThrust){
            throttle = 1.0;
        }
        else if(thrust <= 0.0f){
            throttle = 0;
        }
        else{
            throttle = thrust / maxThrust;
        }
    }

    float GetThrottle() const { return throttle; }

    float GetThrust() const { return maxThrust * throttle; }

    float GetBurnRate() const { return burnRate * throttle; }

};

#endif