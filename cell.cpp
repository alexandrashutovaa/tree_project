#include "cell.h"
#include "zero.h"
#include "stem.h"
#include "producer.h"

cell::cell(float x_, float y_, cell* parent_){ //конструктор, тут все просто
    x = x_;
    y = y_;
    parent = parent_;
    alive = true;
    E = 0;
    W = 0;
    child_count = 0;
    curTask.whereTo = nullptr;
    curTask.howMuchE = 0;
    curTask.howMuchW = 0;
    children = new cell* [MAX_CHILDREN];
    for (int i = 0; i < MAX_CHILDREN; ++i) {
        children[i] = nullptr;
    }
}

cell::~cell() { //деструктор
    for (int i = 0; i < child_count; ++i) {
        if (children[i] != nullptr) {
            delete children[i];
        }
    }
    delete[] children;
}

bool cell::isAlive() {
    return alive;
}//проверка, живой нет


void cell::get(unsigned int e, unsigned int w) {
    if (isAlive()) {
        E += e;
        W += w;
    }
}

void cell::die() {
    alive = false;
}

DATA cell::getData() {
    DATA data;
    data.alive = alive;
    data.x = x;
    data.y = y;
    data.E = E;
    data.W = W;
    data.task = curTask;
    data.parent = parent;
    data.children = children;
    data.child_count = child_count;
    return data;
}

cell* cell::getRoot() {
    cell* root = this;
    while (root->getData().parent != nullptr) {
        root = root->getData().parent;
    }
    return root;
}

bool cell::createChild(float child_x, float child_y, CellType type) {
    if (child_count >= MAX_CHILDREN) return false;

    if (!isPositionValid(child_x, child_y)) return false;

    cell* child = nullptr;

    if (type == CELL_ZERO) {
        child = new zero(child_x, child_y);
    }
    else if (type == CELL_STEM) {
        child = new stem(child_x, child_y, this);
    }
    else if (type == CELL_PRODUCER) {
        child = new producer(child_x, child_y, this);
    }

    if (!child) return false; //если ребенка вооьще не существует. надо же фолс когда-то возвращать. а так я хз насколько полезная строчка

    children[child_count] = child;
    child_count++;
    return true;
}

bool cell::isPositionValid(float new_x, float new_y) { //проверим что родитель не занял место и что оно в принципе не занято
    if (new_x == x && new_y == y) { 
        return false; 
    }

    for (int i = 0; i < child_count; ++i) {
        if (children[i]) {
            if (new_x == children[i]->getData().x && new_y == children[i]->getData().y) {
                return false;
            }
        }
    }

    return true;  // место свободно!
}

void cell::tick() {
    if (!alive) return;
    for (int i = 0; i < child_count; ++i) {
        if (children[i]) {
            children[i]->tick();
        }
    }
    produce();
    grow();
}



//не понадобилось. но было в начальных версиях проекта. может понадобится потом, если развивать.
/*void cell::task(TASK sentTask) {
    curTask = sentTask;
}*/

/*void cell::send() {
    if (alive and (curTask.whereTo != nullptr)) {

        cell* to = curTask.whereTo;

        to->get(curTask.howMuchE, curTask.howMuchW);

        E -= curTask.howMuchE;
        W -= curTask.howMuchW;

        curTask.whereTo = nullptr;
        curTask.howMuchE = 0;
        curTask.howMuchW = 0;
    }
}*/

