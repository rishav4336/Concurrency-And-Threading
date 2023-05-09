// g++ -std=c++11 -pthread t2.cpp 

#include<iostream>
#include<thread>
typedef unsigned long long int ull;

using namespace std;

int myAmount = 0;
mutex m;

void foo() {
    m.lock();
    myAmount++;
    m.unlock();
}

void checkTryLock(int th) {
    for(int i=0;i<100;i++){
        if(m.try_lock()){
            cout<<"Lock Acquired: "<<th<<"\n";
            myAmount++;
            m.unlock();
        }
    }
}

int main() {
    thread t1(checkTryLock, 1);
    thread t2(checkTryLock, 2);

    t1.join();
    t2.join();

    cout<<myAmount<<"\n";

    cout<< std::thread::hardware_concurrency()<<"\n";
}