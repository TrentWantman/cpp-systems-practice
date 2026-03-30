#include <iostream>
using namespace std;

class DoubleCircularBuffer{
public:
    static const int CAPACITY = 64;
    double bufferA[CAPACITY] = {};
    double bufferB[CAPACITY] = {};
    double* writer = bufferA;
    double* reader = bufferB;
    int writeHead = 0;
    int readHead = 0;
    int writeCount = 0;
    
    bool read(double& out){
        if(readHead >= writeCount){
            return false;
        }
        out = reader[readHead];
        readHead++;
        return true;
    }

    bool write(double val){
        if(writeHead >= CAPACITY){
            return false;
        }
        writer[writeHead] = val;
        writeHead++;
        return true;
    }

    bool swapBuffers(){
        writeCount = writeHead;
        writeHead = 0;
        readHead = 0;
        swap(writer, reader);
    }

};