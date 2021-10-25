#pragma once

#include <vector>
#include <string>
#include "memory.hpp"

class Info_student {

    public:

        // Constructor
        Info_student () {

        }

        explicit Info_student (const Info_student& info) {

        }

        Info_student& operator= (const Info_student& rhs) {

        }

        ~Info_student () {

        }


    protected:
        std::string name;
        int age;
        double mid_exam, final_exam;

};

class Info_grad : public Info_student {

    public:
        Info_grad() {

        }

        explicit Info_grad (const Info_grad& info) {

        } 

        Info_grad& operator= (const Info_grad& rhs) {

        }
        
        ~Info_grad () {

        }

    private:
        std::string paper_name;
};