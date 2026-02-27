#include "zero.h"
#include "stem.h"
#include "cell.h"
#include <iostream>

zero::zero(float x, float y) : cell(x, y, nullptr) {
    total_energy = 100.0f;
    total_water = 100.0f;
    get(10, 10);
}

zero::~zero() {
}

bool zero::spend(float neededE, float neededW) {
    if (total_energy >= neededE && total_water >= neededW) {
        total_energy -= neededE;
        total_water -= neededW;
        return true;  // true = хватило, потратили
    }
    return false;     // false = не хватило
}

void zero::produce() {
    total_energy += 1.0f;
    total_water += 0.5f;
}

void zero::grow() {
    if (spend(5.0f, 3.0f)) {
        createChild(getData().x, getData().y + 1.0, CELL_STEM);
    }
}

void zero::addResource(char type, float amount) {
    if (type == 'a') total_energy += amount;
    else total_water += amount;
}

void zero::tick() {
    if (!isAlive()) return;

    produce();
    grow();
    cell::tick();  // <- это запустит tick у всех детей

    if (total_energy <= 0.0 or total_water <= 0.0f) {
        die();
    }
}

