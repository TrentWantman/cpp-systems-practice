#include "RingBuffer.cpp"
#include <thread>
#include <iostream>
using namespace std;
class SensorUnit {
public:
    string name;
    RingBuffer buffer;
    double s1_, s2_, s3_; //three redundant sensors
    bool faulted = false;
    bool stopped = false;
    double latestVote_;
    mutex mtx_;

    SensorUnit(const string& name) : name(name), buffer(10),  faulted(false), latestVote_(0.0) {}

    double noise() {
        return ((rand() % 100) - 50) * 0.01;  // random value between -0.5 and 0.5
    }

    double update(double s1, double s2, double s3){
        s1_ = s1; s2_ = s2; s3_ = s3;
        return vote();
    }

    double vote(){
        double vote;
        bool oneTwo = abs(s1_ - s2_) <= 0.5;
        bool oneThree = abs(s1_ - s3_) <= 0.5;
        bool twoThree = abs(s2_ - s3_) <= 0.5;
        int totalAgree = (int)oneTwo + (int)oneThree + (int)twoThree;
        if ( totalAgree > 1) {
            vote = (s1_ + s2_ + s3_) / 3;
        }
        else if (totalAgree > 0){
            if (oneTwo) {vote = (s1_ + s2_) / 2;}
            else if (oneThree) {vote = (s1_ + s3_) / 2;}
            else if (twoThree) {vote = (s2_ + s3_) / 2;}
        }
        else{
            faulted = true;
            cout << "WARNING: Sensor Unit Is Faulty: sensor 1: " << s1_ << " sensor 2: " << s2_ << " sensor 3: " << s3_ << endl;
            return -999999.9;
        }
        buffer.push(vote);
        return vote;
    }

    bool isFaulted() {return faulted;}

    void run() {
        // runs on its own thread, continuously updates
        int cycle = 0;
        while (!stopped) {
            // read from hardware (simulated)
            double base = 1000.0 + cycle * 10.0; //altitude increasing
        {
            lock_guard<mutex> lock(mtx_);
            latestVote_ = update(base + noise(), base + noise(), base + noise());
        }
            cycle++;
            this_thread::sleep_until(chrono::steady_clock::now() + chrono::milliseconds(50)); //reads at 20hz
        }
    }

    double getLatestVote() {
        lock_guard<mutex> lock(mtx_);
        return latestVote_;
    }
};