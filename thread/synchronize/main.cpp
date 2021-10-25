#include <cstdio>
#include <thread>
#include <mutex>
#include <vector>
#include <ctime>
#include <algorithm>
#include <cmath>
#include <sys/time.h>

#define ui unsigned int

const ui num_data = 128e+2;

void worker_func (const std::vector<double>& data, const ui num_workers, const ui idx_workers, double& result, std::mutex& m) {

    std::thread::id this_id = std::this_thread::get_id();
    ui start = (idx_workers*num_data/num_workers);
    ui end = ((idx_workers+1)*num_data/num_workers);
//    printf("Thread ID-%x : %u ~ %u\n", this_id, start, end);

    for (auto i=data.begin ()+start; i!=data.begin ()+end; i++) {
        int num = ((int)*i)%10;
        std::lock_guard<std::mutex> lock(m);
        result += sqrt (pow (num, 2.2) * num + num) * pow (num, sqrt (num));
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
        workers[i].join();
    }

    return result;
}



int main (void) {

    std::vector<double> data(num_data);
    std::generate(data.begin(), data.end(), std::rand);



    timeval st, ed;
    double result = 0.0f;
    
    gettimeofday(&st, NULL);
    result = run (data, 1);
    gettimeofday(&ed, NULL); 
    printf("Single thread execution. Result : %lf, Time : %lf\n",result, (ed.tv_sec - st.tv_sec) + ((ed.tv_usec-st.tv_usec)*1e-6)); 

    gettimeofday(&st, NULL);
    result = run (data, 16);
    gettimeofday(&ed, NULL); 
    printf("Multi(16) thread execution. Result : %lf, Time : %lf\n",result, (ed.tv_sec - st.tv_sec) + ((ed.tv_usec-st.tv_usec)*1e-6)); 






    return 0;
}

