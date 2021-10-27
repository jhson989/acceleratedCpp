
#include <iostream>
#include <vector>
#include <functional>

int callable_func (const std::vector<int>& a) {
    std::cout << "Callable Function" << std::endl;
    for (auto i=a.begin (); i!=a.end (); i++)
        std::cout << *i << " ";

    std::cout << std::endl;
    return 1;
}

class callable_class {

    public:
        int operator() (const std::vector<int>& a) {
            std::cout << "Callable class" << std::endl;
            for (auto i=a.begin (); i!=a.end (); i++)
                std::cout << *i << " ";

            std::cout << std::endl;
            return 1;       
        }

};

auto callable_lambda = [] (const std::vector<int>& a) {
    std::cout << "Callable lambda" << std::endl;
    for (auto i=a.begin (); i!=a.end (); i++)
        std::cout << *i << " ";

    std::cout << std::endl;
    return 1;   
};



int main (void) {

    std::vector<int> arg (5, 2);
        
    std::function<int (const std::vector<int>&)> f1 = callable_func;
    std::function<int (const std::vector<int>&)> f2 = callable_class ();
    std::function<int (const std::vector<int>&)> f3 = callable_lambda;


    f1 (arg);
    f2 (arg);
    f3 (arg);


    return 0;
};

