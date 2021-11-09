#include <iostream>
#include "shape.hpp"
using std::cout;
using std::endl;

int main(void) {

    Rectangle rec (10, 20);
    cout << rec.GetSize () << endl;

    return 0;

}