#include "card.h"
#include "player.h"
#include "game.h"
#include "skills.h"
#include <string>
#include <vector>
#include <iostream>

Player::Player(std::string name = "None") : name(name),deck(nullptr)
{

    deck = new Card*[7] ;

    for (int i = 0; i < 7; i++)
    {
        deck[i] = nullptr;
    }

}

Player::~Player()
{
    delete[] deck;
}

void Player::playCard(vector<Card*> &hand, vector<Card*> &field)
{
    cout << "Select a card to play from your deck:  " ;

    int select;
    cin >> select;

    while(select > hand.size() || select <= 0)
    {
        cout << "\ninvalid choice try again: " ;
        cin >> select;
    }


    if (hand[select-1]->cardType == "Marksman")
    {
        field.push_back(new Marksman(*hand[select-1])) ;
    }
    else if (hand[select-1]->cardType == "Tank")
    {
        field.push_back(new Tank(*hand[select-1])) ;
    }
    else if (hand[select-1]->cardType == "Mage")
    {
        field.push_back(new Mage(*hand[select-1])) ;
    }
    else if (hand[select-1]->cardType == "Assasin")
    {
        field.push_back(new Assasin(*hand[select-1])) ;
    }
    else if (hand[select-1]->cardType == "Support")
    {
        field.push_back(new Support(*hand[select-1])) ;
    }


    delete hand[select-1] ;
    hand.erase(hand.begin()+select-1) ;

}
