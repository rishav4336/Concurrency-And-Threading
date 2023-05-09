#include <iostream>
#include <thread>
#include <mutex>
#include <semaphore.h>
using namespace std;

// Set the capacity of the bathroom
const int bathroom_capacity = 3;

// Create the semaphores
sem_t male_mutex, female_mutex, bathroom_mutex;

// Initialize counters for male and female
int male_count = 0, female_count = 0;

// Function to represent male using the bathroom
void male_use_bathroom(int id) {
    sem_wait(&male_mutex);
    male_count++;
    if (male_count == 1) {
        sem_wait(&bathroom_mutex);
    }
    sem_post(&male_mutex);

    // Enter the bathroom
    sem_wait(&bathroom_mutex);
    cout << "Male " << id << " is using the bathroom" << endl;
    this_thread::sleep_for(chrono::seconds(2));
    cout << "Male " << id << " is done using the bathroom" << endl;
    sem_post(&bathroom_mutex);

    // Exit the bathroom
    sem_wait(&male_mutex);
    male_count--;
    if (male_count == 0) {
        sem_post(&bathroom_mutex);
    }
    sem_post(&male_mutex);
}

// Function to represent female using the bathroom
void female_use_bathroom(int id) {
    sem_wait(&female_mutex);
    female_count++;
    if (female_count == 1) {
        sem_wait(&bathroom_mutex);
    }
    sem_post(&female_mutex);

    // Enter the bathroom
    sem_wait(&bathroom_mutex);
    cout << "Female " << id << " is using the bathroom" << endl;
    this_thread::sleep_for(chrono::seconds(2));
    cout << "Female " << id << " is done using the bathroom" << endl;
    sem_post(&bathroom_mutex);

    // Exit the bathroom
    sem_wait(&female_mutex);
    female_count--;
    if (female_count == 0) {
        sem_post(&bathroom_mutex);
    }
    sem_post(&female_mutex);
}

int main() {
    // Initialize the semaphores
    sem_init(&male_mutex, 0, 1);
    sem_init(&female_mutex, 0, 1);
    sem_init(&bathroom_mutex, 0, bathroom_capacity);

    // Create threads for male and female
    thread male_threads[10], female_threads[10];
    for (int i = 0; i < 3; i++) {
        male_threads[i] = thread(male_use_bathroom, i+1);
        female_threads[i] = thread(female_use_bathroom, i+1);
    }

    // Join the threads
    for (int i = 0; i < 3; i++) {
        male_threads[i].join();
        female_threads[i].join();
    }

    // Destroy the semaphores
    sem_destroy(&male_mutex);
    sem_destroy(&female_mutex);
    sem_destroy(&bathroom_mutex);

    return 0;
}
