#ifndef _STEM_H_
#define _STEM_H_
#include "cell.h"

class stem : public cell {
public:
    stem(float x, float y, cell* parent);
    ~stem();

    void tick();

protected:
    void grow();
    void produce();
};

#endif