#include "game.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <Windows.h>
#include <iomanip>
#include <typeinfo>
#include "card.h"
#include <vector>
#include "player.h"
#include "skills.h"

using namespace std;



Game::Game()
{

}

Game::~Game()
{

}

void Game::play(Player &p1, Player &p2)
{

    srand(time(0)) ;
    int round = 1;

    vector<Card*> cardVector1;
    for (int i = 0; i < 7; i++)
    {
        cardVector1.push_back(p1.deck[i]);
    }
    vector<Card*> cardVector2;

    for (int i = 0; i < 7; i++)
    {
        cardVector2.push_back(p2.deck[i]);
    }

    vector<Card*> hand1 ;
    vector<Card*> hand2 ;

    vector<Card*> field1 ;
    vector<Card*> field2 ;



for (Card* card : cardVector1) {
    if (card->cardType == "Marksman")
    {
        hand1.push_back(new Marksman(*card)) ;
    }
    else if (card->cardType == "Tank")
    {
        hand1.push_back(new Tank(*card)) ;
    }
    else if (card->cardType == "Mage")
    {
       hand1.push_back(new Mage(*card)) ;
    }
    else if (card->cardType == "Assasin")
    {
        hand1.push_back(new Assasin(*card)) ;
    }
    else if (card->cardType == "Support")
    {
        hand1.push_back(new Support(*card)) ;
    }
}

for (Card* card : cardVector2) {
    if (card->cardType == "Marksman")
    {
        hand2.push_back(new Marksman(*card)) ;
    }
    else if (card->cardType == "Tank")
    {
        hand2.push_back(new Tank(*card)) ;
    }
    else if (card->cardType == "Mage")
    {
        hand2.push_back(new Mage(*card)) ;
    }
    else if (card->cardType == "Assasin")
    {
        hand2.push_back(new Assasin(*card)) ;
    }
    else if (card->cardType == "Support")
    {
        hand2.push_back(new Support(*card)) ;
    }

}

    system("cls") ;

    for(int i=5; i>0; i--)
    {
        cout << "Game will start in " << i << " seconds. Get ready.\n" ;
        Sleep(1000) ;
    }

    // start game
    bool ending = false;
    int turn;

    while(ending == false)
    {
        if(round % 2 == 1)
        {
            turn = 1;
        }
        else if(round % 2 == 0)
        {
            turn = 2;
        }


        if(turn == 1)
        {
            displayScreen(p1,p2,hand1,hand2,field1,field2,round) ;

            if(!hand1.empty())
            {
                cout << "Player 1's turn. ";
                p1.playCard(hand1,field1) ;
            }
            displayScreen(p1,p2,hand1,hand2,field1,field2,round) ;

            if(!hand2.empty())
            {
                cout << "Player 2's turn. ";
                p2.playCard(hand2,field2) ;
            }
            displayScreen(p1,p2,hand1,hand2,field1,field2,round) ;


        }

        else if(turn == 2)
        {
            displayScreen(p1,p2,hand1,hand2,field1,field2,round) ;

            if(!hand2.empty())
            {
                cout << "Player 2's turn. ";
                p2.playCard(hand2,field2) ;
            }

            displayScreen(p1,p2,hand1,hand2,field1,field2,round) ;

            if(!hand1.empty())
            {
                cout << "Player 1's turn. ";
                p1.playCard(hand1,field1) ;
            }

            displayScreen(p1,p2,hand1,hand2,field1,field2,round) ;
        }

        cout << "\n\n" ;
        for(int i=3; i>0; i--)
        {
            cout << "Battle starting in " << i << " seconds\n" ;
            Sleep(1000) ;
        }
        battleScreen(field1,field2,round) ;
        round++ ;

        if(hand1.empty() == true && field1.empty() == true)
        {
            system("cls") ;
            cout << "\n\nPLAYER 2 WON THE GAME!\n\n" ;
            ending = true;
        }

        if(hand2.empty() == true && field2.empty() == true)
        {
            system("cls") ;
            cout << "\n\nPLAYER 1 WON THE GAME!\n\n" ;
            ending = true;
        }
        // bi taraf kaybederse ending = true
    } // while bitisi

    cout << "\nPress anything to return main menu" ;
    cin.ignore(1000,'\n') ;
    getchar() ;


    for (Card* card : hand1)
    {
        delete card;
    }

    for (Card* card : hand2)
    {
        delete card;
    }
    for (Card* card : field1)
    {
        delete card;
    }
    for (Card* card : field2)
    {
        delete card;
    }
    hand1.clear();
    hand2.clear();
    field1.clear();
    field2.clear();
    cardVector1.clear();
    cardVector2.clear();
}

