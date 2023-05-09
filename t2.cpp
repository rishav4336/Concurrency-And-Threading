// Ways to create threads

#include<iostream>
#include<thread>
typedef unsigned long long int ull;

using namespace std;

// 1. Function pointer --> thread t1(func_name, param1, param2, ...)

// 2. Lambda Function


void fun1(int x){
    cout<<x<<" Inside fun\n";
}
int main() {
    auto fun = [](int x){
        while(x-- > 0){
            cout<<x<<endl;
        }
    };
    thread t2(fun, 10);
    thread t1(fun1, 10);
    
    t1.join();
    t2.join();
}