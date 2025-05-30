//elidana@gmail.com
#include <string>
#include "Player.h"

using namespace std;

// Getter for name
string Player::getName(){return name;}

Player::Player(string n, Role* r):name(n), role(r), coins(0), id(counter++){
}

// Setter for name
void Player::setName(const string newName){name = newName;}

Player::~Player(){
    delete role;
}


// Getter for role
Role& Player::getRole(){return *role;}



// Setter for role
//void Player::setRole( Role newRole){role = &newRole;}


// Getter for id
int Player::getId(){return id;}

// Setter for id
void Player::setId(int newId){id = newId;}


Player::Player(const Player& other)
    : name(other.name), coins(other.coins), id(counter++) {
    
}

int Player::counter=0;



Player& Player::operator=(const Player& other) {
    if (this != &other) {
        name = other.name;
        coins = other.coins;
        delete role;
        role = other.role ? other.role->clone() : nullptr;
    }
    return *this;
}