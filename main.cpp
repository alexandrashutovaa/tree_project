#include "all-cells.hpp"
#include "POI.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

void drawGrid(sf::RenderWindow* window, float scale) {

    sf::VertexArray grid(sf::Lines);
    sf::Color gridColor(100, 100, 100);
    sf::Color gridCenterColor(200, 200, 200);
    unsigned int sizeX = window->getSize().x;
    unsigned int sizeY = window->getSize().y;

    while ( window->getSize().x > 20*scale
        || window->getSize().y > 20*scale )
        scale *= 2;
     
    // grid

    for (int i = 1; i <= window->getSize().x / 2; i++) 
    {
        grid.append(sf::Vertex(sf::Vector2f(sizeX/2 + i*scale, 0.f), gridColor));
        grid.append(sf::Vertex(sf::Vector2f(sizeX/2 + i*scale, sizeY), gridColor));
        grid.append(sf::Vertex(sf::Vector2f(sizeX/2 + -i*scale, 0.f), gridColor));
        grid.append(sf::Vertex(sf::Vector2f(sizeX/2 + -i*scale, sizeY), gridColor));
    }
    for (int i = 1; i <= window->getSize().y / 2; i++)
    {
        grid.append(sf::Vertex(sf::Vector2f(0.f, sizeY/2 + i*scale), gridColor));
        grid.append(sf::Vertex(sf::Vector2f(sizeX, sizeY/2 + i*scale), gridColor));
        grid.append(sf::Vertex(sf::Vector2f(0.f, sizeY/2 - i*scale), gridColor));
        grid.append(sf::Vertex(sf::Vector2f(sizeX, sizeY/2 - i*scale), gridColor));
    }

    // white 0, 0 cross

    grid.append(sf::Vertex(sf::Vector2f(sizeX/2, 0.f), gridCenterColor));
    grid.append(sf::Vertex(sf::Vector2f(sizeX/2, sizeY), gridCenterColor));
    
    grid.append(sf::Vertex(sf::Vector2f(0.f, sizeY/2), gridCenterColor));
    grid.append(sf::Vertex(sf::Vector2f(sizeX, sizeY/2), gridCenterColor));

    window->draw(grid);
}

int main()
{
    std::cout << "Running main" << std::endl;

    // window setup

    sf::RenderWindow window(sf::VideoMode(1600, 900), "Cells & trees");
    window.setFramerateLimit(60);

    sf::Image icon;
    if ( ! icon.loadFromFile("icon.png") )
        return -1;
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    const sf::Time TimePerTick = sf::seconds(1.f / 10.f); // 1 second / X ticks

    sf::Font font;
    if (!font.loadFromFile("arialmt.ttf"))
        return -1;
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(40);
    text.setFillColor(sf::Color::White);
    text.setPosition(20.f, 20.f);

    float scale = 60; // pixels per length unit
    unsigned int TickNumber = 0;
    float maxX = 0;
    float maxY = 0;
    float ratio;

    std::vector<POI*> lakes;
    for ( unsigned int i=0; i<10; i++ ) {
        POI* tmp = new POI(
            {30*Random(), 30*Random()}, 3, 'w'
        );
        if ( ! (-5 < tmp->getCoords().x && tmp->getCoords().x < 5 && -5 < tmp->getCoords().y && tmp->getCoords().y < 5) )
            lakes.push_back(tmp);
    }

    std::vector<POI*> lights;
    for ( unsigned int i=0; i<10; i++ ) {
        POI* tmp = new POI(
            {30*Random(), 30*Random()}, 2, 'e'
        );
        if ( ! (-5 < tmp->getCoords().x && tmp->getCoords().x < 5 && -5 < tmp->getCoords().y && tmp->getCoords().y < 5) )
            lights.push_back(tmp);
    }

    rootcell* zero = new rootcell({0, 0});

    // game cycle
    
    while (window.isOpen())
    {
        sf::Time elapsed = clock.restart();
        timeSinceLastUpdate += elapsed;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::Resized)
            {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }
        }

        // tick actions

        while (timeSinceLastUpdate > TimePerTick) {
            timeSinceLastUpdate -= TimePerTick;

            TickNumber += 1;
            // std::cout << "tick " << TickNumber << std::endl;
            zero->tick();

            // find most distant cells, gradually change scale

            Coords maxCoords = zero->maxCoords();
            maxX = maxCoords.x;
            maxY = maxCoords.y;
            
            text.setString(
                std::to_string(1000/TimePerTick.asMilliseconds()) + " TPS\ttick: " + std::to_string(TickNumber) + "\n"
                + "E: " + std::to_string(zero->getEWquantity().x) + "\n"
                + "W: " + std::to_string(zero->getEWquantity().y) + "\n"
            );
        }
        
        ratio = 2*(maxX+2)*scale / window.getSize().x;
        // std::cout << ratio << std::endl;
        if ( 2*(maxY+2)*scale / window.getSize().y > ratio )
            ratio = 2*(maxY+2)*scale / window.getSize().y;
        // std::cout << ratio << std::endl;
        scale *= (51 - ratio) / 50 ;
        
        // display

        window.clear(sf::Color(3, 16, 25));
        drawGrid(&window, scale);
        
        for (unsigned int i=0; i<lakes.size(); i++) {
            lakes[i]->display(&window, scale);
        }

        zero->display_tree(&window, scale);

        for (unsigned int i=0; i<lights.size(); i++) {
            lights[i]->display(&window, scale);
        }

        window.draw(text);
        window.display();
    }
    
    std::cout << "Exit (success)" << std::endl;
    return 0;
}