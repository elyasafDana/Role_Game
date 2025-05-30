//elidana@gmail.com
#ifndef BARON_H
#define BARON_H
#include "Role.h"

class Baron:public Role{
    public:
    Baron();
    ~Baron();
    bool invest() override ;
    void putSanction() override;
    Baron(const Baron& other) : Role(other) {}
    Baron& operator=(const Baron& other) {
        if (this != &other) {
            Role::operator=(other);
        }
        return *this;
    }
    Role* clone() const override {
        return new Baron(*this);
    }


};
#endif // GAME_H

