#ifndef WORLD_H
#define WORLD_H

#include "Rocket.h"

class World {
private:
    Rocket rocket;
    Vec3 gravity;

public:
    World() : rocket(), gravity(0, 0, -9.8f) {}

    void Step(float dt) {
        Vec3 forces = gravity * rocket.GetMass();
        rocket.Update(forces, dt);
    }

    const Rocket& GetRocket() const { return rocket; }
    Rocket& GetRocket() { return rocket; }
};

#endif