#ifndef _PRODUCER_H_
#define _PRODUCER_H_

#include "cell.hpp"

class producer : public cell {
public:
    producer(Coords coords, cell* parent);
    ~producer();
    void tick();
    void produce();
};

#endif