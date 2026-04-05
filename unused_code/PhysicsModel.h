#ifndef PHYSICSMODEL_H
#define PHYSICSMODEL_H

#include "Vec3.h"
#include "DoubleCircularBuffer.h"
 
//TODO: Owns the physics (position, velocity, thrust, gravity). Sensors read from this, flight computer sends commands to it.
 
class PhysicsModel {

private:
    Vec3 position, velocity, acceleration, thrust, gravity;
    float mass;

public:
    PhysicsModel() : mass(1000.0f), position(0,0,0), velocity(0,0,0), acceleration(0,0,0), thrust(0,0,0), gravity(0,0,-9.8f) {}
    
    Vec3 GetPosition() const;
    Vec3 GetVelocity() const;
    Vec3 GetAcceleration() const;

    void SetThrust(Vec3 thrust_);
    void SetMass(float mass_);
    void Update(float dt);

};
 
#endif