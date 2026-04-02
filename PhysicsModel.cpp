#include "PhysicsModel.h"

    
Vec3 PhysicsModel::GetPosition() const{
    return position;
}

Vec3 PhysicsModel::GetVelocity() const{
    return velocity;
}

Vec3 PhysicsModel::GetAcceleration() const{
    return acceleration;
}

void PhysicsModel::SetThrust(Vec3 thrust_){
    thrust = thrust_;
}

void PhysicsModel::SetMass(float mass_){
    mass = mass_;
}

void PhysicsModel::Update(float dt){
    acceleration = thrust * (1.0f / mass) + gravity;
    velocity = velocity + acceleration * dt;
    position = position + velocity * dt;
}