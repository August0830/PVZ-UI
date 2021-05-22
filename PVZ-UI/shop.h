#ifndef SHOP_H
#define SHOP_H

#include <QRectF>
#include "other.h"
#include "card.h"
//include from plant.h
class Shop:public Other
{
public:
    int sun_deposit;
    Shop();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void advance(int phase) override;
    void addPlant(QString s,QPointF pos);
private:
    int counter;
    int time;
};

#endif // SHOP_H
