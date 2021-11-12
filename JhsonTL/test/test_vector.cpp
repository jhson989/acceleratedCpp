
#include <iostream>

#include "test_vector.hpp"


template <typename T>
void print(T a) {
    a.print();
}

void test_vector () {

    // Define a vector
    Vec<int> a;

    // push_back
    for (Vec<int>::size_type i=0; i<10; i++)
        a.push_back (i);

    // Assignment initialization
    std::cout << "----B----" << std::endl;
    Vec<int> b = a;
    print (b);

    // Copy initialization
    std::cout << "----C----" << std::endl;
    Vec<int> c(b);
    print (c);
    // Assignment
    std::cout << "----B----" << std::endl;
    b = a;
    print (b);

    // push pop test
    std::cout << "---pop_back test---" << std::endl;
    auto total_size = a.size();
    print(a);
    for (Vec<int>::size_type i=0; i<total_size; i++) {
        a.pop_back ();
        print (a);
    }
    a.push_back (10);
    print (a);

    // erase test
    std::cout << "---erase (at) test ---" << std::endl;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    a.push_back(4);
    print (a);
    a.erase(1);
    print (a);
    a.erase(2);
    print (a);
    a.erase(2);
    print (a);
    a.erase(0);
    print (a);
    a.push_back (1);
    print (a);



    // Call Deconstructors

}


