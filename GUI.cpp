//elidana@gmail.com

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/fl_message.H>
#include <string>
#include "Player.h"
#include "Governor.h"
#include "Spy.h"
#include "Baron.h"
#include "General.h"
#include "Judge.h"
#include "Merchant.h"
#include "Game.h"

#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;
Fl_Window *window;
Fl_Window *blueWindow;
Fl_Input *nameInput;
Fl_Choice *roleChoice;
Fl_Box *confirmationBox; // תיבה חדשה לאישור
Fl_Box *label1;
Fl_Box *label2;
Fl_Box *label3;

Game game;

int playerAvailableActionNums;

void createButtons(Fl_Window *window, int screenWidth, int screenHeight);
void onSaveLobby(Fl_Widget *, void *)
{
    if (game.getPlayersNum() == 6)
    {
        cout << "only 6 players can play ,cant add another player" << endl;
        return;
    }
    std::string name = nameInput->value();

    std::srand(time(nullptr));

    int roleNumber = std::rand() % 6 + 1;

    if (roleNumber == 1)
        game.addPlayer(name, new Governor());
    if (roleNumber == 2)
        game.addPlayer(name, new Spy());
    if (roleNumber == 3)
        game.addPlayer(name, new Baron());
    if (roleNumber == 4)
        game.addPlayer(name, new Judge());
    if (roleNumber == 5)
        game.addPlayer(name, new Merchant());
    if (roleNumber == 6)
        game.addPlayer(name, new General());

    confirmationBox->labelcolor(FL_RED);
    confirmationBox->redraw(); // רענון התצוגה
}

Player pickPlayer(Fl_Window *window)
{
    int screenHeight = Fl::h(); // גובה החלון
    roleChoice = new Fl_Choice(0, screenHeight / 2 - 15, 200, 30, "Role:");
    roleChoice->align(FL_ALIGN_LEFT);
    roleChoice->labelcolor(FL_RED);
    for (int i = 0; i < game.getPlayersNum(); i++)
    {
        roleChoice->add(game.getPlayerAt(i).getName().c_str());
    }
    window->add(roleChoice);

    // roleChoice->value();
    string playerName = roleChoice->text();
    game.findPlayerByName(playerName);
}

Fl_Choice *arrestChoice = nullptr;
Fl_Button *arrestSaveBtn = nullptr;
Fl_Box *arrestResultBox = nullptr;

void save_ArrestCallback(Fl_Widget *, void *)
{
    if (arrestChoice && arrestResultBox)
    {
        const char *selected = arrestChoice->text();
        Player &p = game.findPlayerByName(selected);

        if (game.getPlayerAt(game.turnNum()).getRole().arrest(p))
        {
            playerAvailableActionNums--;
            

            if (playerAvailableActionNums <= 0)
            {
                blueWindow->hide();
                game.getPlayerAt(game.turnNum()).getRole().turnWasDone();
                game.setPlayerOut(false);
                playerAvailableActionNums = 1;
                game.nextTurn();
                Fl_JPEG_Image *originalImage = new Fl_JPEG_Image("pic.jpg");
                Fl_Image *backgroundImage = originalImage->copy(Fl::w(), Fl::h());
                delete originalImage;
                blueWindow = new Fl_Window(Fl::w(), Fl::h(), "Game");
                Fl_Box *blueBackground = new Fl_Box(0, 0, Fl::w(), Fl::h());
                blueBackground->image(backgroundImage);
                blueBackground->box(FL_FLAT_BOX);
                // Fl_Box *blueBackground = new Fl_Box(0, 0, Fl::w(), Fl::h());
                createButtons(blueWindow, Fl::w(), Fl::h());
                blueBackground->box(FL_FLAT_BOX);
                blueBackground->color(FL_BLUE);
                blueWindow->end();
                blueWindow->show();
            }
        }
    }
}

void arrest_callback(Fl_Widget *, void *win)
{
    Fl_Window *choiceWin = new Fl_Window(300, 200, "choose player");
    choiceWin->begin();

    // יצירת תפריט בחירה
    arrestChoice = new Fl_Choice(50, 50, 200, 30, "choose player:");
    for (int i = 0; i < game.getPlayersNum(); i++)
    {
        arrestChoice->add(game.getPlayerAt(i).getName().c_str());
    }

    // כפתור שמירה
    arrestSaveBtn = new Fl_Button(100, 120, 100, 30, "SAVE");
    arrestSaveBtn->callback(save_ArrestCallback);

    // תיבה להצגת התוצאה (לא חובה)
    arrestResultBox = new Fl_Box(50, 160, 200, 30);
    arrestResultBox->box(FL_DOWN_BOX);
    arrestResultBox->align(FL_ALIGN_INSIDE | FL_ALIGN_LEFT);

    choiceWin->end();
    choiceWin->show();
}

