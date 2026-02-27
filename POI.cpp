#include "POI.h"
#include "cell.h"
#include "zero.h"
#include <cmath>


POI::POI(float x_, float y_, float r_, char t_){
    x = x_;
    y = y_;
    radius = r_;
    type = t_;
    amount = 100;
}

POI::~POI() {};

void POI::produceRequest(cell* producer, cell* zeroCell) {
    if (amount <= 0) return;  //ресурс кончился

    DATA d = producer->getData();

    float dx = d.x - x;
    float dy = d.y - y;
    float dist = std::sqrt(dx * dx + dy * dy);

    if (dist <= radius) {
        amount -= 1;  // ресурс уменьшается

        // отдаем ресурс zero
        zero* root = (zero*)zeroCell;
        if (type == 'L') {
            root->addResource('a', 1);
        }
        else {
            root->addResource('b', 1);
        }
    }
}

// создаем глобальные массивы??? хзхз тут я не уверена, дипсик помог
POI* g_lights[10] = { nullptr };
int g_light_count = 0;
POI* g_minerals[10] = { nullptr };
int g_mineral_count = 0;