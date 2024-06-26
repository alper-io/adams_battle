#pragma once

#include "card.h"
#include "player.h"
#include "skills.h"
#include <Windows.h>
#include <iomanip>
#include <vector>
#include <string>
#include <iostream>

class Game {
public:



    Game();  // Constructor
    ~Game(); // Destructor


    void play(Player &p1, Player &p2) ;
    void selectDeck(Player &p, vector<vector<Card*>> preDecks, Card** cards, int cardsSize) ;



};

void battleScreen(vector<Card*> &field1,vector<Card*> &field2,int round) ;
void viewCards(Card** cards, int cardsSize) ;
void infoCard(Card** cards, int cardsSize) ;
void displayScreen(Player &p1, Player &p2,vector<Card*> &hand1,vector<Card*> &hand2,vector<Card*> &field1,vector<Card*> &field2,int turn) ;
