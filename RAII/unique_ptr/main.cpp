
#include <iostream>
#include <memory>
#include <string>

using std::string;

template <class T>
class vec3d_raii {

    public:
        vec3d_raii (string name, T a=0, T b=0, T c=0) : data_(nullptr), name_(name) {
            std::cout << "Constructor called for : " << name_ <<std::endl;
            data_ = new T[3]{a, b, c};
        }

        vec3d_raii (const vec3d_raii& a) = delete;
        vec3d_raii& operator= (const vec3d_raii& a) = delete;

        ~vec3d_raii () {
            std::cout << "Destructor called for : " << name_ <<std::endl;
            delete data_;
        }

        T operator* (const vec3d_raii& operand) {
            return (data_[0]*operand.data_[0] + data_[1]*operand.data_[1] + data_[2]*operand.data_[2]);
        }


    private:
        T* data_; 
        string name_;

};


int main (void) {
    
    std::unique_ptr<vec3d_raii<int>> v1 = std::make_unique<vec3d_raii<int>>("v1", 1, 2, 3);
    std::unique_ptr<vec3d_raii<int>> v2 = std::make_unique<vec3d_raii<int>>("v2", 100, 10, 1);


    std::cout << (*v1.get())*(*v2.get()) << std::endl;
    

    return 0;
}


