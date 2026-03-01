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
    if ( this->alive )
        return;
    
    energy += 0.1;
    water += 0.1;

    if ( Random() >= 0.8 )
        spread();
    
    // <- ��� �������� tick � ���� �����
}

void rootcell::spread() {
    if (children.size() >= 4)
        return;

    if ( !SpendRequest(5, 5) )
        return;

    cell* child;
    float dx = 2*Random();
    float dy = 2*Random();
    float len = std::sqrt(dx*dx + dy*dy);
    dx /= len;
    dy /= len;

    child = new stem({0 + dx, 0 + dy}, this);

    // if (!child) return false; //���� ������� ������ �� ����������. ���� �� ���� �����-�� ����������. � ��� � �� ��������� �������� �������

    children.push_back(child);
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