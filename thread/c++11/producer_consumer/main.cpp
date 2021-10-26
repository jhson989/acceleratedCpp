#include "utils.hpp"
#include <queue>
#include <mutex>
#include <vector>
#include <algorithm> // generate
#include <condition_variable>
#include <cstdlib> // rand
#include <string>
#include <thread>

const int num_data = 50;
const int num_consumers = 6;

void func_producer (std::queue<std::string>* data, std::mutex* m, std::condition_variable* cv) {
    
    for (int i=0; i<num_data; i++) {
        // Produce a random string
        std::vector<char> rand_vec (50+std::rand()%50);
        std::generate (rand_vec.begin (), rand_vec.end (), [] () { 
                    return 'a' + rand()%('z'-'a'+1);
                });
        std::string rand_str (rand_vec.begin (), rand_vec.end ());

        // Issue
        {
            std::unique_lock<std::mutex> ulk (*m);
            data->push (rand_str);
        }

        // Notify a sleeping consumer
        cv->notify_one ();
        printf("Produce %d data\n", i);
        std::this_thread::sleep_for(std::chrono::milliseconds(rand_str.length()));
    }

    printf("Producer done...\n");
    cv->notify_all ();
}

void func_consumer (std::queue<std::string>* data, std::mutex* m, std::condition_variable* cv, int* num_processed) {

    while (*num_processed < num_data) {
    
        int num_now = 0;
        std::thread::id tid = std::this_thread::get_id();
        std::string content;
        {
            std::unique_lock<std::mutex> ulk (*m);
            cv->wait (ulk, [&] {return !data->empty() || *num_processed == num_data;});

            if (*num_processed == num_data) {
                return;
            }
            
            num_now = (*num_processed); 
            (*num_processed)++;
            content = data->front ();
            data->pop ();
        }
        printf("Thread %x : process (%d)_(%s)\n", tid, num_now, content.c_str());
        std::this_thread::sleep_for(std::chrono::milliseconds(10*content.length()));
    }



}


int main(void) {

    std::queue<std::string> data;
    std::mutex m;
    std::condition_variable cv;
    int num_processed = 0;

    std::thread producer (func_producer, &data, &m, &cv);
    std::vector<std::thread> consumers;
    for (int i=0; i<num_consumers; i++) {
        consumers.push_back (std::thread (func_consumer, &data, &m, &cv, &num_processed));
    }

    
    producer.join();
    for (auto con=consumers.begin (); con<consumers.end (); con++) {
        con->join ();
    }

    return 0;
}
