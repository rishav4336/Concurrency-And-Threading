#include<iostream>
#include<thread>
#include<mutex>
#include<deque>
#include<future>


using namespace std;

mutex m;
condition_variable cond;
deque<packaged_task<int()>> q;

int factorial(int n){
    int x = 1;
    for(int i=2;i<=n;i++){
        x = x * i;
    }
    return x;
}

void func(){
    packaged_task<int()> t;
    {
        unique_lock<mutex> locker(m);
        cond.wait(locker, [](){return !q.empty();});
        t = std::move(q.front());
        q.pop_front();
    }
    t();
}


int main() {
    thread t1(func);
    packaged_task<int()> t(bind(factorial, 6));

    future<int> f = t.get_future();
    cond.
    {
        unique_lock<mutex> locker(m);
        q.push_back(std::move(t));
    }
    cond.notify_one();
    cout<<f.get()<<"\n";
    t1.join();
}