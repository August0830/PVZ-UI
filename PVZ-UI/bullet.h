#ifndef BULLET_H
#define BULLET_H
#include "other.h"

class Bullet:public Other
{
public:
    Bullet(int attack=0,bool flag=false);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
    void advance(int phase) override;
private:
    bool snow;
    int attack;
    qreal speed;
};

#endif // BULLET_H
