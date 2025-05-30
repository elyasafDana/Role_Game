//elidana@gmail.com
#include"Spy.h"
#include"Player.h"
#include<iostream>

Spy:: Spy(){
    //Role();
    srole="Spy";
}

Spy:: ~Spy(){}



void Spy:: preventArrest(Player& p){
    p.getRole().setCanArrest(false);

}
