#pragma once

#include <cstdio>
#include <sys/time.h>
#include <algorithm>
#include <cstdlib>
#include <vector>

inline timeval get_time () {
    timeval t;
    gettimeofday (&t, NULL);
    return t;
}

inline const double get_sec (timeval& start, timeval& end) {
    return (end.tv_sec - start.tv_sec) + (end.tv_usec-start.tv_usec)*1e-6 ;
}

template <typename T>
inline void get_random_vector (std::vector<T>& data, T min=0, T max=1000) {
    std::generate (data.begin (), data.end (), [&] () {return min +(T)(std::rand()%(int)(max-min));});
}
