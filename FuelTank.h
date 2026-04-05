#ifndef FUELTANK_H
#define FUELTANK_H

class FuelTank{
private:
    const float CAPACITY = 3800000;
    float fuel;

public:
    FuelTank() : fuel(CAPACITY){}

    float GetFuel() const { return fuel; }

    bool IsEmpty() const { return fuel <= 0.0f; }

    float Consume(float amount){
        if (fuel <= 0) return 0;
        if (amount >= fuel) {
            float consumed = fuel;
            fuel = 0;
            return consumed;
        }
        fuel -= amount;
        return amount;
    }
};
#endif