#include "peashooter.h"

PeaShooter::PeaShooter()
{
    attack=25;
    life=300;
    time = int(1.4*1000/33);
    setMovie("://image/PeaShooter.gif");
}

void PeaShooter::advance(int phase)
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
            Bullet* bullet = new Bullet(attack);
            bullet->setX(x()+32);
            bullet->setY(y());
            scene()->addItem(bullet);
            return;
        }
    }
}

bool PeaShooter::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    return other->type()==Zombie::Type && qFuzzyCompare(other->y(),y());//检查本行有无僵尸 不需要相邻
}