Fl_Choice *sanctionChoice = nullptr;
Fl_Button *sanctionSaveBtn = nullptr;
Fl_Box *sanctionResultBox = nullptr;

void save_SanctionCallback(Fl_Widget *, void *)
{
    if (sanctionChoice && sanctionResultBox)
    {
        const char *selected = sanctionChoice->text();
        Player &p = game.findPlayerByName(selected);
        if (game.getPlayerAt(game.turnNum()).getRole().sanction(p))
        {
            playerAvailableActionNums--;

            if (playerAvailableActionNums <= 0)
            {
                blueWindow->hide();
                game.getPlayerAt(game.turnNum()).getRole().turnWasDone();
                game.setPlayerOut(false);
                playerAvailableActionNums = 1;
                game.nextTurn();
                Fl_JPEG_Image *originalImage = new Fl_JPEG_Image("pic.jpg");
                Fl_Image *backgroundImage = originalImage->copy(Fl::w(), Fl::h());
                delete originalImage;
                blueWindow = new Fl_Window(Fl::w(), Fl::h(), "Game");
                // Fl_Box *blueBackground = new Fl_Box(0, 0, Fl::w(), Fl::h());
                Fl_Box *blueBackground = new Fl_Box(0, 0, Fl::w(), Fl::h());
                blueBackground->image(backgroundImage);
                blueBackground->box(FL_FLAT_BOX);
                createButtons(blueWindow, Fl::w(), Fl::h());
                blueBackground->box(FL_FLAT_BOX);
                blueBackground->color(FL_BLUE);
                blueWindow->end();
                blueWindow->show();
            }
        }

        // אפשר לעדכן תוצאה בתיבה אם רוצים
    }
}
Player *p;
void sanction_callback(Fl_Widget *, void *win)
{

    Fl_Window *choiceWin = new Fl_Window(300, 200, "Choose Player to Sanction");
    choiceWin->begin();

    // תפריט בחירה
    sanctionChoice = new Fl_Choice(50, 50, 200, 30, "Choose player:");
    for (int i = 0; i < game.getPlayersNum(); i++)
    {
        sanctionChoice->add(game.getPlayerAt(i).getName().c_str());
    }

    // כפתור שמירה
    sanctionSaveBtn = new Fl_Button(100, 120, 100, 30, "SAVE");
    sanctionSaveBtn->callback(save_SanctionCallback);

    // תיבה להצגת תוצאה
    sanctionResultBox = new Fl_Box(50, 160, 200, 30);
    sanctionResultBox->box(FL_DOWN_BOX);
    sanctionResultBox->align(FL_ALIGN_INSIDE | FL_ALIGN_LEFT);

    choiceWin->end();
    choiceWin->show();
}

bool cancleCoup;
void on_cancle_click(Fl_Widget *widget, void *data)
{
    playerAvailableActionNums--;
    game.getPlayerAt(game.turnNum()).getRole().decreaseCoin(7);
    cout << "we cancled the action" << endl;
    if (playerAvailableActionNums <= 0)
    {
        blueWindow->hide();
        game.getPlayerAt(game.turnNum()).getRole().turnWasDone();
        game.setPlayerOut(false);
        playerAvailableActionNums = 1;
        game.nextTurn();
        Fl_JPEG_Image *originalImage = new Fl_JPEG_Image("pic.jpg");
        Fl_Image *backgroundImage = originalImage->copy(Fl::w(), Fl::h());
        delete originalImage;
        blueWindow = new Fl_Window(Fl::w(), Fl::h(), "Game");
        Fl_Box *blueBackground = new Fl_Box(0, 0, Fl::w(), Fl::h());
        blueBackground->image(backgroundImage);
        blueBackground->box(FL_FLAT_BOX);
        createButtons(blueWindow, Fl::w(), Fl::h());
        blueBackground->box(FL_FLAT_BOX);
        blueBackground->color(FL_BLUE);
        blueWindow->end();
        blueWindow->show();
    }
}

void on_dont_cancle_click(Fl_Widget *widget, void *data)
{
    if (game.getPlayerAt(game.turnNum()).getRole().coup((*p), game))
    {
        // playerAvailableActionNums--;


        if (game.isWinner())
        {
            blueWindow->hide();
        }
        cout << game.turnNum() << endl;

        if (playerAvailableActionNums <= 0)
        {

            blueWindow->hide();
            game.getPlayerAt(game.turnNum()).getRole().turnWasDone();
            game.setPlayerOut(false);
            playerAvailableActionNums = 1;
            game.nextTurn();
            Fl_JPEG_Image *originalImage = new Fl_JPEG_Image("pic.jpg");
            Fl_Image *backgroundImage = originalImage->copy(Fl::w(), Fl::h());
            delete originalImage;
            blueWindow = new Fl_Window(Fl::w(), Fl::h(), "Game");
            Fl_Box *blueBackground = new Fl_Box(0, 0, Fl::w(), Fl::h());
            blueBackground->image(backgroundImage);
            blueBackground->box(FL_FLAT_BOX);

            // Fl_Box *blueBackground = new Fl_Box(0, 0, Fl::w(), Fl::h());
            createButtons(blueWindow, Fl::w(), Fl::h());
            blueBackground->box(FL_FLAT_BOX);
            blueBackground->color(FL_BLUE);
            blueWindow->end();
            blueWindow->show();
        }
    }
}

