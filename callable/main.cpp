
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

        int callable_member_func (const std::vector<int>& a) {
            std::cout << "Callable class member function" << std::endl;
            for (auto i=a.begin (); i!=a.end (); i++)
                std::cout << *i << " ";

            std::cout << std::endl;
            return 1;       
        }

        static int callable_member_static_func (const std::vector<int>& a) {
            std::cout << "Callable class static member function" << std::endl;
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

    callable_class a;
    std::vector<int> arg (5, 2);
        

    std::cout << std::endl << "============= function pointer" <<std::endl;    
    int (*p1) (const std::vector<int>& a) = callable_func;
    p1 (arg);

    std::cout << std::endl << "============= std::function" <<std::endl;

    // std::function : a object for callable objects
    std::function<int (const std::vector<int>&)> f1 = callable_func;
    std::function<int (const std::vector<int>&)> f2 = callable_class ();
    std::function<int (const std::vector<int>&)> f3 = callable_lambda;
    std::function<int (callable_class*, const std::vector<int>&)> f4 = &callable_class::callable_member_func;
    std::function<int (const std::vector<int>&)> f5 = &callable_class::callable_member_static_func;


    int ret1 = f1 (arg);
    int ret2 = f2 (arg);
    int ret3 = f3 (arg);
    int ret4 = f4 (&a, arg); // member function of class implicitly get one more argument pointing to self (i.e. this)
    int ret5 = f5 (arg);



    std::cout << std::endl << "============= std::mem_fn" <<std::endl;

    // mem_fn : return std::function object for an input member function
    int ret6 = std::mem_fn (&callable_class::callable_member_func) (&a, arg);
    // Somtimes recommended way
    int ret7 = [] (callable_class &a, const std::vector<int>& arg) { 
        std::cout << "Use a lambda for calling a class member function" << std::endl;
        a.callable_member_func(arg); 
        return 1; 
    } (a, arg);


    return 0;
};

