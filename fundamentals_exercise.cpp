// ============================================================================
// C++ FUNDAMENTALS EXERCISE
// ============================================================================
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <algorithm>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <cassert>

using namespace std;

// ============================================================================
// SECTION 1: BUILD A CLASS FROM SCRATCH
// ============================================================================
// This class manages a resource (heap memory), which means the compiler's
// default copy/move/destructor will do the wrong thing. You need to write
// them yourself. That's the Rule of Five.

class SensorBuffer {
private:
    double* data_;
    size_t  size_;
    string  name_;

public:
    SensorBuffer(const string& name, size_t size) {
        name_ = name;
        size_ = size;
        data_ = new double[size];
        for (size_t i = 0; i < size_; i++){
            data_[i] = 0.0;
        }
        cout << "SensorBuffer " << name_ << " constructed with " << size_ << " elements " << endl;
    }

    ~SensorBuffer() {
        if(data_ != nullptr){
                delete[] data_;
        }
        cout << "SensorBuffer " << name_ << " destoryed" << endl;
    }

    SensorBuffer(const SensorBuffer& other) {
        name_ = other.name_;
        size_ = other.size_;
        data_ = new double[size_];
        for (size_t i = 0; i < size_; i++){
            data_[i] = other.data_[i];
        }
        cout << "SensorBuffer " << name_ << " copy constructed from " << other.name_ << endl;
    }

    SensorBuffer& operator=(const SensorBuffer& other) {
        if (this == &other) return *this;
        delete[] this->data_;
        data_ = new double[other.size_];
        for(size_t i = 0; i < other.size_; i++){
            data_[i] = other.data_[i];
        }
        name_ = other.name_;
        size_ = other.size_;
        cout<<"SensorBuffer " << name_ << " copy assigned from " << other.name_ << endl;
        return *this;
    }

    SensorBuffer(SensorBuffer&& other) noexcept {
        data_ = other.data_;
        other.data_ = nullptr;
        name_ = std::move(other.name_);
        size_ = other.size_;
        other.size_ = 0;
        cout << "SensorBuffer " << name_ << " move constructed from " << other.name_ << endl;
    }

    SensorBuffer& operator=(SensorBuffer&& other) noexcept {
        if (this == &other) return *this;
        delete[] this->data_;
        this->size_ = other.size_;
        this->name_ = std::move(other.name_);
        this->data_ = other.data_;
        other.data_ = nullptr;
        other.size_ = 0;
        cout << "SensorBuffer " << this->name_ << " move assigned from " << other.name_ << endl;
        return *this;
    }

    void set(size_t index, double value) {
        if(index < size_){
            data_[index] = value;
        }
    }

    double get(size_t index) const {
        if(index < size_){
            return data_[index];
        }
        return -1.0;
    }

    size_t getSize() const {
        return this->size_;
    }

    const string& getName() const {
        return this->name_;
    }

    void print() const {
        cout << name_ << ": [";
        for (size_t i = 0; i < size_; i++) {
            if (i > 0) cout << ", ";
            cout << data_[i];
        }
        cout << "]" << endl;
    }
};


// ============================================================================
// TESTS
// ============================================================================

void testSection1() {
    cout << "\n=== SECTION 1: Basic Construction ===" << endl;

    {
        SensorBuffer buf("IMU_ACCEL", 5);
        buf.set(0, 9.81);
        buf.set(1, 0.02);
        buf.set(2, -0.15);
        buf.print();
    }

    {
        SensorBuffer accel("ACCEL", 3);
        accel.set(0, 1.0);
        accel.set(1, 2.0);
        accel.set(2, 3.0);
    
        SensorBuffer backup = accel;
        backup.set(0, 999.0);
    
        accel.print();
        backup.print();
    }

    {
        SensorBuffer temp("TEMP_SENSOR", 4);
        temp.set(0, 72.5);
        temp.set(1, 73.1);
    
        SensorBuffer moved = std::move(temp);
        moved.print();
    }

    {
        vector<SensorBuffer> sensors;
        sensors.push_back(SensorBuffer("GYRO_X", 100));
        sensors.push_back(SensorBuffer("GYRO_Y", 100));
        sensors.push_back(SensorBuffer("GYRO_Z", 100));
        cout << "Vector has " << sensors.size() << " sensors" << endl;
    }

    {
        SensorBuffer a("PRESSURE", 3);
        a.set(0, 101.3);
        a.set(1, 101.5);
        a.set(2, 101.7);
 
        SensorBuffer b("ALTITUDE", 2);
        b.set(0, 500.0);
        b.set(1, 600.0);
 
        b = a;
        a.set(0, 999.0);
 
        a.print();
        b.print();
    }
 
    {
        SensorBuffer a("THRUST", 3);
        a.set(0, 7600.0);
        a.set(1, 7650.0);
        a.set(2, 7700.0);
 
        SensorBuffer b("DRAG", 2);
        b.set(0, 100.0);
 
        b = std::move(a);
 
        b.print();
    }
}


