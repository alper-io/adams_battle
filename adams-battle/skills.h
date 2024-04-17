#ifndef  SKILLS_H
#define  SKILLS_H

#include <iostream>
#include "card.h"
#include <vector>


using namespace std;

typedef void (*FunctionPointer)();

void skill1() ;
void skill2() ;
void skill3() ;
void skill4() ;
void skill5() ;
void skill6() ;
void skill7() ;
void skill8() ;
void skill9() ;
void skill10() ;
void skill11() ;
void skill12() ;

void getSkills(FunctionPointer* skills, int size) ;
void assignSkills(Card** cards, FunctionPointer* skills, int size) ;


#endif // SKILLS_H
