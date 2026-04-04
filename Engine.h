class Engine
{
private:

    const float maxThrust = 70000000;
    float throttle;

public:

    Engine() : throttle(0.f){}

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

};

