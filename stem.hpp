#ifndef _STEM_H_
#define _STEM_H_

#include "cell.hpp"

class stem : public cell {
public:
    stem(Coords coords, cell* parent);
    ~stem();
    void tick();
    void spread();
};

#endif