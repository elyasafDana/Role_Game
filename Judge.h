//elidana@gmail.com
#ifndef Judge_H
#define Judge_H

#include"Player.h"
class Judge: public Role{    
    public:
        Judge();
        ~Judge();
        //void  tax();
        Judge(const Judge& other) : Role(other) {}
    Judge& operator=(const Judge& other) {
        if (this != &other) {
            Role::operator=(other);
        }
        return *this;
    }
    Role* clone() const override {
        return new Judge(*this);
    }
        
    };

    #endif