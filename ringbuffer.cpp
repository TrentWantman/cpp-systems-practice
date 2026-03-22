// Implement a RingBuffer class with fixed capacity. No dynamic allocation after construction. This is how software stores the last N sensor readings without ever calling new in the hot path.
// Requirements:

// Constructor takes a capacity
// push(double value) - add a value. If full, overwrite the oldest
// pop() - remove and return the oldest value
// isEmpty() and isFull() - status checks
// All operations O(1)
// No dynamic allocation after construction

#include <iostream>
using namespace std;

class RingBuffer{
public:
    int capacity_;
    double* buffer;
    int head;
    int tail;
    int count_;

    RingBuffer(const int&  capacity){
        buffer = new double[capacity];
        capacity_ = capacity;
        for (int i = 0; i < capacity_; i++){
            buffer[i] = 0;
        }
        head = 0; count_=0; tail = 0;
    }

    ~RingBuffer(){
        delete[] buffer;
        buffer = nullptr;
        capacity_ = 0;
    }

    bool isEmpty() { return count_ == 0; }
    bool isFull() { return count_ == capacity_; }

    void push(const double& value){
        if(isFull()){ head = (head+1) % capacity_;}
        else{count_++;}
        buffer[tail] = value;
        tail = (tail+1)% capacity_;
    }

    double pop(){
        if(isEmpty()){ cout << "Buffer is empty" << endl; return -1;}
        else{ count_--;}
        double temp = buffer[head];
        buffer[head] = 0;
        head = (head+1) % capacity_;
        return temp;
    }
    
};

int main(){
    RingBuffer rb(3);
    rb.push(1.0);
    rb.push(3.0);
    rb.push(2.0);
    rb.push(2.0);
    rb.push(1.0);
    rb.push(2.0);
    rb.push(3.0);

    for (int i = 0; i < rb.capacity_; i++ ){
        cout << rb.buffer[i] << endl;
    }
    cout << "\n" << endl;
    cout << "Head to tail" << endl;
    cout << "\n" << endl;
    cout << rb.pop() << endl;
    cout << rb.pop() << endl;
    cout << rb.pop() << endl;
    cout << rb.pop() << endl;
}