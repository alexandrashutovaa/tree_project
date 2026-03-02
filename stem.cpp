#include "cell.hpp"
#include "stem.hpp"
#include "producer.hpp"
#include "rootcell.hpp"

#include <iostream>

stem::stem(Coords coords, cell* parent) : cell(coords, parent) {
    this->color = sf::Color(200, 50, 50);
}

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

    if ( Random() > 0.7 )
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
    dx /= len; dx *= 2; dx += Random();
    dy /= len; dy *= 2; dy += Random();
    
    len = std::sqrt(this->getData().coords.x * this->getData().coords.x + this->getData().coords.y * this->getData().coords.y);
    dx += 4*this->getData().coords.x / len;
    dy += 4*this->getData().coords.y / len;

    if ( Random() > -0.5 )
        child = new stem({this->getData().coords.x + dx, this->getData().coords.y + dy}, this);
    else
        child = new producer({this->getData().coords.x + dx, this->getData().coords.y + dy}, this);

    // if (!child) return false; //���� ������� ������ �� ����������. ���� �� ���� �����-�� ����������. � ��� � �� ��������� �������� �������

    children.push_back(child);
}