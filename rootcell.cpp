#include "rootcell.hpp"
#include "stem.hpp"
#include "cell.hpp"
#include <iostream>

rootcell::rootcell(Coords coords) : cell(coords, nullptr) {
    energy = 10;
    water = 10;
}

rootcell::~rootcell() { }

void rootcell::tick() {
    if ( this->alive ) {
        if ( Random() >= 0.8 )
            spread();
        // energy += 0.1;
        // water += 0.1;
        energy += children.size();
        water += children.size();
    }
    
    for (unsigned int i=0; i < this->children.size(); i++)
        children[i]->tick();
        
    // <- ��� �������� tick � ���� �����
}

void rootcell::spread() {
    if (children.size() >= 4)
        return;

    if ( !SpendRequest(5, 5) )
        return;

    cell* child;
    float dx = Random();
    float dy = Random();
    float len = std::sqrt(dx*dx + dy*dy);
    dx /= len;
    dy /= len;
    dx *= 2;
    dy *= 2;

    child = new stem({0 + dx, 0 + dy}, this);

    // if (!child) return false; //���� ������� ������ �� ����������. ���� �� ���� �����-�� ����������. � ��� � �� ��������� �������� �������

    children.push_back(child);
}

Coords rootcell::getEWquantity() {
    Coords EW = {this->energy, this->water};
    return EW;
}

bool rootcell::SpendRequest(float neededE, float neededW) {
    if (energy >= neededE && water >= neededW) {
        energy -= neededE;
        water -= neededW;
        return true; // true = �������, ���������
    }
    return false; // false = �� �������
}

void rootcell::getResource(char type, float amount) {
    if ( type=='e' )
        this->energy += amount;
    else if ( type=='w' )
        this->water += amount;
    else
        std::cout << "illegal char at getResource" << std::endl;
}