void printBattle(vector<Card*> field1,vector<Card*> field2,int round)
{
    system("cls") ;
    cout << "                                       ROUND: " << round;
    cout << "\n\n\nFIELD 1:    " ;
    for(int i=0; i<field1.size(); i++)
    {
        field1[i]->cardImage() ;
        cout << "    " ;
    }
    cout << "\n\n\n____________________________________________________________________________________________________  damage advantages(x2):    water>fire; fire>earth; earth>water\n\n\n" ;

    cout << "FIELD 2:    " ;
    for(int i=0; i<field2.size(); i++)
    {
        field2[i]->cardImage() ;
        cout << "    " ;
    }
    cout << "\n\n\n\n" ;
    cout << "Battle Info:\n\n";
}

void battleScreen(vector<Card*> &field1,vector<Card*> &field2,int round)
{

    printBattle(field1,field2,round) ;
    Sleep(2000) ;

    for(int i=0; i<field1.size(); i++)
        {
            field1[i]->hasAttacked = false;
            field2[i]->hasAttacked = false;
        }

    int a,b;
    bool endRound = false;

    while(endRound == false)
    {
        if(round % 2 == 1)
        {
                for(a=0; a<field1.size(); a++)       // 1 field karti atak yapiyor
                {
                    if(field1[a]->hasAttacked == false && field2.size() > 0)
                    {
                        cout << "Player 1: " ;
                        field1[a]->attack(field2,round) ;
                        Sleep(4300) ;
                        break ;
                    }
                }

                for (int i = field2.size()-1; i >= 0; i--)   // 2.field ölenleri cikar
                    {
                        if (field2[i]->isDead())
                        {
                            cout << "\n" << field2[i]->name << " is dead!\n";
                            Sleep(3000);
                            delete field2[i];
                            field2.erase(field2.begin() + i);
                        }
                    }

                for(b=0; b<field2.size(); b++)    // 2. field attack yapiyor
                {
                    if(field2[b]->hasAttacked == false && field1.size() > 0)
                    {
                        cout << "Player 2: " ;
                        field2[b]->attack(field1,round) ;
                        Sleep(4300) ;
                        break ;
                    }
                }

                 for (int i = field1.size()-1; i >= 0; i--)  // 1. field ölenleri cikar
                    {
                        if (field1[i]->isDead())
                        {
                            cout << "\n" << field1[i]->name << " is dead!\n";
                            Sleep(3000);
                            delete field1[i];
                            field1.erase(field1.begin() + i);
                        }
                    }

                endRound = true;
                for(int i=0; i<field1.size(); i++) // butun cardlar saldirmis mi diye kontrol et, eger bir tane bile varsa roundu bitirme 1.field
                {
                    if(field1[i]->hasAttacked == false && field2.size() >0)
                    {
                        endRound = false ;
                        break ;
                    }
                    else{continue;}
                }
                for(int i=0; i<field2.size(); i++) // butun cardlar saldirmis mi diye kontrol et, eger bir tane bile varsa roundu bitirme 2.field
                {
                    if(field2[i]->hasAttacked == false && field1.size() >0)
                    {
                        endRound = false ;
                        break ;
                    }
                    else{continue;}
                }


        }


        else if(round % 2 == 0)
        {
            for(b=0; b<field2.size(); b++)       // 2. field karti atak yapiyor
                {
                    if(field2[b]->hasAttacked == false && field1.size() > 0)
                    {
                        cout << "Player 2: " ;
                        field2[b]->attack(field1,round) ;
                        Sleep(4300) ;
                        break ;
                    }
                }

                 for (int i = field1.size()-1; i >= 0; i--) // 1. field ölenleri cikar
                    {
                        if (field1[i]->isDead())
                        {
                            cout << "\n" << field1[i]->name << " is dead!\n";
                            Sleep(3000);
                            delete field1[i];
                            field1.erase(field1.begin() + i);
                        }
                    }

                for(a=0; a<field1.size(); a++)    // 1. field attack yapiyor
                {
                    if(field1[a]->hasAttacked == false && field2.size() > 0)
                    {
                        cout << "Player 1: " ;
                        field1[a]->attack(field2,round) ;
                        Sleep(4300) ;
                        break ;
                    }
                }

                 for (int i = field2.size()-1; i >= 0; i--) // 2.field ölenleri cikar
                    {
                        if (field2[i]->isDead())
                        {
                            cout << "\n" << field2[i]->name << " is dead!\n";
                            Sleep(3000);
                            delete field2[i];
                            field2.erase(field2.begin() + i);
                        }
                    }

                endRound = true;
                for(int i=0; i<field1.size(); i++) // butun cardlar saldirmis mi diye kontrol et, eger bir tane bile varsa roundu bitirme 1.field
                {
                    if(field1[i]->hasAttacked == false && field2.size() >0)
                    {
                        endRound = false ;
                        break ;
                    }
                    else{continue;}
                }
                for(int i=0; i<field2.size(); i++) // butun cardlar saldirmis mi diye kontrol et, eger bir tane bile varsa roundu bitirme 2.field
                {
                    if(field2[i]->hasAttacked == false && field1.size() >0)
                    {
                        endRound = false ;
                        break ;
                    }
                    else{continue;}
                }
        }
    } // end of round

    cout << "\nEnd of Round " << round  ;
    Sleep(4000) ;


}

