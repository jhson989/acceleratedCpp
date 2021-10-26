#include "utils.hpp"

#include <iostream>
#include <string>
#include <future>
#include <thread>

void worker (std::promise<std::string>& p) {
    p.set_value ("Hello world!");
}


int main(void) {

    std::promise<std::string> p;
    std::future<std::string> data = p.get_future ();

    std::thread thrd (worker, std::ref (p));
    std::cout << data.get() << std::endl;

    thrd.join ();

    return 0;
}

