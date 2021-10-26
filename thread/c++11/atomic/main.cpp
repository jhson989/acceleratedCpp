#include "utils.hpp"
#include <cstdio>
#include <atomic>
#include <thread>
#include <vector>
#include <mutex>

const int num_threads = 8;
const unsigned int num_data = 1e+8*num_threads;

void atomic_reduction (const std::vector<int>::iterator& data_start, const std::vector<int>::iterator& data_end, std::atomic<unsigned int>& sum) {

    for (auto i=data_start; i!=data_end; i++)
        sum.fetch_add (*i);

}

void lock_reduction (const std::vector<int>::iterator& data_start, const std::vector<int>::iterator& data_end, unsigned int& sum, std::mutex& m) {

    for (auto i=data_start; i!=data_end; i++){
        std::lock_guard<std::mutex> lock(m);
        sum += (*i);
    }
}

int main (void) {

    timeval st, ed;
    std::vector<int> data (num_data);
    get_random_vector (data, -5, 5);
    const unsigned int per_thread = num_data/num_threads;

    printf("Atomic reduction");
    st = get_time ();
    std::atomic<unsigned int> atomic_sum (0.0f);
    std::vector<std::thread> atomic_funcs;
    for (unsigned int i=0; i<num_threads; i++) {
        atomic_funcs.push_back (std::thread (atomic_reduction, data.begin ()+i*per_thread, data.begin ()+(i+1)*per_thread, std::ref (atomic_sum)));
    }
    for (auto func=atomic_funcs.begin (); func!=atomic_funcs.end (); func++) {
        func->join ();
    }
    ed = get_time ();
    printf ("Elapsed time : %.4lf Result : %d \n\n", get_sec (st, ed), atomic_sum.load());

    printf("Lock reduction");
    st = get_time ();
    unsigned int lock_sum = 0.0f;
    std::mutex m;
    std::vector<std::thread> lock_funcs;
    for (unsigned int i=0; i<num_threads; i++) {
        lock_funcs.push_back (std::thread (lock_reduction, data.begin ()+i*per_thread, data.begin ()+(i+1)*per_thread, std::ref (lock_sum), std::ref (m)));
    }
    for (auto func=lock_funcs.begin (); func!=lock_funcs.end (); func++) {
        func->join ();
    }
    ed = get_time ();
    printf ("Elapsed time : %.4lf Result : %d \n\n", get_sec (st, ed), lock_sum);





}