Fl_Choice *coupChoice = nullptr;
Fl_Button *coupSaveBtn = nullptr;
Fl_Box *coupResultBox = nullptr;

void save_CoupCallback(Fl_Widget *, void *)
{
    if (coupChoice && coupResultBox)
    {
        const char *selected = coupChoice->text();
        p = &game.findPlayerByName(selected);
        bool foundGen = false;
        if (game.getPlayerAt(game.turnNum()).getRole().getCoins() >= 7)
        {
            playerAvailableActionNums--;

            for (int i = 0; i < game.getPlayersNum(); i++)
            {
                if (game.getPlayerAt(i).getRole().getName() == "General" && game.getPlayerAt(i).getRole().getCoins() >= 5)
                {
                    cout << "we have general" << endl;
                    foundGen = true;
                    // Fl_Window *cancleWindow = new Fl_Window(300, 150, "cancle winow");
                    Fl_Window *cancleWindow = new Fl_Window(300, 150, "ביטול פעולה");

                    Fl_Box *box = new Fl_Box(20, 20, 260, 30, "General,do you want to cancle?");
                    box->box(FL_UP_BOX);
                    box->labelfont(FL_BOLD);
                    box->labelsize(16);
                    box->labelcolor(FL_BLACK);

                    // כפתור לביטול
                    Fl_Button *button1 = new Fl_Button(50, 80, 90, 30, "cancle");
                    button1->callback(on_cancle_click, cancleWindow);

                    // כפתור לאי-ביטול
                    Fl_Button *button2 = new Fl_Button(160, 80, 90, 30, " dont cancle");
                    button2->callback(on_dont_cancle_click, cancleWindow);

                    cancleWindow->end();
                    cancleWindow->set_modal(); // כדי לחסום את החלון הראשי בזמן הצגת החלון הזה
                    cancleWindow->show();
                }
            }

            if (!foundGen)
            {
                if (game.getPlayerAt(game.turnNum()).getRole().coup((*p), game))
                {


                    if (game.isWinner())
                    {
                        blueWindow->hide();
                    }
                    else
                    {
                        cout << game.turnNum() << endl;

                        if (playerAvailableActionNums <= 0)
                        {

                            blueWindow->hide();
                            game.getPlayerAt(game.turnNum()).getRole().turnWasDone();
                            game.setPlayerOut(false);
                            playerAvailableActionNums = 1;
                            game.nextTurn();
                            Fl_JPEG_Image *originalImage = new Fl_JPEG_Image("pic.jpg");
                            Fl_Image *backgroundImage = originalImage->copy(Fl::w(), Fl::h());
                            delete originalImage;
                            blueWindow = new Fl_Window(Fl::w(), Fl::h(), "Game");
                            Fl_Box *blueBackground = new Fl_Box(0, 0, Fl::w(), Fl::h());
                            blueBackground->image(backgroundImage);
                            blueBackground->box(FL_FLAT_BOX);

                            createButtons(blueWindow, Fl::w(), Fl::h());
                            blueBackground->box(FL_FLAT_BOX);
                            blueBackground->color(FL_BLUE);
                            blueWindow->end();
                            blueWindow->show();
                        }
                    }
                }
            }
        }
        else
        {
            cout << "you need 7 coins" << endl;
        }
        
    }
}

void coup_callback(Fl_Widget *, void *win)
{

    Fl_Window *choiceWin = new Fl_Window(300, 200, "Choose Player to Coup");
    choiceWin->begin();
    cout << game.getPlayersNum() << endl;
    // תפריט בחירה
    coupChoice = new Fl_Choice(50, 50, 200, 30, "Choose player:");
    for (int i = 0; i < game.getPlayersNum(); i++)
    {
        if (game.getPlayerAt(i).getName() != game.getPlayerAt(game.turnNum()).getName())
        {

            coupChoice->add(game.getPlayerAt(i).getName().c_str());
        }
    }

    // כפתור שמירה
    coupSaveBtn = new Fl_Button(100, 120, 100, 30, "SAVE");
    coupSaveBtn->callback(save_CoupCallback);

    // תיבה להצגת תוצאה
    coupResultBox = new Fl_Box(50, 160, 200, 30);
    coupResultBox->box(FL_DOWN_BOX);
    coupResultBox->align(FL_ALIGN_INSIDE | FL_ALIGN_LEFT);

    choiceWin->end();
    choiceWin->show();
}

