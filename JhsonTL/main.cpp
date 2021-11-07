
#include <iostream>

#include "Vector.hpp"


void test_vector ();


int main(void) {

    test_vector ();

    return 0;
}


void test_vector () {

    // Define a vector
    Vec<int> a;

    // push_back
    for (int i=0; i<10; i++)
        a.push_back (i);

    // Assignment initialization
    std::cout << "----B----" << std::endl;
    Vec<int> b = a;
    for (int i=0; i<10; i++)
        std::cout << b[i] << std::endl;

    // Copy initialization
    std::cout << "----C----" << std::endl;
    Vec<int> c(b);
    for (int i=0; i<10; i++)
        std::cout << c[i] << std::endl;

    // Assignment
    std::cout << "----B----" << std::endl;
    b = a;
    for (int i=0; i<10; i++)
        std::cout << b[i] << std::endl;

    // Call Deconstructors

}


