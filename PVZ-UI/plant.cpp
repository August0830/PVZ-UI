#include "plant.h"
#include "zombie.h"
Plant::Plant()
{
    movie=nullptr;
    attack = 0;
    counter=0;
    state=0;
    time =0;
}
Plant::~Plant()
{
    delete movie;
}

QRectF Plant::boundingRect() const
{
    return QRectF(-35,-35,70,70);
}

void Plant::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawImage(boundingRect(),movie->currentImage());//打印动画效果
}

bool Plant::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)
    return other->type() == Zombie::Type && qFuzzyCompare(other->y(),y())
            && qAbs(other->x()-x())<30;
    //是否在同一行上并且间距足够判断相邻
}

int Plant::type() const
{
    return Type;
}

void Plant::setMovie(QString path)
{
    if(movie)
        delete movie;
    movie = new QMovie(path);//设定动画
    movie->start();
}
