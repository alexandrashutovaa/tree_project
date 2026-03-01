#include "POI.hpp"
#include "cell.hpp"
#include "producer.hpp"
#include "rootcell.hpp"
#include <cmath>
#include <SFML/Graphics.hpp>

POI::POI(Coords coords_, float r_, char t_){
    radius = r_;
    type = t_;
    coords = coords_;

    if (this->type == 'e')
        this->color = sf::Color(
            200 + 30*Random(), 180 + 30*Random(), 30 + 5*Random(), 100 + 20*Random()
        );
    else if (this->type == 'w')
        this->color = sf::Color(
            30 + 5*Random(), 70 + 10*Random(), 160 + 20*Random()
        );
    else
        this->color = sf::Color::Magenta;
}

POI::~POI() { };

Coords POI::getCoords() {
    return this->coords;
};

char POI::getType() {
    return this->type;
};

void POI::produceRequest(producer* producer, rootcell* root) {

    Coords producerCoords = producer->getData().coords;

    float dx = producerCoords.x - this->coords.x;
    float dy = producerCoords.y - this->coords.y;

    float dist = std::sqrt(dx*dx + dy*dy);

    if (dist <= radius)
        root->getResource(this->type, 1);
}

void POI::display(sf::RenderWindow* window, float scale) {

    float RadiusInPixels = this->radius * scale;

    sf::CircleShape circle(RadiusInPixels);
    circle.setFillColor(this->color);
    
    circle.setOutlineColor(sf::Color::White);
    circle.setOutlineThickness(1.f);

    Coords dispCoords = DisplayCoordinates(this->getCoords(), window, scale);

    circle.setPosition(dispCoords.x - RadiusInPixels, dispCoords.y - RadiusInPixels);
    window->draw(circle);
}

// ������� ���������� �������??? ���� ��� � �� �������, ������ �����
// POI* g_lights[10] = { nullptr };
// int g_light_count = 0;
// POI* g_minerals[10] = { nullptr };
// int g_mineral_count = 0;