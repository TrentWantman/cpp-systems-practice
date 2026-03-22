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