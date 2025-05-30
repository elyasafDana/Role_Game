//elidana@gmail.com
#include "Role.h"
#include "Player.h"
#include "Game.h"

#include <iostream>



    Role:: ~Role(){

    }
    Role:: Role(){
        coins=0;
        lastArrested=-1;
        isBanned=false;
        canArrest=true;
    }

    string Role:: getName(){
        return srole;
    }

    void Role:: putSanction(){
        isBanned=true;
    }

    void Role :: decreaseCoin(int num){
        coins =coins-num;
    }
     bool Role:: gather(){
        if (!isBanned){
            coins++;
            cout<<"adding one"<<endl;
            return true;
        }
        else{
            cout<<"you are banned cant do this action"<<endl;
            return false;
        }
    }

     bool Role ::tax(){
        if (!isBanned){
            cout<<"adding 2"<<endl;
            coins += 2;
            return true;
        }else{
            cout<<"you are banned cant do this action"<<endl;
            return false;
        }
    }

    bool Role::getIfBanned(){
        return isBanned;
    }
     bool Role::bribe(){
        if (canAfford(4)){
            decreaseCoin(4);
            return true;
        }
        return false;
    }
     bool Role:: arrest(Player& p){
        if(!canArrest) {
            cout<<"you are banned from arreest action"<<endl;
            return false;    
        }
        if (p.getId() == lastArrested){
            cout << "this player was arrested last turn youcant arrest this player" << endl;
            return false;
        }else{
            if(!(p.getRole().getName()=="General")){
                p.getRole().decreaseCoin(1);
            }
            if (p.getRole().getName()=="Merchant")
            {
                p.getRole().decreaseCoin(1);//decrease another coin sum=2;
                lastArrested=p.getId();
                return true;
            }
            
            coins++;
            lastArrested=p.getId();
            return true;
        }
        
    }

     bool Role::sanction(Player& p){
        if(canAfford(3)){
            p.getRole().putSanction();
            if (p.getRole().getName()=="Judge")
            {
                cout<<"decresing"<<4 <<"from"<<coins  <<endl;
                decreaseCoin(4);
            }
            else if(p.getRole().getName()=="Baron") {
                    p.getRole().addCoins(1);
                }
            else{
                decreaseCoin(3);
            }
            return true;
        }
        else{
            cout<<"you dont have enough mony"<<endl;
            return false;
        }

    }

    //virtual bool coup(Player p,Game g);     // פונקציה טהורה
     bool Role::coup(Player& p,Game& g){
        if(canAfford(7)){
            g.removePlayer(&p);
            g.setPlayerOut(true);
            cout<<"the player is out"<<endl;
            return true;
        }
        else{
            cout<<"you dont have enough money"<<endl;
            return false;
        }
    }


     bool Role::canAfford(int m){
        if (coins - m < 0){
            cout<<"you dont have enough mony"<<endl;
            return false;
        }
        return true;
    }

    int Role::getCoins(){
        return coins;

    }

    void Role:: addCoins(int num){
        coins+=num;
    }

    void Role:: setCanArrest(bool b){
        canArrest=b;
    }

    bool Role:: getCanArrest(){
        return canArrest;
    }
     bool Role:: invest(){
        cout<<"not override"<<endl;
        return false;
    }
     int Role::seeCoins(Player p){
        cout<<"see of ROLE"<<endl;
        return p.getRole().getCoins();}
     void  Role::preventArrest(Player& p){}
    void  Role:: turnWasDone(){

        canArrest=true;
        isBanned=false;

    }

    Role::Role(const Role& other)
    : coins(other.coins), isBanned(other.isBanned),
      canArrest(other.canArrest), srole(other.srole) {}

Role& Role::operator=(const Role& other) {
    if (this != &other) {
        coins = other.coins;
        isBanned = other.isBanned;
        canArrest = other.canArrest;
        srole = other.srole;
    }
    return *this;
}


    

int Role::lastArrested = -1;



    