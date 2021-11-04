#include <iostream>
using std::cout;
using std::endl;

template <class T>
T add (T a) {
    return a;
}

template <class T, class... Ts>
T add (T a, Ts... args) {
    return a + add (args...);
}

int main(void) {

    cout << add (1) << " = 1" << endl;
    cout << add (1, 2) << " = 1 + 2" << endl;
    cout << add (1, 2, 3) << " = 1 + 2 + 3" << endl;
    cout << add (1, 2, 3, 4) << " = 1 + 2 + 3 + 4" << endl;
    cout << add (1, 2, 3, 4, 5) << " = 1 + 2 + 3 + 4 + 5" << endl;
    
    return 0;
}

