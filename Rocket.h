#include "Mat3x3.h"
#include "Engine.h"

class Rocket{
private:
    Mat3x3 orientation;
    float mass;
    Vec3 forward;
    Vec3 position;
    Vec3 velocity;
    Engine engine;

public:
    Rocket() : orientation(), mass(1000.0f), forward(0,0,1), position(0,0,0), velocity(0,0,0), engine() {};
    void Update(Vec3 externalForces, float dt);
    void Rotate(Mat3x3 rotation);
    
    void Update(Vec3 externalForces, float dt) {
        Vec3 thrustDirection = orientation * forward;
        Vec3 thrustForce = forward * engine.GetThrust();
        Vec3 acceleration = (thrustForce + externalForces) * (1.0f / mass);
        velocity = velocity + acceleration * dt;
        position = position + velocity * dt;
    }

    void Print() const {
        printf("Rocket State\n");
        printf("Position: ");
        position.Print();
        printf("Velocity: ");
        velocity.Print();
        printf("Mass: %f\n", mass);
        printf("Throttle: %f\n", engine.GetThrottle());
        printf("Thrust Direction: ");
        (orientation * forward).Print();
        printf("Orientation:\n");
        orientation.Print();
    }
};