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
    if ( icon.loadFromFile("icon.png") )
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    const sf::Time TimePerTick = sf::seconds(1.f / 10.f); // 1 second / X ticks

    // sf::Font font;
    // if (!font.loadFromFile("arialmt.ttf"))
    //     return EXIT_FAILURE;
    // sf::Text text;
    // text.setFont(font);
    // text.setCharacterSize(50);
    // text.setFillColor(sf::Color::White);
    // text.setPosition(100.f, 100.f);

    float scale = 60; // pixels per length unit
    unsigned int TickNumber = 0;

    std::vector<POI*> lights;
    for ( unsigned int i=0; i<10; i++ ) {
        POI* tmp = new POI(
            {10*Random(), 10*Random()}, 2, 'e'
        );
        lights.push_back(tmp);
    }
    std::vector<POI*> lakes;
    for ( unsigned int i=0; i<10; i++ ) {
        POI* tmp = new POI(
            {10*Random(), 10*Random()}, 3, 'w'
        );
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
            //process_tree(zero);
            
            TickNumber += 1;
            std::cout << "tick " << TickNumber << std::endl;
        }

        // display

        window.clear(sf::Color(3, 16, 25));
        drawGrid(&window, scale);
        
        for (unsigned int i=0; i<lakes.size(); i++) {
            lakes[i]->display(&window, scale);
        }

        // display_tree(&window, zero, scale);

        for (unsigned int i=0; i<lights.size(); i++) {
            lights[i]->display(&window, scale);
        }

        window.display();
    }
    
    std::cout << "Exit (success)" << std::endl;
    return 0;
}