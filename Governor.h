//elidana@gmail.com
#ifndef GOVERNER_H
#define GOVERNER_H
#include "Role.h"

class Governor: public Role{    
public:
    Governor();
    ~Governor();
    bool  tax() override;
    Governor(const Governor& other) : Role(other) {}
    Governor& operator=(const Governor& other) {
        if (this != &other) {
            Role::operator=(other);
        }
        return *this;
    }
    Role* clone() const override {
        return new Governor(*this);
    }
};

#endif