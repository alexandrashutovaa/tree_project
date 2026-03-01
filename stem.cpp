#include "stem.hpp"
#include "cell.hpp"

stem::stem(Coords coords, cell* parent) : cell(coords, parent) { }

stem::~stem() { }

void stem::tick() {
    for (unsigned int i=0; i < this->children.size(); i++)
        children[i]->tick();
    
    if ( this->alive )
        spread();
}

void stem::spread() {
    /*if (children.size() >= 4)
        return;

    if ( !SpendRequest(5, 5) )
        return;

    cell* child;
    float dx = 2 - 4*Random01();
    float dy = 2 - 4*Random01();
    float len = std::sqrt(dx*dx + dy*dy);
    dx /= len;
    dy /= len;

    child = new stem({0 + dx, 0 + dy}, this);

    // if (!child) return false; //���� ������� ������ �� ����������. ���� �� ���� �����-�� ����������. � ��� � �� ��������� �������� �������

    children.push_back(child);*/
}