Fl_Choice *seeCoinsChoice = nullptr;
Fl_Button *seeCoinsBtn = nullptr;
Fl_Box *seeCoinsResultBox = nullptr;

void seeCoinsCallback(Fl_Widget *, void *)
{
    if (seeCoinsChoice && seeCoinsResultBox)
    {
        const char *selected = seeCoinsChoice->text();
        Player &p = game.findPlayerByName(selected);
        // הנחה שיש פונקציה כזו
        string s= "the player has " + p.getRole().getCoins();
        // הצגת מספר המטבעות בתיבה
        seeCoinsResultBox->label((p.getName() + " has " + to_string(p.getRole().getCoins()) + " coins").c_str());
    }
}

void seeCoins_windowCallback(Fl_Widget *, void *win)
{

    Fl_Window *choiceWin = new Fl_Window(300, 200, "See Player Coins");
    choiceWin->begin();

    // תפריט בחירה
    seeCoinsChoice = new Fl_Choice(50, 50, 200, 30, "Choose player:");
    for (int i = 0; i < game.getPlayersNum(); i++)
    {
        seeCoinsChoice->add(game.getPlayerAt(i).getName().c_str());
    }

    // כפתור הצגה
    seeCoinsBtn = new Fl_Button(100, 120, 100, 30, "SHOW");
    seeCoinsBtn->callback(seeCoinsCallback);

    // תיבת תוצאה
    seeCoinsResultBox = new Fl_Box(50, 160, 200, 30);
    seeCoinsResultBox->box(FL_DOWN_BOX);
    seeCoinsResultBox->align(FL_ALIGN_INSIDE | FL_ALIGN_LEFT);

    choiceWin->end();
    choiceWin->show();
}

Fl_Choice *preventArrestChoice = nullptr;
Fl_Button *preventArrestBtn = nullptr;
Fl_Box *preventArrestResultBox = nullptr;

void preventArrestCallback(Fl_Widget *, void *)
{
    if (preventArrestChoice && preventArrestResultBox)
    {
        const char *selected = preventArrestChoice->text();
        Player &selectedPlayer = game.findPlayerByName(selected);

        // ביצוע הפעולה דרך השחקן הנוכחי
        game.getPlayerAt(game.turnNum()).getRole().preventArrest(selectedPlayer);
        cout << selectedPlayer.getRole().getCanArrest() << endl;

        // עדכון תיבת תוצאה
        std::string msg = selectedPlayer.getName() + " can no longer arrest.";
        preventArrestResultBox->label(msg.c_str());

        std::cout << "preventArrest called on " << selectedPlayer.getName() << std::endl;
    }
}

void preventArrest_windowCallback(Fl_Widget *, void *win)
{

    Fl_Window *choiceWin = new Fl_Window(300, 200, "Prevent Arrest");
    choiceWin->begin();

    // תפריט בחירה
    preventArrestChoice = new Fl_Choice(50, 50, 200, 30, "Choose player:");
    for (int i = 0; i < game.getPlayersNum(); i++)
    {
        if (game.getPlayerAt(i).getName() != game.getPlayerAt(game.turnNum()).getName())
        {
            preventArrestChoice->add(game.getPlayerAt(i).getName().c_str());
        }
    }

    // כפתור פעולה
    preventArrestBtn = new Fl_Button(100, 120, 100, 30, "APPLY");
    preventArrestBtn->callback(preventArrestCallback);

    // תיבת תוצאה
    preventArrestResultBox = new Fl_Box(50, 160, 200, 30);
    preventArrestResultBox->box(FL_DOWN_BOX);
    preventArrestResultBox->align(FL_ALIGN_INSIDE | FL_ALIGN_LEFT);

    choiceWin->end();
    choiceWin->show();
}

void on_cancle_bribe_click(Fl_Widget *widget, void *data)
{
    Fl_Box *box = (Fl_Box *)data;
    playerAvailableActionNums--;
    game.getPlayerAt(game.turnNum()).getRole().decreaseCoin(4);
    cout << "we cancled the action" << endl;
    if (playerAvailableActionNums <= 0)
    {
        blueWindow->hide();
        game.getPlayerAt(game.turnNum()).getRole().turnWasDone();
        game.setPlayerOut(false);
        playerAvailableActionNums = 1;
        game.nextTurn();

        Fl_JPEG_Image *originalImage = new Fl_JPEG_Image("pic.jpg");
        Fl_Image *backgroundImage = originalImage->copy(Fl::w(), Fl::h());
        delete originalImage;
        blueWindow = new Fl_Window(Fl::w(), Fl::h(), "Game");

        Fl_Box *blueBackground = new Fl_Box(0, 0, Fl::w(), Fl::h());
        blueBackground->image(backgroundImage);
        blueBackground->box(FL_FLAT_BOX);
        blueBackground->box(FL_FLAT_BOX);
        blueBackground->color(FL_BLUE);
        createButtons(blueWindow, Fl::w(), Fl::h());
        blueWindow->end();
        blueWindow->show();
    }
    box->label("canceling");
}

