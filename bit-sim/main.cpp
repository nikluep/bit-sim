#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event evnt;
        
        while (window.pollEvent(evnt))
        {
            switch (evnt.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                std::cout << "The WINDOW is " << evnt.size.width << " Pixels wide aNd " << evnt.size.height << " pxls high!" << std::endl;
                break;
            case sf::Event::TextEntered:
                if (evnt.text.unicode < 128) {
                    std::cout << (char)evnt.text.unicode;
                }
            }
            
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}