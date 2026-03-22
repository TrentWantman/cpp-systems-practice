#include <unordered_set>
#include <unordered_map>
class LaunchSequence{
public:
    enum State {IDLE, PRELAUNCH, IGNITION, LIFTOFF, MAX_Q, MECO, LANDING, SAFED, ABORT};
    State currentState;
    unordered_map<int, unordered_set<int>> transitions;

    LaunchSequence() {
        transitions[IDLE] = {PRELAUNCH, ABORT};
        transitions[PRELAUNCH] = {IGNITION, ABORT};
        transitions[IGNITION] = {LIFTOFF, ABORT};
        transitions[LIFTOFF] = {MAX_Q, ABORT};
        transitions[MAX_Q] = {MECO, ABORT};
        transitions[MECO] = {LANDING, ABORT};
        transitions[LANDING] = {SAFED, ABORT};
        transitions[SAFED] = {ABORT};
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
            case MAX_Q : return "MAX_Q";
            case MECO : return "MECO";
            case LANDING : return "LANDING";
            case SAFED : return "SAFED";
            case ABORT : return "ABORT";
            default: return "UKNOWN";
        }
    }

    string getState(){
        return stateName(currentState);
    }
};