void on_dont_cancle_bribe_click(Fl_Widget *widget, void *data)
{
    if (game.getPlayerAt(game.turnNum()).getRole().bribe())
    {
        playerAvailableActionNums++;


        if (playerAvailableActionNums <= 0)
        {

            blueWindow->hide();
            game.getPlayerAt(game.turnNum()).getRole().turnWasDone();
            game.setPlayerOut(false);
            playerAvailableActionNums = 1;
            game.nextTurn();
            Fl_JPEG_Image *originalImage = new Fl_JPEG_Image("pic.jpg");
            Fl_Image *backgroundImage = originalImage->copy(Fl::w(), Fl::h());
            delete originalImage;
            blueWindow = new Fl_Window(Fl::w(), Fl::h(), "Game");

            Fl_Box *blueBackground = new Fl_Box(0, 0, Fl::w(), Fl::h());
            blueBackground->image(backgroundImage);
            blueBackground->box(FL_FLAT_BOX);
            createButtons(blueWindow, Fl::w(), Fl::h());
            blueBackground->box(FL_FLAT_BOX);
            blueBackground->color(FL_BLUE);
            blueWindow->end();
            blueWindow->show();
        }
    }
}

void on_cancle_tax_click(Fl_Widget *widget, void *data)
{
    playerAvailableActionNums--;

    cout << game.getPlayerAt(game.turnNum()).getRole().getCoins() << endl;

    if (playerAvailableActionNums <= 0)
    {

        blueWindow->hide();
        game.getPlayerAt(game.turnNum()).getRole().turnWasDone();
        game.setPlayerOut(false);
        playerAvailableActionNums = 1;
        game.nextTurn();
        Fl_JPEG_Image *originalImage = new Fl_JPEG_Image("pic.jpg");
        Fl_Image *backgroundImage = originalImage->copy(Fl::w(), Fl::h());
        delete originalImage;
        blueWindow = new Fl_Window(Fl::w(), Fl::h(), "Game");

        Fl_Box *blueBackground = new Fl_Box(0, 0, Fl::w(), Fl::h());
        blueBackground->image(backgroundImage);
        blueBackground->box(FL_FLAT_BOX);

        createButtons(blueWindow, Fl::w(), Fl::h());
        blueBackground->box(FL_FLAT_BOX);
        blueBackground->color(FL_BLUE);
        blueWindow->end();
        blueWindow->show();
    }
}

void on_dont_cancle_tax_click(Fl_Widget *widget, void *data)
{
    if (game.getPlayerAt(game.turnNum()).getRole().tax())
    {
        playerAvailableActionNums--;
        cout << game.getPlayerAt(game.turnNum()).getRole().getCoins() << endl;

        if (playerAvailableActionNums <= 0)
        {

            blueWindow->hide();
            game.getPlayerAt(game.turnNum()).getRole().turnWasDone();
            game.setPlayerOut(false);
            playerAvailableActionNums = 1;
            game.nextTurn();
            Fl_JPEG_Image *originalImage = new Fl_JPEG_Image("pic.jpg");
            Fl_Image *backgroundImage = originalImage->copy(Fl::w(), Fl::h());
            delete originalImage;
            blueWindow = new Fl_Window(Fl::w(), Fl::h(), "Game");

            Fl_Box *blueBackground = new Fl_Box(0, 0, Fl::w(), Fl::h());
            blueBackground->image(backgroundImage);
            blueBackground->box(FL_FLAT_BOX);
            createButtons(blueWindow, Fl::w(), Fl::h());
            blueBackground->box(FL_FLAT_BOX);
            blueBackground->color(FL_BLUE);
            blueWindow->end();
            blueWindow->show();
        }
    }
}