void displayScreen(Player &p1, Player &p2,vector<Card*> &hand1,vector<Card*> &hand2,vector<Card*> &field1,vector<Card*> &field2,int round)
{

    /*

*/
    system("cls") ;


    cout << p1.name << "\n\n";
    cout << "Deck 1:     name    atk   hp    type     element\n\n" ;

    for (int i = 0; i < hand1.size(); i++)
    {
        cout << "     " << i+1 << ")    " << hand1[i]->name ;
        for(int x=10-hand1[i]->name.length(); x>=0; x--)
            {
                cout << " ";
            }
            cout << hand1[i]->getAtk() << "  " << hand1[i]->getHp() << "  " << hand1[i]->cardType ;
            for(int x=10-hand1[i]->cardType.length(); x>=0; x--)
            {
                cout << " ";
            }
            cout << hand1[i]->element;


        cout << "\n";
    }

    cout << "\n\n\n                                    BATTLE FIELD\n\n\n" ;
    cout << "Player 1 area:       " ;
    for(int i = 0; i<field1.size(); i++)
    {
        field1[i]->cardImage() ;
        cout << "    " ;
    }

    cout << "\n\n\nROUND: " << round << "__________________________________________________________________________________________________________   damage advantages(x2):    water>fire; fire>earth; earth>water\n\n\n" ;

    cout << "Player 2 area:       " ;
    for(int i = 0; i<field2.size(); i++)
    {
        field2[i]->cardImage() ;
        cout << "    " ;
    }

    cout << "\n\n\n\n" << p2.name << "\n\n";
   cout << "Deck 1:     name    atk   hp    type     element\n\n" ;

    for (int i = 0; i < hand2.size(); i++)
    {
        cout << "     " << i+1 << ")    " << hand2[i]->name ;
        for(int x=10-hand2[i]->name.length(); x>=0; x--)
            {
                cout << " ";
            }
            cout << hand2[i]->getAtk() << "  " << hand2[i]->getHp() << "  " << hand2[i]->cardType;
            for(int x=10-hand2[i]->cardType.length(); x>=0; x--)
            {
                cout << " ";
            }
            cout << hand2[i]->element ;

        cout << "\n";
    }
    cout << "\n\n" ;





}

bool checkError(Card** cards, Player &p,int choose ,int cardsSize)  // check if user selecting same card
{
    for(int x = 0; x<7; x++)
    {
        if(p.deck[x] == cards[choose])
        {
            cout << "\nYou cant select same card\n\n" ;
            return false;
        }
    }
    return true;
}

void Game::selectDeck(Player &p, vector<vector<Card*>> preDecks , Card** cards, int cardsSize )  // user selecting deck
{


    cout << "\n\n" << p.name << " Select one." ;
    cout << "\n\n1.Use existing deck" ;
    cout << "\n2.Create your deck\n" ;

    int select;
    cin >> select;

    if(select == 1)
    {

        for(int i = 0; i<preDecks.size(); i++)
        {
            cout << "\n" << i+1 << "." << "Deck: "  ;

            for(int x = 0; x<7; x++)
            {
               cout << preDecks[i][x]->name << " - " ;
            }
        }
        cout << "\n\n\nSelect your deck\n" ;
        int s;
        cin >> s;

        for(int i = 0; i<7; i++)
        {
            p.deck[i] = preDecks[s-1][i] ;
        }

    }

    else if(select == 2)
    {
        infoCard(cards,cardsSize) ;


        for(int i = 0; i<7; i++) // 7 card secimi
        {

            int choose ;

            do
            {
                cout << "\nSelect " << i+1 << ". card: " ;
                cin >> choose;
            }while(checkError(cards,p,choose,cardsSize) == false) ;

            p.deck[i] = cards[choose] ;
        }
    }

    system("cls") ;
    cout << p.name << " Deck:\n\n";
    for(int i = 0; i<7; i++)
    {
        cout << p.deck[i]->name << endl;
    }

    cout << "\n\n Press anything to continue." ;
    cin.ignore(1000,'\n') ;
    getchar() ;

}


