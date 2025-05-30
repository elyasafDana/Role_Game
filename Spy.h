//elidana@gmail.com
#ifndef SPY_H
#define SPY_H

#include"Player.h"
class Spy: public Role{    
    public:
        Spy();
        ~Spy();
        
        void  preventArrest(Player& p) override;
        Spy(const Spy& other) : Role(other) {}
    Spy& operator=(const Spy& other) {
        if (this != &other) {
            Role::operator=(other); // קריאה לבסיס
        }
        return *this;
    }
    Role* clone() const override {
        return new Spy(*this);
    }
    };

    #endif
