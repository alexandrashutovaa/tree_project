#ifndef _ZERO_H_
#define _ZERO_H_
#include "cell.h"

class zero : public cell {
private:
    float total_energy;
    float total_water; 

public:
    zero(float x, float y);
    virtual ~zero();

    bool spend(float neededE, float neededW);
    void tick();
    void addResource(char type, float amount); //тк у нас значения энергии и воды приватные, чтобы продюсер мог добавлять нужен этот метод


protected:
    void grow();
    void produce();
};

#endif