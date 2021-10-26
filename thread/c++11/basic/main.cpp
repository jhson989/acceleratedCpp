#include <iostream>
#include <cstdio>
#include <thread>
#include <cmath>
#include <vector>
#include <sys/time.h>

#define ui unsigned int    

const ui num_data = 1e+8;

void worker_func (const std::vector<double>& data, const ui num_workers, const ui idx_workers, double* result) {

    std::thread::id this_id = std::this_thread::get_id();
    ui start = (idx_workers*num_data/num_workers);
    ui end = ((idx_workers+1)*num_data/num_workers);
    printf("Thread ID-%x : %u ~ %u\n", this_id, start, end);

    for (auto i=data.begin ()+start; i!=data.begin ()+end; i++) {
        *result += sqrt (pow ((*i), 2.2) * (*i) + (*i)) * pow ((*i), sqrt (*i));
    }

}

void run (std::vector<double>& data, const ui num_workers, double& result) {

    std::vector<std::thread> workers;
    std::vector<double> partial_result(num_workers, 0.0f);
    for (ui i=0; i<num_workers; i++) {
        workers.push_back (std::thread (worker_func, data, num_workers, i, &partial_result[i]));
    }

    for (ui i=0; i<num_workers; i++) {
        workers[i].join();
    }

    result = 0.0f;
    for (auto i=partial_result.begin (); i!=partial_result.end (); i++) {
        result += *i;
    }       
}



int main(void) {

    timeval st, ed;
    double result = 0.0f;
    
    std::vector<double> data(num_data, 3.0f);


    gettimeofday(&st, NULL);
    run (data, 1, result);
    gettimeofday(&ed, NULL); 
    std::cout << "Single thread execution. Result : " << result << " Time : " << (ed.tv_sec - st.tv_sec) + ((ed.tv_usec-st.tv_usec)*1e-6) << std::endl;

    gettimeofday(&st, NULL);
    run (data, 4, result);
    gettimeofday(&ed, NULL); 
    std::cout << "Multi(4) threads execution. Result : " << result << " Time : " << (ed.tv_sec - st.tv_sec) + ((ed.tv_usec-st.tv_usec)*1e-6) << std::endl;



    return 0;
}

