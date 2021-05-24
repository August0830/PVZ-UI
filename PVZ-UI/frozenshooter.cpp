#include "frozenshooter.h"

FrozenShooter::FrozenShooter()
{
    life = 300;
    attack = 25;
    time=int(1.4*1000/33);
    setMovie("://image/FrozenShooter.gif");
}

void FrozenShooter::advance(int phase)
{
    if(!phase)
        return;
    update();
    if(life<=0)
        delete this;
    else if(++counter>=time)
    {
        counter=0;
        if(!collidingItems().empty())
        {
            Bullet* bullet = new Bullet(attack,true);//设定成是寒冰效果的子弹
            bullet->setX(x()+32);
            bullet->setY(y());
            scene()->addItem(bullet);
            return;
        }
    }
}

bool FrozenShooter::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    return other->type()==Zombie::Type && qFuzzyCompare(other->y(),y());
}
