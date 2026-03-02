#include "cell.hpp"
#include "producer.hpp"

#include <chrono>
#include <random>
#include <vector>
#include <SFML/Graphics.hpp>

float Random() {
	std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(0, 2000);
    return 0.001*(distrib(gen)-1000);
};

Coords DisplayCoordinates(Coords coords, sf::RenderWindow* window, float scale) {
	Coords disp;
    disp.x = window->getSize().x / 2;
    disp.y = window->getSize().y / 2;
    disp.x += scale * coords.x;
    disp.y += scale * coords.y;
	return disp;
};

cell::cell(Coords coords_, cell* parent_) { //�����������, ��� ��� ������
    alive = true;
    coords = coords_;
    parent = parent_;
    
    if ( parent )
        root = parent->getData().root;
    else
        root = this;
    }

cell::~cell() { } //����������

void cell::die() {
    alive = false;
}

DATA cell::getData() {
    DATA data;
    data.alive = this->alive;
	data.coords = this->coords;
	data.parent = this->parent;
    data.root = this->root;
    data.children = this->children;
    return data;
}

void cell::display_tree(sf::RenderWindow* window, float scale) {

    sf::CircleShape circle(6.f);
    circle.setFillColor(sf::Color::Red);
    circle.setOutlineColor(sf::Color::Black);
    circle.setOutlineThickness(1.f);

    Coords dispCoords = DisplayCoordinates(this->getData().coords, window, scale);

    circle.setPosition(dispCoords.x - 6, dispCoords.y - 6);
    window->draw(circle);

    for (unsigned int i=0; i < this->children.size(); i++) {

        Coords dispCoords2 = DisplayCoordinates(children[i]->getData().coords, window, scale);

        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(dispCoords.x, dispCoords.y)), // Start point (x1, y1)
            sf::Vertex(sf::Vector2f(dispCoords2.x, dispCoords2.y))  // End point (x2, y2)
        };

        line[0].color = sf::Color::Red;
        line[1].color = sf::Color::Red;

        window->draw(line, 2, sf::Lines);
    }

    for (unsigned int i=0; i < this->children.size(); i++) {
        children[i]->display_tree(window, scale);
    }
}

Coords cell::maxCoords() {
    Coords maxcoords = {
        this->getData().coords.x * ( 2*(this->getData().coords.x > 0)-1 ),
        this->getData().coords.y * ( 2*(this->getData().coords.y > 0)-1 )
    };

    for ( unsigned int i=0; i<children.size(); i++ ) {
        Coords maxChildCoords = children[i]->maxCoords();
        if ( maxChildCoords.x > maxcoords.x )
            maxcoords.x = maxChildCoords.x;
        if ( maxChildCoords.y > maxcoords.y )
            maxcoords.y = maxChildCoords.y;
    }
    return maxcoords;
}

/*
bool cell::createChild(float child_x, float child_y, CellType type) {
    if (child_count >= MAX_CHILDREN) return false;

    if (!isPositionValid(child_x, child_y)) return false;

    cell* child = nullptr;

    if (type == CELL_ZERO) {
        child = new root(child_x, child_y);
    }
    else if (type == CELL_STEM) {
        child = new stem(child_x, child_y, this);
    }
    else if (type == CELL_PRODUCER) {
        child = new producer(child_x, child_y, this);
    }

    if (!child) return false; //���� ������� ������ �� ����������. ���� �� ���� �����-�� ����������. � ��� � �� ��������� �������� �������

    children[child_count] = child;
    child_count++;
    return true;
}
*/

/*
bool cell::isPositionValid(float new_x, float new_y) { //�������� ��� �������� �� ����� ����� � ��� ��� � �������� �� ������
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

    return true;  // ����� ��������!
}
*/