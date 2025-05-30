//elidana@gmail.com
#include "Player.h"
#include "Game.h"
#include<vector>


using namespace std;
int Game:: getPlayersNum(){
    return playersArr.size();
}
Game::~Game(){}
Game::Game(){
    index=0;
    isPlayerOut=false;
}

int Game:: turnID(){
     return getPlayerAt(index).getId();
}
void Game:: nextTurn(){
    index=(++index)%getPlayersNum();
}

int Game:: turnNum(){
     return index;
}
string Game::turn(){
     return getPlayerAt(index).getName();
}

string Game:: players(){
    cout<<"the players in the game:"<<endl;
    string names="";
    for (int i = 0; i < getPlayersNum(); i++)
    {
        cout<<getPlayerAt(i).getName()<<endl;
        names=names+getPlayerAt(i).getName();
    }
    return names;
}




bool Game:: isWinner(){
    cout<<getPlayerAt(0).getName()<<endl;

    if(getPlayersNum()<=1){
        cout<<"the winner is:"<<getPlayerAt(0).getName()<<endl;
        return true;
    }
    return false;

}
string Game::winner(){
    return getPlayerAt(0).getName();
}
 Player& Game ::getPlayerAt(int index){
     return *(playersArr.at(index));
}


void Game:: setPlayerOut(bool b){
    isPlayerOut=b;
}


//Player(string n, Role r){
void Game:: addPlayer(string n, Role* r){
    playersArr.push_back( new Player(n,r));
}

// void Game:: removePlayer(Player p){
//     for (int i = 0; i < getPlayersNum(); i++)
//     {
//         if (p.getId()==getPlayerAt(i).getId()){
//             playersArr.erase(playersArr.begin() + i);
//             break;
//         }
        
//     }


// }
void Game::removePlayer(Player* p) {
    for (int i = 0; i < getPlayersNum(); i++) {
        if (playersArr[i] == p) {
            playersArr.erase(playersArr.begin() + i);
            break;
        }
    }
}

    Player& Game:: findPlayerByName(string playerName ){
        for (int i = 0; i < getPlayersNum(); i++)
        {
            if(getPlayerAt(i).getName()==playerName){
                //cout<<"found"<<endl;
                return getPlayerAt(i);
            }
        }
        cout<<"not found"<<endl;
    }

    