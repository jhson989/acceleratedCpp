
#include <iostream>

#include "Vector.hpp"


int main(void) {
    Vec<int> a;

    for (int i=0; i<10; i++)
        a.push_back (i);


    std::cout << "----B----" << std::endl;
    Vec<int> b = a;
    for (int i=0; i<10; i++)
        std::cout << b[i] << std::endl;

    std::cout << "----C----" << std::endl;
    Vec<int> c(b);
    for (int i=0; i<10; i++)
        std::cout << c[i] << std::endl;

    std::cout << "----B----" << std::endl;
    b = a;
    for (int i=0; i<10; i++)
        std::cout << b[i] << std::endl;




    return 0;
}

