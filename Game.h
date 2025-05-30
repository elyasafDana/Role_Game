//elidana@gmail.com
#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
//#include"Player.h"
//#include"Role.h"
using namespace std;
class Player;
class Role;
class Game{

private:
    int index;
    bool isPlayerOut;
    vector<Player*> playersArr;

    

public:
    Game();
    ~Game();
    
    int getPlayersNum();
    int turnID();
    int turnNum();
    string players();
    bool isWinner();
    void addPlayer(string n, Role* r);
    void setPlayerOut(bool b);
    string turn();
    string winner();

    
    Player& getPlayerAt(int index);
    void removePlayer(Player* p);
    Player&  findPlayerByName(string playerName );
    void  nextTurn();



};

#endif // GAME_H
