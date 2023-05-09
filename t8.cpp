#include<iostream>
#include<thread>

using namespace std;

class A {
public:
    A(int x) { }
    void f(int x, char c) { }
    void g(int x) { return x; }
    void operator() (int x)  { return x*2; }
};

void foo(int x) {

}

int main() {
    A a;
    thread t1(a, 6); // copy of a in different thread
    thread t2(ref(a), 5); // a() in different thread
    thread t3(A(), 5); // Teamp A()
    thread t4(move(a), 6); // can't be used further since a is moved to child thread
    thread t5([](int x){return x*x;}, 6); // ibuilt lambda function
    thread t6(foo, 7);
    thread t7(&A::f, a, 8, 'w'); // calling function f of A by making copy of a in different thread
    thread t8(&A::f, &a, 8, 'l'); // Calling function f of A like a.f(8, 'l') in different thread
}