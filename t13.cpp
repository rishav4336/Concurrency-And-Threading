#include<iostream>
#include<semaphore.h>
#include<thread>
#include<vector>

using namespace std;

sem_t empty = 1;
sem_t male = 1;
sem_t female = 1;
sem_t male_count = 3;
sem_t female_count = 3;
sem_t turns = 1;

int fcount = 0, mcount = 0;

void femaleB(int id) {
    sem_wait(&turns);
    sem_wait(&female);
    fcount = fcount + 1;
    if(fcount == 1){
        sem_wait(&empty);
    }
    sem_post(&female);
    sem_post(&turns);

    sem_wait(&female_count);

    cout<<"Female with id: "<<id<<" enters bathroom\n";
    this_thread::sleep_for(std::chrono::seconds(1));
    sem_post(&female_count);

    sem_wait(&female);
    fcount = fcount - 1;
    if(fcount == 0){
        sem_post(&empty);
    }
    sem_post(&female);
}

void maleB(int id) {
    sem_wait(&turns);
    sem_wait(&male);
    mcount = mcount + 1;
    if(mcount == 1){
        sem_wait(&empty);
    }
    sem_post(&male);
    sem_post(&turns);

    sem_wait(&male_count);

    cout<<"Male with id: "<<id<<" enters bathroom\n";
    this_thread::sleep_for(std::chrono::seconds(1));
    sem_post(&male_count);

    sem_wait(&male);
    mcount = mcount - 1;
    if(mcount == 0){
        sem_post(&empty);
    }
    sem_post(&male);
}


int main() {
    vector<std::thread> mth;
    vector<thread> fth;

    for(int i=0;i<5;i++){
        thread mt(maleB, i+1);
        thread ft(femaleB, i+1);
        mth.push_back(std::move(mt));
        fth.push_back(std::move(ft));
    }

    for(int i=0;i<5;i++){
        mth[i].join();
        fth[i].join();
    }
}