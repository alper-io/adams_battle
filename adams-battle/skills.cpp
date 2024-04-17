#include <iostream>
#include "card.h"
#include "skills.h"
#include "player.h"
#include "game.h"

#include <vector>
using namespace std ;
typedef void (*FunctionPointer)();

void skill1() // BROMEN's skill
{
    cout << "BROMEN ADAM!" ;
}


void skill2() // Mobayi
{

}

void skill3() // Jagu
{

}

void skill4() // Atreus
{

}

void skill5() // Marcus Aurelius
{

}

void skill6() // yusuf
{

}

void skill7() // Mona Lisa
{

}

void skill8() // Bedocan
{

}

void skill9() // Lorach
{

}

void skill10() // Umai
{

}

void skill11() // Bebi
{

}

void getSkills(FunctionPointer* skills, int size)
{
    skills[0] = nullptr;
    skills[1] = skill1;
    skills[2] = skill2;
    skills[3] = skill3;
    skills[4] = skill4;
    skills[5] = skill5;
    skills[6] = skill6;
    skills[7] = skill7;
    skills[8] = skill8;
    skills[9] = skill9;
    skills[10] = skill10;
    skills[11] = skill11;


}

void assignSkills(Card** cards, FunctionPointer* skills,int size)
{
    for (int i = 0; i <size; i++)
    {
        cards[i]->skill = skills[i];
    }
}
