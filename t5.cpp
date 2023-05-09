#include<iostream>
#include<thread>
#include<mutex>
#include<string>
#include<fstream>

using namespace std;

mutex m;

// void sPrint(string msg, int id){
//     std::lock_guard<std::mutex> guard(m);
//     // m.lock();
//     cout<<msg<<" "<<id<<"\n";
//     // m.unlock();
// }

class LogFile {
    mutex m_mutex;
    ofstream f;
public:
    LogFile() {
        f.open("Log.txt");
    }
    void sPrint(string msg, int id){
        std::lock_guard<std::mutex> guard(m_mutex);
        // m.lock();
        f<<msg<<" "<<id<<"\n";
        // m.unlock();
    }
};

void func1(LogFile& log) {
    for(int i=0;i>=-100;i--){
        log.sPrint("From Thread", i);
    }
}

int main() {
    LogFile log;
    thread t1(func1, std::ref(log));

    for(int i=0;i<100;i++){
        log.sPrint("From Main", i);
    }

    t1.join();

}