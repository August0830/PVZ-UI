#ifndef DOUBLESHOOTER_H
#define DOUBLESHOOTER_H
#include "plant.h"
#include "bullet.h"
#include "zombie.h"

class DoubleShooter:public Plant
{
public:
    DoubleShooter();
    void advance(int phase) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
};

#endif // DOUBLESHOOTER_H
