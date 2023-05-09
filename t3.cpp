// g++ -std=c++11 -pthread t2.cpp 

#include<iostream>
#include<thread>
typedef unsigned long long int ull;

using namespace std;

void foo(int x){
    while(x --> 0){
        cout<<x<<endl;
    }
    this_thread::sleep_for(chrono::seconds(3));
}

int main() {
    thread t1(foo, 10);

    cout<<"Main thread before\n";
    t1.join();
    cout<<"Main thread after\n";
}