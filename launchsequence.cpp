// Implement a LaunchSequence state machine
// States: IDLE → PRELAUNCH → IGNITION → LIFTOFF
// ABORT is reachable from any state.
// Requirements:

// Class called LaunchStateMachine
// Stores the current state
// transition(State next) - only allows valid transitions. Invalid transitions print an error and stay in current state
// getState() - returns current state as a string
// Valid transitions: IDLE->PRELAUNCH, PRELAUNCH->IGNITION, IGNITION->LIFTOFF, any->ABORT
// Once in ABORT or LIFTOFF, no further transitions allowed (terminal states)
#include <iostream>
#include <unordered_set>
using namespace std;

class LaunchSequence{
public:
    enum State {IDLE, PRELAUNCH, IGNITION, LIFTOFF, ABORT};
    State currentState;
    unordered_map<int, unordered_set<int>> transitions;

    LaunchSequence() {
        transitions[IDLE] = {PRELAUNCH, ABORT};
        transitions[PRELAUNCH] = {IGNITION, ABORT};
        transitions[IGNITION] = {LIFTOFF, ABORT};
        transitions[LIFTOFF] = {};
        transitions[ABORT] = {};
        currentState = IDLE;
    }

    void transition(State nextState){
        if (transitions[currentState].count(nextState)){
            string prevState = stateName(currentState);
            currentState = nextState;
            cout << "SUCCESS: State transitioned - " << prevState << " -> " << stateName(currentState) << endl; 
        }
        else{
            cout << "ERROR: Not a valid state transition - " << stateName(currentState) << " -> " << stateName(nextState) << endl; 
        }
    }

    string stateName(State s){
        switch (s) {
            case IDLE : return "IDLE";
            case PRELAUNCH : return "PRELAUNCH";
            case IGNITION : return "IGNITION";
            case LIFTOFF : return "LIFTOFF";
            case ABORT : return "ABORT";
            default: return "UKNOWN";
        }
    }

    string getState(){
        return stateName(currentState);
    }
};

int main() {
    LaunchSequence rocket;
    cout << rocket.getState() << endl;
    rocket.transition(LaunchSequence::PRELAUNCH);
    rocket.transition(LaunchSequence::IGNITION);
    rocket.transition(LaunchSequence::LIFTOFF);
    rocket.transition(LaunchSequence::ABORT);  // should fail

    // skipping a state
    LaunchSequence rocket2;
    rocket2.transition(LaunchSequence::IGNITION);  // should fail - can't skip PRELAUNCH

    // abort from mid-sequence
    LaunchSequence rocket3;
    rocket3.transition(LaunchSequence::PRELAUNCH);
    rocket3.transition(LaunchSequence::ABORT);
    rocket3.transition(LaunchSequence::IDLE);  // should fail - ABORT is terminal
    return 0;
}