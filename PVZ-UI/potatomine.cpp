#include "potatomine.h"

PotatoMine::PotatoMine()
{
    attack=1800;
    life = 300;
    time = int(15.0*1000/33);
    setMovie("://image/PotatoMine1.gif");
}

QRectF PotatoMine::boundingRect() const
{
    return state==2 ? QRectF(-75,-75,150,150):Plant::boundingRect();
}

void PotatoMine::advance(int phase)
{
    if(!phase)
        return;
    update();
    if(life<=0)
        delete this;
    else if(state==0 && ++counter>=time)//超过一定时间才进入可以爆炸的阶段
    {
        state=1;
        counter=0;
        time=int(1.0*1000/33);
        setMovie("://image/PotatoMine.gif");
    }
    else if(state==1 && ++counter>=time)
    {
        counter=0;
        QList<QGraphicsItem*>items = collidingItems();
        if(!items.empty())
        {
            state=2;
            setMovie("://image/PotatoMineBomb.gif");
            foreach(QGraphicsItem *item,items)
            {
                Zombie* zom=qgraphicsitem_cast<Zombie*>(item);
                zom->life-=attack;
                if(zom->life<=0)
                    delete zom;
            }
        }
    }
    else if(state==2 && movie->currentFrameNumber()==movie->frameCount()-1)//帧数 播放到最后一帧作为停止判断条件
        delete this;//
}

bool PotatoMine::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    return other->type() == Zombie::Type && qFuzzyCompare(other->y(),y())
            && qAbs(other->x()-x())<50;
}
