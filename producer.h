#ifndef _PRODUCER_H_
#define _PRODUCER_H_
#include "cell.h"

class producer : public cell {
public:
    producer(float x, float y, cell* parent);
    virtual ~producer();

    void tick();

protected:
    void produce();
    void grow();
};

#endif