#ifndef CONEZOMBIE_H
#define CONEZOMBIE_H
#include "zombie.h"
#include "plant.h"

class ConeZombie:public Zombie
{
public:
    ConeZombie();
    void advance(int phase);
};

#endif // CONEZOMBIE_H
