//elidana@gmail.com
#ifndef ROLE_H
#define ROLE_H
#include<string>
//#include "Player.h" // לכלול את כותרת מחלקת Player
class Player;
class Game;
using namespace std;
class Role
{
protected:
static int lastArrested;
int coins;
bool isBanned;
bool canArrest;
string srole;

public:
string getName();
    Role();
   virtual ~Role();
    virtual void putSanction();
    // פונקציות וירטואליות
    virtual bool gather();
    virtual bool tax();
    virtual bool bribe();
    virtual bool arrest(Player& p);
    virtual bool invest();
        virtual int seeCoins(Player p);
    virtual void  preventArrest(Player& p);
    virtual bool sanction(Player& p); // פונקציה טהורה
    virtual bool coup(Player& p,Game& g);     // פונקציה טהורה
   
    bool canAfford(int m); // cheak if i have enough money to make a action
    void decreaseCoin(int num);
    int getCoins();
    void setCanArrest(bool b);
    bool getCanArrest();
    void turnWasDone();
    bool getIfBanned();
    void  addCoins(int num);

    Role(const Role& other);               // בנאי העתקה
    Role& operator=(const Role& other);    // אופרטור השמה

    virtual Role* clone() const = 0; 

};

#endif // ROLE_H
