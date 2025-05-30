//elidana@gmail.com
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "Game.h"
#include "Spy.h"
#include "Judge.h"
#include "Merchant.h"
#include "Governor.h"
#include "Baron.h"
#include "General.h"


TEST_CASE("Role abilities: Spy, Judge, Merchant") {

    Game g;
    g.addPlayer("jud",new Judge());
    g.addPlayer("s",new Spy());
    g.addPlayer("march",new Merchant());
    g.addPlayer("baron",new Baron());
    g.addPlayer("gov",new Governor());
    g.addPlayer("gen",new General());

    CHECK(g.getPlayersNum() == 6);

    // Test: correct turn index
    CHECK(g.turnNum() == 0);

    // Test: get current player and name
    Player& p0 = g.getPlayerAt(g.turnNum());
    CHECK(p0.getName() == "jud");


    // Simulate turn progression
    g.nextTurn(); // turn 1
    CHECK(g.getPlayerAt(g.turnNum()).getName() == "s");
    g.getPlayerAt(4).getRole().tax();
    CHECK(g.getPlayerAt(4).getRole().getCoins() == 3);

    g.getPlayerAt(1).getRole().preventArrest(g.getPlayerAt(0));
    CHECK(g.getPlayerAt(0).getRole().getCanArrest()== false);

    g.getPlayerAt(3).getRole().invest();
    CHECK(g.getPlayerAt(3).getRole().getCoins()== 3);

    // g.getPlayerAt(0).getRole().sanction(g.getPlayerAt(3));
    // CHECK(g.getPlayerAt(3).getRole().getCoins()== 4);
    g.getPlayerAt(5).getRole().gather();
    g.getPlayerAt(3).getRole().arrest(g.getPlayerAt(5));
    CHECK(g.getPlayerAt(5).getRole().getCoins()== 1);
    
    CHECK(g.getPlayerAt(3).getRole().getCoins()== 4);
    g.getPlayerAt(3).getRole().sanction(g.getPlayerAt(0));
    CHECK(g.getPlayerAt(3).getRole().getCoins()== 0);

    g.getPlayerAt(3).getRole().arrest(g.getPlayerAt(2));
    CHECK(g.getPlayerAt(3).getRole().getCoins()== 0);

    g.getPlayerAt(3).getRole().gather();
    g.getPlayerAt(3).getRole().gather();
    g.getPlayerAt(3).getRole().gather();
    g.getPlayerAt(3).getRole().gather();
    g.getPlayerAt(3).getRole().sanction(g.getPlayerAt(4));
    CHECK(g.getPlayerAt(4).getRole().tax()== false);
    g.getPlayerAt(3).getRole().arrest(g.getPlayerAt(0));
    CHECK(g.getPlayerAt(1).getRole().arrest(g.getPlayerAt(0))== false);


    g.getPlayerAt(3).getRole().tax();
    g.getPlayerAt(3).getRole().tax();
    g.getPlayerAt(3).getRole().tax();
    g.getPlayerAt(3).getRole().tax();
    g.getPlayerAt(3).getRole().coup(g.getPlayerAt(0),g);
    bool isinside=false;
    for(int i=0;i<g.getPlayersNum();i++){
        if(g.getPlayerAt(i).getName()=="Jud") isinside=true;
    }

    CHECK(isinside==false);








}


// TEST_CASE("Role abilities: Spy, Judge, Merchant") {
//     Game game;
//     Spy spy;
//     Judge judge;
//     Merchant merchant;

//     merchant.gather();
//     merchant.gather();
//     merchant.gather();
//     CHECK(merchant.getCoins() == 3);

//     game.nextTurn();
//     merchant.startTurn(); // simulate bonus logic
//     CHECK(merchant.getCoins() == 4);

//     spy.preventArrest(merchant);
//     CHECK(merchant.getRole().canArrest() == false);

//     merchant.setCoins(4);
//     merchant.bribe();
//     CHECK(merchant.getCoins() == 0);

    
// }

// TEST_CASE("Role abilities: Governor, Baron, General") {
//     Game game;
//     Governor gov ;
//     Baron baron;
//     General general;

//     // --- Governor uses tax, should get 3 coins ---
//     bool taxed = gov.tax();
//     CHECK(taxed == true);
//     CHECK(gov.getCoins() == 3);

//     // Governor banned: tax should fail
//     gov.setBan(true);
//     CHECK(gov.tax() == false);
//     CHECK(gov.getCoins() == 3); // no change

//     // --- Baron invests: pays 3 to gain 6 (you give 3 directly for test) ---
//     baron.setCoins(3);
//     CHECK(baron.invest() == true);
//     CHECK(baron.getCoins() == 6); // +3 in fake logic for now

//     // Baron gets sanctioned (gets +1 coin as compensation)
//     int beforeSanction = baron.getCoins();
//     baron.putSanction(); // sets isBanned + gives him 1 coin
//     CHECK(baron.isBannedNow() == true);
//     CHECK(baron.getCoins() == beforeSanction + 1);

//     // General exists – no logic yet, just a stub
//     CHECK(general.getRoleName() == "General");
// }
// TEST_CASE("Game functionality: adding players, turn order, winner logic") {
//     Game game;

//     // Create roles and add players
//     Role* r1 = new Spy();
//     Role* r2 = new Judge();
//     Role* r3 = new Merchant();

//     game.addPlayer("Alice", r1);
//     game.addPlayer("Bob", r2);
//     game.addPlayer("Charlie", r3);

//     // Check number of players
//     CHECK(game.getPlayersNum() == 3);

//     // Check players added correctly
//     CHECK(game.getPlayerAt(0).getName() == "Alice");
//     CHECK(game.getPlayerAt(1).getName() == "Bob");
//     CHECK(game.getPlayerAt(2).getName() == "Charlie");

//     // Test turn order
//     CHECK(game.turnNum() == 0);
//     game.nextTurn();
//     CHECK(game.turnNum() == 1);
//     game.nextTurn();
//     CHECK(game.turnNum() == 2);
//     game.nextTurn();
//     CHECK(game.turnNum() == 0); // back to start

//     // Test findPlayerByName
//     CHECK(game.findPlayerByName("Bob").getName() == "Bob");

//     // Test removePlayer
//     Player& bob = game.findPlayerByName("Bob");
//     game.removePlayer(&bob);
//     CHECK(game.getPlayersNum() == 2);
//     CHECK(game.getPlayerAt(0).getName() == "Alice");
//     CHECK(game.getPlayerAt(1).getName() == "Charlie");

//     // Simulate winner
//     game.removePlayer(&game.findPlayerByName("Charlie"));
//     CHECK(game.getPlayersNum() == 1);
//     CHECK(game.winner() == true);
// }
