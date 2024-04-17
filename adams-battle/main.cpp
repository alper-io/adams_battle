#include "card.h"
#include "skills.h"
#include "game.h"
#include "player.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#define CARDCOUNT 12  // how many cards do we have

using namespace std;
typedef void (*FunctionPointer)(); // void function pointer type

    // functions
int displayMainMenu() ;
int credits() ;
void assignSkills(Card** cards, FunctionPointer* skills, int size) ;
void readCardsFromFile(const string& filename,Card** cards ,int size) ;




int main()
{

    // get card array dynamically

    Card** cards = new Card*[CARDCOUNT] ;
    readCardsFromFile("cards.txt",cards,CARDCOUNT);

     // get skills array dynamically. skills is a function pointer array
    FunctionPointer* skills = new FunctionPointer[CARDCOUNT];
    getSkills(skills,CARDCOUNT) ;  // skills.h

    // assign skill to each card
    assignSkills(cards,skills,CARDCOUNT) ; // skills.h

    Card* d1[] = {cards[1],cards[2],cards[3],cards[4],cards[5],cards[6],cards[7]} ;
    Card* d2[] = {cards[11],cards[10],cards[9],cards[8],cards[7],cards[6],cards[5]} ;

    vector<vector<Card*>> preDecks ;

    preDecks.push_back(vector<Card*> (begin(d1), end(d1))) ;
    preDecks.push_back(vector<Card*> (begin(d2), end(d2))) ;


    Player p1("Player 1");
    Player p2("Player 2");

    Game game;

    // start program
    int quitVariable = 0 ;
    while(quitVariable != 1)
    {
        switch(displayMainMenu())
        {
            case 1:
                // Play vs Computer



                break;
            case 2:
                // Player vs Player



                game.selectDeck(p1,preDecks,cards,CARDCOUNT) ;
                game.selectDeck(p2,preDecks,cards,CARDCOUNT) ;
                game.play(p1,p2) ;


                break;
            case 3:
                // Tutorial
                break ;
            case 4:
                // view all Cards
                viewCards(cards,CARDCOUNT) ;
                break ;
            case 5:
                // credits
                credits() ;
                break ;
            case 6:
                cout << "\n\nExiting the game.." ;
                quitVariable = 1 ; // exit while loop and end the program
                break ;
            default:
                cout << "\nInvalid choice! Please select a number!\n" ;
                break;
        }
    }


    // Deallocate Memory
    for(int i = 0; i<CARDCOUNT; i++)
    {
        delete cards[i];
    }
    delete[] cards ;



    delete[] skills;

    return(0) ;
}

int displayMainMenu()
{
    int a;
    system("cls") ;
    cout << "Press the number you want to select.\n\n" ;
    cout << "1. Player vs Computer\n" ;
    cout << "2. Player vs Player\n" ;
    cout << "3. Tutorial\n" ;
    cout << "4. Cards\n" ;
    cout << "5. Credits\n" ;
    cout << "6. Quit\n\n" ;

    cin >> a ;
    return(a) ;

}



void readCardsFromFile(const string& filename, Card** cards ,int size)
{
    ifstream cardFile(filename);

    if (!cardFile.is_open())
    {
        cerr << "Error opening the file!" << endl;
    }


    int i;
    string cardtype ;


    for(i = 0; i<size; i++)
    {

        getline(cardFile, cardtype, '\t');

        if(cardtype == "Assasin")
        {
            cards[i] = new Assasin();
        }
        else if(cardtype == "Tank")
        {
            cards[i] = new Tank();

        }
        else if(cardtype == "Mage")
        {
            cards[i] = new Mage();

        }
        else if(cardtype == "Marksman")
        {
            cards[i] = new Marksman();

        }
        else if(cardtype == "Support")
        {
            cards[i] = new Support();

        }
        else
        {
            continue;
        }

        int hp, atk ;
        cards[i]->cardType = cardtype ;
        getline(cardFile, cards[i]->element, '\t');
        getline(cardFile, cards[i]->name, '\t');
        cardFile >> cards[i]->cardIndex ;
        cardFile >> ws;
        cardFile >> hp;
        cardFile >> ws;
        cardFile >> atk;
        cardFile >> ws;
        getline(cardFile, cards[i]->skillString, '\n') ;

        cards[i]->setAtk(atk) ;
        cards[i]->setHp(hp) ;


    }

    cardFile.close();

}

void tutorial()
{
    system("cls") ;
    cout << "Welcome to tutorial. Select the topic you want to learn.\n\n" ;

    cout << "1. Card Types" ;
    cout << "Creating a deck" ;

}



int credits()
{
    system("cls") ;
    cout << "Developers\n" << endl;
    cout << "Kaan Aydemir" << endl;
    cout << "Edip Alper Selcuk" << endl;
    cout << "Fatih Gazi Goc" << endl;



    cout << "\n\nPress anything to return main menu\n" ;
    cin.ignore(1000,'\n') ;
    getchar() ;

    return 0;
}
