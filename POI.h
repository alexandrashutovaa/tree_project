#ifndef _POI_H_
#define _POI_H_
#include "cell.h"

class POI {
public:
    float x, y;      
    float radius;      
    char type; // L- свет M - минералы
    float amount; // сколько осталось

    POI(float x_, float y_, float r_, char t_);
    virtual ~POI();
    void produceRequest(cell* producer, cell* zeroCell);
};

// глобальные массивы (доступны везде)
extern POI* g_lights[10]; //массив источников света
extern int g_light_count; //сколько источников света
extern POI* g_minerals[10]; // аналогично
extern int g_mineral_count;

#endif