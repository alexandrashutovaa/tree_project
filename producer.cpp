#include "producer.h"
#include "zero.h"
#include "cell.h"
#include "POI.h"
#include <iostream>

producer::producer(float x, float y, cell* parent) : cell(x, y, parent) {}

producer::~producer() {}

void producer::produce() {
    zero* root = (zero*)getRoot(); //это короче посоветовал дипсик: по сути метод getRoot должен возвращать cell*, но там короче в
     //возникает метод, который сработает только с zero. если останется время, сделаю по красоте, пока так

    //проверяем все источники света
    for (int i = 0; i < g_light_count; i++) {
        if (g_lights[i] != nullptr) {
            g_lights[i]->produceRequest(this, root);
        }
    }

    //проверяем все минералы
    for (int i = 0; i < g_mineral_count; i++) {
        if (g_minerals[i] != nullptr) {
            g_minerals[i]->produceRequest(this, root);
        }
    }
}

void producer::tick() {
    if (!isAlive()) return;
    produce();    // добываем ресурсы
    cell::tick(); // дети (если есть)
}
void producer::grow() {}