void createButtons(Fl_Window *window, int screenWidth, int screenHeight)
{

    if (game.getPlayerAt(game.turnNum()).getRole().getName() == "Merchant" && game.getPlayerAt(game.turnNum()).getRole().getCoins() >= 3)
    {
        game.getPlayerAt(game.turnNum()).getRole().addCoins(1);
    }
    if (game.getPlayerAt(game.turnNum()).getRole().getCoins() >= 10)
    {
        Fl_Button *btn6 = new Fl_Button(Fl::w() / 2, Fl::h() / 2, 100, 30, "coup");
        btn6->callback(coup_callback, window);
    }

    else
    {

        int buttonCount = 6;
        cout << "your name is:" << game.getPlayerAt(game.turnNum()).getRole().getName() << endl;
        if (game.getPlayerAt(game.turnNum()).getRole().getName() == "Baron")
        {
            buttonCount = 7;
        }
        if (game.getPlayerAt(game.turnNum()).getRole().getName() == "Spy")
        {
            buttonCount = 8;
        }

        int buttonWidth = 300; // רוחב סביר לכפתור
        int buttonHeight = 40; // גובה סביר לכפתור
        int startX = screenWidth - buttonWidth - 50;
        ;                                                             // מרכז הכפתור לאורך ה-X
        int startY = (screenHeight - buttonHeight * buttonCount) / 2; // מרכז הכפתור לאורך ה-Y

        // צבע אפור בינוני (לא כהה ולא בהיר מדי)
        Fl_Color buttonColor = fl_rgb_color(169, 169, 169); // אפור (#A9A9A9)

        // יצירת כפתורים
        Fl_Button *btn1 = new Fl_Button(startX, startY, buttonWidth, buttonHeight, "gather");
        btn1->color(buttonColor); // הגדרת צבע לכפתור
        btn1->callback([](Fl_Widget *w, void *data)
                       { 
        if( game.getPlayerAt(game.turnNum()).getRole().gather()){
            playerAvailableActionNums--;
            
            if(playerAvailableActionNums<=0){
             w->window()->hide(); 
             game.getPlayerAt(game.turnNum()).getRole().turnWasDone();
             game.setPlayerOut(false);
             playerAvailableActionNums=1;
             game.nextTurn();
             
             Fl_JPEG_Image *originalImage = new Fl_JPEG_Image("pic.jpg");
Fl_Image *backgroundImage = originalImage->copy(Fl::w(), Fl::h());
delete originalImage;

             blueWindow = new Fl_Window(Fl::w(), Fl::h(), "Game");
             
             Fl_Box *blueBackground = new Fl_Box(0, 0, Fl::w(), Fl::h());
blueBackground->image(backgroundImage);
blueBackground->box(FL_FLAT_BOX);

             createButtons(blueWindow,Fl::w(),Fl::h());
             blueBackground->box(FL_FLAT_BOX);
             blueBackground->color(FL_BLUE); 
             blueWindow->end();
            blueWindow->show();
             }
        } });

        Fl_Button *btn2 = new Fl_Button(startX, startY + buttonHeight + 10, buttonWidth, buttonHeight, "tax");
        btn2->color(buttonColor); // הגדרת צבע לכפתור
        btn2->callback([](Fl_Widget *w, void *data)
                       {
                           bool foundGov = false;

                           if (!game.getPlayerAt(game.turnNum()).getRole().getIfBanned())
                           {

                               for (int i = 0; i < game.getPlayersNum(); i++)
                               {
                                   if (game.getPlayerAt(i).getRole().getName() == "Governor")
                                   {
                                       cout << "we have Governor" << endl;
                                       foundGov = true;
                                       Fl_Window *cancleWindow = new Fl_Window(300, 150, "ביטול פעולה");

                                       Fl_Box *box = new Fl_Box(20, 20, 260, 30, "General,do you want to cancle?");
                                       box->box(FL_UP_BOX);
                                       box->labelfont(FL_BOLD);
                                       box->labelsize(16);
                                       box->labelcolor(FL_BLACK);

                                       // כפתור לביטול
                                       Fl_Button *button1 = new Fl_Button(50, 80, 90, 30, "cancle");
                                       button1->callback(on_cancle_tax_click, cancleWindow);

                                       // כפתור לאי-ביטול
                                       Fl_Button *button2 = new Fl_Button(160, 80, 90, 30, " dont cancle");
                                       button2->callback(on_dont_cancle_tax_click, cancleWindow);

                                       cancleWindow->end();
                                       cancleWindow->set_modal(); // כדי לחסום את החלון הראשי בזמן הצגת החלון הזה
                                       cancleWindow->show();
                                   }
                               }
                               if (!foundGov)
                               {
                                   if (game.getPlayerAt(game.turnNum()).getRole().tax())
                                   {
                                       playerAvailableActionNums--;
                                       cout << game.getPlayerAt(game.turnNum()).getRole().getCoins() << endl;

                                       if (playerAvailableActionNums <= 0)
                                       {

                                           blueWindow->hide();
                                           game.getPlayerAt(game.turnNum()).getRole().turnWasDone();
                                           game.setPlayerOut(false);
                                           playerAvailableActionNums = 1;
                                           game.nextTurn();
                                           Fl_JPEG_Image *originalImage = new Fl_JPEG_Image("pic.jpg");
                                           Fl_Image *backgroundImage = originalImage->copy(Fl::w(), Fl::h());
                                           delete originalImage;
                                           blueWindow = new Fl_Window(Fl::w(), Fl::h(), "Game");

                                           Fl_Box *blueBackground = new Fl_Box(0, 0, Fl::w(), Fl::h());
                                           blueBackground->image(backgroundImage);
                                           blueBackground->box(FL_FLAT_BOX);
                                           createButtons(blueWindow, Fl::w(), Fl::h());
                                           blueBackground->box(FL_FLAT_BOX);
                                           blueBackground->color(FL_BLUE);
                                           blueWindow->end();
                                           blueWindow->show();
                                       }
                                   }
                               }
                           }
                       });

        Fl_Button *btn3 = new Fl_Button(startX, startY + 2 * (buttonHeight + 10), buttonWidth, buttonHeight, "bribe");
        btn3->color(buttonColor); // הגדרת צבע לכפתור
        btn3->callback([](Fl_Widget *w, void *data)
                       {
                           if (game.getPlayerAt(game.turnNum()).getRole().getCoins() >= 4)
                           {
                               bool foundJud = false;

                               for (int i = 0; i < game.getPlayersNum(); i++)
                               {
                                   if (game.getPlayerAt(i).getRole().getName() == "Judge")
                                   {
                                       foundJud = true;
                                       cout << "we have general" << endl;
                                       Fl_Window *cancleWindow = new Fl_Window(300, 150, "ביטול פעולה");

                                       Fl_Box *box = new Fl_Box(20, 20, 260, 30, "General,do you want to cancle?");
                                       box->box(FL_UP_BOX);
                                       box->labelfont(FL_BOLD);
                                       box->labelsize(16);
                                       box->labelcolor(FL_BLACK);

                                       // כפתור לביטול
                                       Fl_Button *button1 = new Fl_Button(50, 80, 90, 30, "cancle");
                                       button1->callback(on_cancle_bribe_click, cancleWindow);

                                       // כפתור לאי-ביטול
                                       Fl_Button *button2 = new Fl_Button(160, 80, 90, 30, " dont cancle");
                                       button2->callback(on_dont_cancle_bribe_click, cancleWindow);

                                       cancleWindow->end();
                                       cancleWindow->set_modal(); // כדי לחסום את החלון הראשי בזמן הצגת החלון הזה
                                       cancleWindow->show();
                                   }
                               }
                               if (!foundJud)
                               {
                                   if (game.getPlayerAt(game.turnNum()).getRole().bribe())
                                   {
                                       playerAvailableActionNums++;

                                       cout << game.turnNum() << endl;


                                       if (playerAvailableActionNums <= 0)
                                       {

                                           blueWindow->hide();
                                           game.getPlayerAt(game.turnNum()).getRole().turnWasDone();
                                           game.setPlayerOut(false);
                                           playerAvailableActionNums = 1;
                                           game.nextTurn();
                                           Fl_JPEG_Image *originalImage = new Fl_JPEG_Image("pic.jpg");
                                           Fl_Image *backgroundImage = originalImage->copy(Fl::w(), Fl::h());
                                           delete originalImage;
                                           blueWindow = new Fl_Window(Fl::w(), Fl::h(), "Game");

                                           Fl_Box *blueBackground = new Fl_Box(0, 0, Fl::w(), Fl::h());
                                           blueBackground->image(backgroundImage);
                                           blueBackground->box(FL_FLAT_BOX);
                                           createButtons(blueWindow, Fl::w(), Fl::h());
                                           blueBackground->box(FL_FLAT_BOX);
                                           blueBackground->color(FL_BLUE);
                                           blueWindow->end();
                                           blueWindow->show();
                                       }
                                   }
                                   foundJud = false;
                               }
                           }
                       });

        Fl_Button *btn4 = new Fl_Button(startX, startY + 3 * (buttonHeight + 10), buttonWidth, buttonHeight, "arrest");
        btn4->color(buttonColor); // הגדרת צבע לכפתור
        btn4->callback(arrest_callback, window);

        Fl_Button *btn5 = new Fl_Button(startX, startY + 4 * (buttonHeight + 10), buttonWidth, buttonHeight, "sanction");
        btn5->color(buttonColor); // הגדרת צבע לכפתור
        btn5->callback(sanction_callback, window);

        Fl_Button *btn6 = new Fl_Button(startX, startY + 5 * (buttonHeight + 10), buttonWidth, buttonHeight, "coup");
        btn6->color(buttonColor);
        btn6->callback(coup_callback, window);

        if (game.getPlayerAt(game.turnNum()).getRole().getName() == "Baron")
        {
            Fl_Button *btn7 = new Fl_Button(startX, startY + 6 * (buttonHeight + 10), buttonWidth, buttonHeight, "invest");
            btn7->color(buttonColor); // הגדרת צבע לכפתור
            btn7->callback([](Fl_Widget *w, void *data)
                           { 
        if(game.getPlayerAt(game.turnNum()).getRole().invest()){
            playerAvailableActionNums--;
            cout<<playerAvailableActionNums<<endl;
            game.players();
            if(playerAvailableActionNums<=0){
             w->window()->hide();
             Fl_JPEG_Image *originalImage = new Fl_JPEG_Image("AIcave.jpg");
             Fl_Image *backgroundImage = originalImage->copy(Fl::w(), Fl::h());
             delete originalImage;

             blueWindow = new Fl_Window(Fl::w(), Fl::h(), "Game");
             
             Fl_Box *blueBackground = new Fl_Box(0, 0, Fl::w(), Fl::h());
blueBackground->image(backgroundImage);
blueBackground->box(FL_FLAT_BOX);
             
             //Fl_Box *blueBackground = new Fl_Box(0, 0, Fl::w(), Fl::h());
             createButtons(blueWindow,Fl::w(),Fl::h());
             blueBackground->box(FL_FLAT_BOX);
             blueBackground->color(FL_BLUE);  
             game.getPlayerAt(game.turnNum()).getRole().turnWasDone();
             game.setPlayerOut(false);
             playerAvailableActionNums=1;
             game.nextTurn();
             
             blueWindow->end();
            blueWindow->show();
             }
        } });
        }
        if (game.getPlayerAt(game.turnNum()).getRole().getName() == "Spy")
        {
            Fl_Button *btn7 = new Fl_Button(startX, startY + 6 * (buttonHeight + 10), buttonWidth, buttonHeight, "see coins");
            btn7->color(buttonColor); // הגדרת צבע לכפתור
            btn7->callback(seeCoins_windowCallback, window);

            Fl_Button *btn8 = new Fl_Button(startX, startY + 7 * (buttonHeight + 10), buttonWidth, buttonHeight, "prevent arrest");
            btn8->color(buttonColor); // הגדרת צבע לכפתור
            btn8->callback(preventArrest_windowCallback, window);
        }
    }
}

