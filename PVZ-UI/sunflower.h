#ifndef SUNFLOWER_H
#define SUNFLOWER_H
#include "plant.h"
#include "sun.h"

class Sunflower:public Plant
{
public:
    Sunflower();
    void advance(int phase) override;
};

#endif // SUNFLOWER_H
