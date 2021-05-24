#ifndef NUT_H
#define NUT_H
#include "plant.h"

class Nut:public Plant
{
public:
    Nut();
    void advance(int phase) override;
};

#endif // NUT_H
