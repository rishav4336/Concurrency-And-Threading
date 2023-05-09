#include<iostream>
#include<thread>
typedef unsigned long long int ull;

using namespace std;

ull odd = 0;
ull even = 0;

ull st = 0;
ull en = 1900000000;

void oddSum(ull st, ull en){
	for(ull i = st; i<= en; i++){
		if(i&1){
			odd += i;
		}
	}
}
void evenSum(ull st, ull en){
	for(ull i = st; i<= en; i++){
		if((i&1)==0){
			even += i;
		}
	}
}

int main() {
	thread t1(oddSum, st, en);
	thread t2(evenSum, st, en);
    // oddSum(st, en);
    // evenSum(st, en);

	t1.join();
	t2.join();

	cout<<odd<<" Odd sum\n";
	cout<<even<<" evenSum\n";
}