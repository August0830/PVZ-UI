#ifndef SHOP_H
#define SHOP_H


#include "other.h"
#include "plant.h"
#include "card.h"
#include "sun.h"
#include "sunflower.h"
#include "peashooter.h"
#include "doubleshooter.h"
#include "frozenshooter.h"
#include "nut.h"
#include "potatomine.h"
#include "cherrybomb.h"
#include "basiczombie.h"


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
