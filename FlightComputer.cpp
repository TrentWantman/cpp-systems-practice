#include "SensorUnit.cpp"
#include "LaunchSequence.cpp"
#include <chrono>
#include <thread>
#include <iostream>
using namespace std;

class FlightComputer {
public:
    void run() {
        // Loop 50 times at 10Hz
        // Each cycle: record start time, do work, record end time
        // Sleep for the remaining time to hit exactly 100ms
        auto cycleTime = chrono::milliseconds(100);
        auto startAllCycles = chrono::steady_clock::now();
        auto start = startAllCycles;
        SensorUnit sensors("SU-10-ALT");
        thread sensorThread(&SensorUnit::run, &sensors);
        LaunchSequence ls;
        ls.transition(ls.PRELAUNCH);
        ls.transition(ls.IGNITION);
        ls.transition(ls.LIFTOFF);

        for (int i = 0; i < 50; i++){
            double alt = sensors.getLatestVote();
            if(ls.getState() == "LIFTOFF"){
                if(alt >= 1200.0) { ls.transition(ls.MAX_Q);}
            }
            else if(ls.getState() == "MAX_Q"){
                if(alt >= 1500.0) { ls.transition(ls.MECO);}
            }

            this_thread::sleep_for(10ms);
            auto end = chrono::steady_clock::now();
            auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start);
            if (elapsed > cycleTime){
                cout << "OVERRUN cycle " << i << ": " << elapsed.count() << "ms" << endl;
            }
            else {
                //this_thread::sleep_until(start + chrono::milliseconds(59)); // sleep most of it
                while (chrono::steady_clock::now() < start + chrono::milliseconds(100)) {
                    // spin burns CPU but guarantees precision
                }
                auto totalCycle = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - start);
                cout << "Cycle " << i << ": State=" << ls.getState() <<  " Altitude: " << alt << "ft" << " work=" << elapsed.count() << "ms total=" << totalCycle.count() << "ms" << endl;
            }
            start = chrono::steady_clock::now();
        }
        cout << "All Cycles " << ": " << "ms total=" << chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - startAllCycles).count() << "ms" << endl;
        sensors.stopped = true;
        sensorThread.join();
    }
};