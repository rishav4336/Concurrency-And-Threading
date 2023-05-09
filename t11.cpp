#include<iostream>
#include<thread>
#include<mutex>

using namespace std;
class MyClass {
private:
    string s;
    int char_count;
    int thread_count;
    mutex m;
    condition_variable cond;

    vector<thread> threads;
    vector<thread::id> thread_ids;
    int allowed_thread;
    int next_char;


public:
    MyClass(string s, int c_count, int t_count) {
        this->s = s;
        char_count = c_count;
        thread_count = t_count;
        allowed_thread = 0;
        next_char = 0;
    }

    void run() {
        for(int i=0;i<thread_count;i++){
            cout<<"Thread Creation "<<i<<"\n";
            thread t(&MyClass::print_thread, this);
            thread_ids.push_back(t.get_id());
            threads.push_back(std::move(t));
        }

        for(int i=0;i<thread_count;i++)
            threads[i].join();
    }

    void waitForAllThreadsToInit() {
        while(1){
            if(threads.size() == thread_count)  return;
        }
    }

    void print_thread() {
        while(1){
            waitForAllThreadsToInit();
            unique_lock<mutex> locker(m);
            cond.wait(locker, [&]() { return this_thread::get_id() == thread_ids[allowed_thread]; });
            print_chars();
            allowed_thread = (allowed_thread + 1)%thread_count;

            locker.unlock();
            cond.notify_all();
        }
    }

    void print_chars() {
        cout<<"Thread Id is: "<<this_thread::get_id()<<" : ";
        int print_count = 0;
        while(print_count<char_count){
            cout<<s[next_char];
            next_char = (next_char + 1)%s.length();
            print_count++;
        }
        this_thread::sleep_for(chrono::seconds(1));
        cout<<endl;
    }
};

int main(int argc, char*argv[]){
    if(argc!=4){
        cout<<"Please provide 4 parameters\n - A String, Charactee count, and thread count\n";
        return 1;
    }
    string str = argv[1];
    int char_count = atoi(argv[2]);
    int th_count = atoi(argv[3]);

    MyClass p(str, char_count, th_count);
    p.run();

    return 0;
}