void infoCard(Card** cards, int cardsSize)
{
    vector<Card*> fire;
    vector<Card*> water;
    vector<Card*> earth;

    int f = 0; // fire cards counter
    int w = 0; // water cards counter
    int e = 0; // earth cards counter

    for(int i = 0; i<cardsSize; i++)
    {
        if(cards[i]->element == "fire")
        {
            fire.push_back(cards[i]) ;
            f++;
        }
        else if(cards[i]->element == "water")
        {
            water.push_back(cards[i]) ;
            w++;
        }
        else if(cards[i]->element == "earth")
        {
            earth.push_back(cards[i]) ;
            e++;
        }
    }

        // display cards using setw


        cout << setw(17) << left << "Fire Cards" << setw(28) << left << "Water Cards" << setw(37) << left << "Earth Cards" << endl ;

        int x=0,y=0,z=0;


        while((x<f) && (y<w) && (z<e))
        {
            if(x<f)
            {
                cout << x << "." << setw(17) << left <<fire[x]->name ;
                x++ ;
            }
            else
            {
                cout << setw(17) << left << " " ;
            }

            if(y<w)
            {
                cout << f+y << "." << setw(26) << left << water[y]->name ;
                y++ ;
            }
            else
            {
                cout << setw(26) << left << " " ;
            }

            if(z<e)
            {
                cout << f+w+z << "." << setw(35) << left << earth[z]->name ;
                z++ ;
            }
            else
            {
                cout << " " ;
            }
            cout << "\n" ;

        }

    fire.clear();
    water.clear();
    earth.clear();
}


void viewCards(Card** cards, int cardsSize)
{
    vector<Card*> fire;
    vector<Card*> water;
    vector<Card*> earth;

    int f = 0; // fire cards counter
    int w = 0; // water cards counter
    int e = 0; // earth cards counter

    for(int i = 0; i<cardsSize; i++)
    {
        if(cards[i]->element == "fire")
        {
            fire.push_back(cards[i]) ;
            f++;
        }
        else if(cards[i]->element == "water")
        {
            water.push_back(cards[i]) ;
            w++;
        }
        else if(cards[i]->element == "earth")
        {
            earth.push_back(cards[i]) ;
            e++;
        }
    }

        // display cards using setw


        cout << setw(17) << left << "Fire Cards" << setw(28) << left << "Water Cards" << setw(37) << left << "Earth Cards" << endl ;

        int x=0,y=0,z=0;


        while((x<f) && (y<w) && (z<e))
        {
            if(x<f)
            {
                cout << x << "." << setw(17) << left <<fire[x]->name ;
                x++ ;
            }
            else
            {
                cout << setw(17) << left << " " ;
            }

            if(y<w)
            {
                cout << f+y << "." << setw(26) << left << water[y]->name ;
                y++ ;
            }
            else
            {
                cout << setw(26) << left << " " ;
            }

            if(z<e)
            {
                cout << f+w+z << "." << setw(35) << left << earth[z]->name ;
                z++ ;
            }
            else
            {
                cout << " " ;
            }
            cout << "\n" ;

        }

    string strS;
    int intS ;
    size_t pos;

        cout << "\nSelect the number of the card you want to view (press 'x' for returning main menu): " ;
        cin >> strS;
        if(strS == "x")
            {
                fire.clear();
                water.clear();
                earth.clear();
                return;
            }
        intS = stoi(strS,&pos) ;

        while( (intS<0) || (intS>=cardsSize || pos < strS.length()) )
        {
            cout << "\ninvalid choice try again.\n" ;
            cout << "\nSelect the number of the card you want to view (press 'x' for returning main menu): " ;
            cin >> strS;
            if(strS == "x")
            {
                fire.clear();
                water.clear();
                earth.clear();
                return;
            }

           intS = stoi(strS,&pos) ;
        }

    system("cls") ;

    for(int i=0; i<cardsSize; i++)
    {
        if(cards[i]->cardIndex == intS)
        {
            cards[i]->displayCard();
            cout << "\n\n" ;
            cards[i]->cardImage() ;
            break;
        }
    }

    cout << "\n\n\nPress enter to return:\n";
    cin.ignore(1000,'\n');
    getchar() ;

    fire.clear();
    water.clear();
    earth.clear();

    viewCards(cards,cardsSize);

}
