#ifndef  PLAYER_H
#define  PLAYER_H
#include "card.h"
#include <string>
#include <vector>

class Player
{
public:

    Player(std::string name) ;

    std::string name;
    Card** deck;

    void playCard(vector<Card*> &hand, vector<Card*> &field) ;
    ~Player() ;

};




#endif //PLAYER_H
