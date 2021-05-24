#include "doubleshooter.h"

DoubleShooter::DoubleShooter()
{
    attack=25;
    life=300;
    time = int(1.4*1000/33);
    setMovie("://image/DoubleShooter.gif");
}

void DoubleShooter::advance(int phase)
{
    if(!phase)
        return ;
    update();
    if(life<=0)
        delete this;
    else if(++counter>=time)
    {
        counter=0;
        if(!collidingItems().empty())
        {
            Bullet* bullet = new Bullet(attack);
            bullet->setX(x()+32);
            bullet->setY(y());
            scene()->addItem(bullet);
            //fist bullet
            bullet = new Bullet(attack);
            bullet->setX(x()+64);
            bullet->setY(y());
            scene()->addItem(bullet);
            //second bullet
            return;
        }
    }
}

bool DoubleShooter::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    return other->type()==Zombie::Type && qFuzzyCompare(other->y(),y());//检查本行有无僵尸 不需要相邻
}
