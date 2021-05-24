#include "nut.h"

Nut::Nut()
{
    life = 4000;
    setMovie("://image/Nut.gif");
}
void Nut::advance(int phase)
{
    if(!phase)
        return;
    update();
    if(life<=0)
        delete this;
    else if(life<=1333 && state!=2)
    {
        state=2;
        setMovie("://image/Nut2.gif");
    }
    else if(1333<life && life<=2667 && state!=1)
    {
        state=1;
        setMovie("://image/Nut1.gif");
    }
}