void onStartGame(Fl_Widget *, void *)
{
    if (game.getPlayersNum() < 2)
    {
        cout << "you must have at least 2 players" << endl;
        return;
    }
    window->hide();
    int screenWidth = Fl::w();
    int screenHeight = Fl::h();

    Fl_JPEG_Image *originalImage = new Fl_JPEG_Image("pic.jpg");
    Fl_Image *backgroundImage = originalImage->copy(Fl::w(), Fl::h());
    delete originalImage;

    blueWindow = new Fl_Window(screenWidth, screenHeight, "Game");

    Fl_Box *blueBackground = new Fl_Box(0, 0, Fl::w(), Fl::h());
    blueBackground->image(backgroundImage);
    blueBackground->box(FL_FLAT_BOX);

    int coins = game.getPlayerAt(game.turnNum()).getRole().getCoins();

    std::string coinsStr = std::to_string(coins);
    string name = game.getPlayerAt(game.turnNum()).getName();
    label1 = new Fl_Box(20, 30, 150, 30);
    label1->copy_label(game.getPlayerAt(game.turnNum()).getName().c_str());
    label1->labelfont(FL_HELVETICA_BOLD);
    label1->labelsize(25);
    label1->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);

    // טקסט שני מתחת לראשון
    label2 = new Fl_Box(20, 70, 150, 30);
    label2->copy_label(coinsStr.c_str());
    label2->labelfont(FL_HELVETICA_BOLD);
    label2->labelsize(25);
    label2->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);

    label3 = new Fl_Box(20, 110, 150, 30);
    label3->copy_label(game.getPlayerAt(game.turnNum()).getRole().getName().c_str());
    label3->labelfont(FL_HELVETICA_BOLD);
    label3->labelsize(25);
    label3->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);

    playerAvailableActionNums = 1;

    createButtons(blueWindow, screenWidth, screenHeight);

    blueWindow->end();
    blueWindow->show();
}

