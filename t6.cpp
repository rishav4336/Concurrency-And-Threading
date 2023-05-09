#include<iostream>
#include<thread>
#include<mutex>
#include<deque>

using namespace std;

deque<int> q;
mutex m;
condition_variable cond;

void func1() {
    int count = 10;
    while(count>0){
        unique_lock<mutex> locker(m);
        q.push_front(count);
        locker.unlock();
        this_thread::sleep_for(chrono::seconds(1));
        cond.notify_one();
        count--;
    }
}

void func2() {
    int data = 0;
    while(data != 1) {
        unique_lock<mutex> locker(m);
        cond.wait(locker, [](){ return !q.empty();});
        data = q.back();
        q.pop_back();
        locker.unlock();
        cout<<"T2 got he data: "<<data<<"\n";
    }
}

int main() {
    thread t1(func1);   
    thread t2(func2);

    t1.join();
    t2.join();

    return 0;
}