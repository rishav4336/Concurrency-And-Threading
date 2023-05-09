#include<iostream>
#include<thread>
#include<mutex>
#include<deque>
#include<future>


using namespace std;

mutex m1;
mutex m2;
int x = 0, y = 0;

void incXY(int& a, mutex& m, char c){
    for(int i=0;i<5;i++){
        m.lock();
        a++;
        cout<<c<<" "<<a<<"\n";
        m.unlock();
        this_thread::sleep_for(chrono::seconds(1));
    }
}

void add(){
    int use = 5;
    int xy = 0;
    while(1){
        int lockRes = try_lock(m1, m2);
        if(lockRes==-1){
            if(x!=0 && y!=0){
                use--;
                xy += x+y;
                x=0;
                y=0;
                cout<<"X+Y = "<<xy<<"\n";
            } else {
                cout<<"X or Y is not 1 "<<x<<" "<<y<<"\n";
                
            }
            m1.unlock();
            m2.unlock();
            if(use==0)  break;
        } else {
            cout<<"Not able to lock\n";
            this_thread::sleep_for(chrono::milliseconds(100));
        }
    }
}

int main() {
    thread t1(incXY, ref(x), ref(m1), 'X');
    thread t2(incXY, ref(y), ref(m2), 'Y');
    thread t3(add);
    t1.join();
    t2.join();
    t3.join();

}