#include "producer.hpp"
#include "cell.hpp"
#include "POI.hpp"

producer::producer(Coords coords, cell* parent) : cell(coords, parent) {
    this->color = sf::Color(50, 50, 200);
}

producer::~producer() { }

/*
void producer::produce() {
    zero* root = (zero*)getRoot(); //��� ������ ����������� ������: �� ���� ����� getRoot ������ ���������� cell*, �� ��� ������ �
     //��������� �����, ������� ��������� ������ � zero. ���� ��������� �����, ������ �� �������, ���� ���

    //��������� ��� ��������� �����
    for (int i = 0; i < g_light_count; i++) {
        if (g_lights[i] != nullptr) {
            g_lights[i]->produceRequest(this, root);
        }
    }

    //��������� ��� ��������
    for (int i = 0; i < g_mineral_count; i++) {
        if (g_minerals[i] != nullptr) {
            g_minerals[i]->produceRequest(this, root);
        }
    }
}
*/

void producer::tick() {
    if ( this->alive )
        produce();

    for (unsigned int i=0; i < this->children.size(); i++)
        children[i]->tick();
}

void producer::produce() {
    
}