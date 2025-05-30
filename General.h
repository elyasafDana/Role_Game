//elidana@gmail.com

#ifndef GENERAL_H
#define GENERAL_H

#include"Role.h"

class General:public Role{
    public:
    General();
    ~General();
    General(const General& other) : Role(other) {}
    General& operator=(const General& other) {
        if (this != &other) {
            Role::operator=(other);
        }
        return *this;
    }
    Role* clone() const override {
        return new General(*this);
    }



};

#endif 