void testSmartPointers() {
    cout << "\n=== SECTION 3: Smart Pointers ===" << endl;

    std::unique_ptr<SensorBuffer> sensor = make_unique<SensorBuffer>("GPS", 10);
    sensor->print();

    auto moved = std::move(sensor);
    if (!sensor) cout << "Original is now nullptr (as expected)" << endl;
    moved->print();

    auto shared1 = make_shared<SensorBuffer>("GPS", 10);
    cout << "Use count: " << shared1.use_count() << endl;
    auto shared2 = shared1;
    cout << "Use count: " << shared1.use_count() << endl;
}


void testLambdas() {
    cout << "\n=== SECTION 4: Lambdas ===" << endl;

    auto add = [](double a, double b) {return a + b;};
    cout << "3.5 + 2.1 = " << add(3.5, 2.1) << endl;

    vector<double> readings = {3.14, 1.59, 2.65, 3.58, 9.79};
    sort(readings.begin(), readings.end(), [](double a, double b) {return a>b;});
    for (double r : readings) cout << r << " ";
    cout << endl;

    vector<double> values = {1.0, 2.0, 3.0, 4.0, 5.0};
    auto transform = [](vector<double>& v, function<double(double)> fn) {
        for (int i = v.size()-1; i >= 0; i--){
            v[i] = fn(v[i]);
        }
    };
    transform(values, [](double v){return v * v;});
    for (double v : values) cout << v << " ";
    cout << endl;

    vector<double> data = {0.5, 1.2, 0.8, 2.1, 0.3, 1.8};
    double threshold = 1.0;
    int count = 0;
    auto counter = [&count, threshold](double d) {count += d > threshold;};
    for (double d : data) counter(d);
    cout << count << " readings exceeded threshold" << endl;
}


void testConst() {
    cout << "\n=== SECTION 5: Const Correctness ===" << endl;

    int x = 10;
    const int* ptr1 = &x;
    ptr1 = nullptr;

    int y = 10;
    int* const ptr2 = &y;
    *ptr2 = 20;

    auto average = [](const vector<double>& v) { double a = 0; for (double d : v){ a += (d/v.size());} return a; };
    vector<double> data = {1.0, 2.0, 3.0, 4.0, 5.0};
    cout << "Average: " << average(data) << endl;
}


int shared_counter = 0;
mutex counter_mutex;

void incrementCounter(int times) {
    for (int i = 0; i < times; i++) {
        lock_guard<mutex> lock(counter_mutex);
        shared_counter++;
    }
}

void testThreading() {
    cout << "\n=== SECTION 6: Threading ===" << endl;

    shared_counter = 0;
    thread t1(incrementCounter, 100000);
    thread t2(incrementCounter, 100000);
    t1.join();
    t2.join();
    cout << "Counter (should be 200000): " << shared_counter << endl;

    bool ready = false;
    double sensor_value = 0.0;
    mutex mtx;
    condition_variable cv;
    
    auto producer = [&]() {
        this_thread::sleep_for(chrono::milliseconds(500));
        {
            lock_guard<mutex> lock(mtx);
            sensor_value = 42.0;
            ready = true;
            cout << "Producer: sensor value ready" << endl;
        }
        cv.notify_one();
    };
    
    auto consumer = [&]() {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [&]() { return ready; });
        cout << "Consumer: got sensor value = " << sensor_value << endl;
    };
    
    thread prod(producer);
    thread cons(consumer);
    prod.join();
    cons.join();
}


int main() {
    cout << "========================================" << endl;
    cout << " C++ FUNDAMENTALS EXERCISE" << endl;
    cout << "========================================" << endl;

    testSection1();
    testSmartPointers();
    testLambdas();
    testConst();
    testThreading();

    return 0;
}