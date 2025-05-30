//elidana@gmail.com
#ifndef Merchant_H
#define Merchant_H

#include"Player.h"
class Merchant: public Role{    
    public:
        Merchant();
        ~Merchant();
        //void  tax();
        Merchant(const Merchant& other) : Role(other) {}
    Merchant& operator=(const Merchant& other) {
        if (this != &other) {
            Role::operator=(other);
        }
        return *this;
    }
    Role* clone() const override {
        return new Merchant(*this);
    }
        
    };

    #endif