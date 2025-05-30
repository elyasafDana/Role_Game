//elidana@gmail.com
#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include "Role.h"  // כלול את כותרת מחלקת Role
using namespace std;



class Player {
    private:
        string name;
        Role* role;
        int coins;
        int id;
        static int counter;

    public:
        // בנאי
        Player(string n, Role* r);//:name(n), role(r), coins(0), id(counter++){
        //}
        ~Player();
        string getName();
        void setName(const string newName);
        Role& getRole();
        //void setRole( Role newRole);
        int getId();
        void setId(int newId);
         Player(const Player& other);              // בנאי העתקה
    Player& operator=(const Player& other);
};

#endif // PLAYER_H
