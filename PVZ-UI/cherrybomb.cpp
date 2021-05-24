#include "cherrybomb.h"

CherryBomb::CherryBomb()
{
    attack=1800;
    life=300;
    setMovie("://image/CherryBomb.gif");
}

QRectF CherryBomb::boundingRect() const
{
    return state ? QRectF(-150,-150,300,300):Plant::boundingRect();
}

void CherryBomb::advance(int phase)
{
    if(!phase)
        return ;
    update();
    if(life<=0)
        delete this;
    else if(state==0 && movie->currentFrameNumber()==movie->frameCount()-1)
    {
        state=1;
        setMovie("://image/Boom.gif");
        QList<QGraphicsItem*> items = collidingItems();
        foreach(QGraphicsItem *item,items)
        {
            Zombie* zom=qgraphicsitem_cast<Zombie*>(item);
            zom->life-=attack;
            if(zom->life<=0)
            {
                zom->state=3;
                zom->setMovie("://image/Burn.gif");
            }

        }
    }
    else if(state==1 && movie->currentFrameNumber()==movie->frameCount()-1)//爆炸但是周围没有僵尸
        delete this;
}

bool CherryBomb::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    return other->type() == Zombie::Type && QLineF(pos(),other->pos()).length()<150;//检查上下左右的格子
}
