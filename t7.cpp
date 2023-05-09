#include<iostream>
#include<thread>
#include<mutex>
#include<deque>
#include<future>


using namespace std;

mutex m;
condition_variable cond;

int fact(future<int>& fu){

    // unique_lock<mutex> locker(m);
    int res = 1;
    int n = fu.get();
    for(int i=2;i<=n;i++){
        res = res * i;
    }

    // x = res;
    // locker.unlock();
    // cond.notify_one();
    return res;
}
int main() {
    int x = 4;
    // thread t1(fact, 5, ref(x));
    // unique_lock<mutex> locker(m);
    // cond.wait(locker);
    // t1.join();

    promise<int> p;
    future<int> f = p.get_future();

    future<int> ans = async(launch::async, fact, ref(f));
    p.set_value(6);

    cout<<ans.get()<<"\n";
}