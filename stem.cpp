#include "stem.hpp"
#include "cell.hpp"
#include "rootcell.hpp"

#include <iostream>

stem::stem(Coords coords, cell* parent) : cell(coords, parent) { }

stem::~stem() { }

void stem::tick() {
    if ( this->alive )
        if ( Random() >= 0.2 )
            spread();
    
    for (unsigned int i=0; i < this->children.size(); i++)
        children[i]->tick();
}

void stem::spread() {

    if (children.size() >= 3)
        return;

    if ( Random() > 0.8 )
        return;

    rootcell* rootptr = (rootcell*)(this->getData().root);
    if ( ! rootptr->SpendRequest(
        this->getData().coords.x * (2*this->getData().coords.x-1), this->getData().coords.y * (2*this->getData().coords.y-1)
    ) )
        return;

    cell* child;
    float dx, dy;
    dx = Random();
    dy = Random();
    float len = std::sqrt(dx*dx + dy*dy);
    dx /= len; dx += 0.5*Random();
    dy /= len; dy += 0.5*Random();
    
    len = std::sqrt(this->getData().coords.x * this->getData().coords.x + this->getData().coords.y * this->getData().coords.y);
    dx += 2*this->getData().coords.x / len;
    dy += 2*this->getData().coords.y / len;

    child = new stem({this->getData().coords.x + dx, this->getData().coords.y + dy}, this);

    // if (!child) return false; //���� ������� ������ �� ����������. ���� �� ���� �����-�� ����������. � ��� � �� ��������� �������� �������

    children.push_back(child);
}