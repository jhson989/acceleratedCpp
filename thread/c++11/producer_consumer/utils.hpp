

#pragma once

#include <cstdio>
#include <sys/time.h>

inline timeval get_time () {
    timeval t;
    gettimeofday (&t, NULL);
    return t;
}

inline const double get_sec (timeval& start, timeval& end) {
    return (end.tv_sec - start.tv_sec) + (end.tv_usec-start.tv_usec)*1e-6 ;
}
