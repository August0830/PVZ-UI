#ifndef FROZENSHOOTER_H
#define FROZENSHOOTER_H
#include "plant.h"
#include "zombie.h"
#include "bullet.h"

class FrozenShooter:public Plant
{
public:
    FrozenShooter();
    void advance(int phase) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
};

#endif // FROZENSHOOTER_H
