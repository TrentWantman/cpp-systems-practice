#include "FlightComputer.cpp"
int main() {
    FlightComputer fc;
    // fc.run();
    Vec3 pos(0.0f, 0.0f, 1000.0f);
    Vec3 vel(100.0f, 0.0f, 50.0f);
    Vec3 gravity(0.0f, 0.0f, -9.81f);
    float dt = 0.1f;

    for (int i = 0 ;i < 100; i++){
        vel = vel + gravity * dt;
        pos = pos + vel * dt;

        pos.print();
    }
    return 0;
}