int main()
{
    int screenWidth = Fl::w();
    int screenHeight = Fl::h();

    Fl_JPEG_Image *originalImage = new Fl_JPEG_Image("AIcave.jpg");
    Fl_Image *backgroundImage = originalImage->copy(screenWidth, screenHeight);
    delete originalImage;

    window = new Fl_Window(screenWidth, screenHeight, "The Game");
    Fl_Box *backgroundBox = new Fl_Box(0, 0, screenWidth, screenHeight);
    backgroundBox->image(backgroundImage);
    backgroundBox->box(FL_FLAT_BOX);

    // שדות קלט וכפתורים
    nameInput = new Fl_Input(screenWidth / 2 - 100, 30, 200, 30, "Name:");
    nameInput->labelcolor(FL_RED);

    Fl_Button *saveButton = new Fl_Button(screenWidth / 2 - 130, 150, 120, 40, "Save Player");
    saveButton->callback(onSaveLobby);

    Fl_Button *startButton = new Fl_Button(screenWidth / 2 + 10, 150, 120, 40, "Start Game");
    startButton->callback(onStartGame);

    // תיבת אישור חדשה בתחתית החלון
    confirmationBox = new Fl_Box(0, screenHeight - 50, screenWidth, 30);
    confirmationBox->align(FL_ALIGN_CENTER);
    confirmationBox->labelfont(FL_BOLD);
    confirmationBox->labelsize(16);
    confirmationBox->labelcolor(FL_RED);
    confirmationBox->box(FL_NO_BOX); // ללא רקע

    window->end();
    window->show();
    return Fl::run();
}