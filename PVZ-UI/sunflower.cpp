#include "sunflower.h"

Sunflower::Sunflower()
{
    life = 300;
    time = int(10.0*1000/33);
    setMovie("://image/Sunflower.gif");
}

void Sunflower::advance(int phase)
{
    if(!phase)
        return ;
    update();
    if(life<=0)
        delete this;
    else if(++counter>=time)
    {
        counter=0;
        scene()->addItem(new Sun(pos()));
    }
}
