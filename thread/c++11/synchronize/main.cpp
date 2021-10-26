#include <cstdio>
#include <thread>
#include <mutex>
#include <vector>
#include <ctime>
#include <algorithm>
#include <cmath>

#include "utils.hpp"

#define ui unsigned int
const ui num_data = 1e+8;




void worker_func (const std::vector<double>& data, const ui num_workers, const ui idx_workers, double& result, std::mutex& m) {

    std::thread::id this_id = std::this_thread::get_id ();
    ui start = (idx_workers*num_data/num_workers);
    ui end = ((idx_workers+1)*num_data/num_workers);

    for (auto i=data.begin ()+start; i!=data.begin ()+end; i++) {
        std::lock_guard<std::mutex> lock(m);
        result += (*i);
    }

}


double run (std::vector<double>& data, const ui num_workers) {
    double result = 0.0f;
    std::mutex m;
    std::vector<std::thread> workers;

    for (ui i=0; i<num_workers; i++) {
        workers.push_back (std::thread (worker_func, data, num_workers, i, std::ref (result), std::ref (m)));
    }

    for (ui i=0; i<num_workers; i++) {
        workers[i].join ();
    }

    return result;
}



int main (void) {

    std::vector<double> data (num_data);
    std::generate (data.begin (), data.end (), std::rand);



    timeval st, ed;
    double result = 0.0f;

    ui num_workers = 1;
    st = get_time ();
    result = run (data, num_workers);
    ed = get_time ();
    printf ("Single thread execution. Result : %lf, Time : %lf\n", result, get_sec (st, ed)); 

    num_workers = 8;
    st = get_time ();
    result = run (data, num_workers);
    ed = get_time ();
    printf ("Multi(%d) threads execution. Result : %lf, Time : %lf\n", num_workers, result, get_sec (st, ed)); 



    return 0;
}

