#include <SFML/Graphics.hpp>
#include <iostream>

#include "animation.h"

int main()
{
	//make objkts
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
	sf::RectangleShape player(sf::Vector2f(150.0f,150.0f));
	sf::Sprite sprite;
	sf::Texture playerTexture;
	sf::Texture backgroundTexture;
	sf::Clock clock;
	animation animation(&playerTexture, sf::Vector2u(3, 3), 0.2f);
	

	//set spawn and spwn on click pos
	player.setOrigin(75.0f, 75.0f);
	player.setPosition(500.0f, 500.0f);
	//load texture files
	backgroundTexture.loadFromFile("background.png");
	playerTexture.loadFromFile("aniMatiOn.png");
	

	//set textures in objct
	player.setTexture(&playerTexture);
	sprite.setTexture(backgroundTexture);

	//float to save time
	float deltaTime = 0.0f;
	


	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
			player.move(-0.1f, 0.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
			player.move(0.1f, 0.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
			player.move(0.0f, -0.1f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
			player.move(0.0f, 0.1f);
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			player.setPosition((float)mousePos.x, ((float)mousePos.y));
		}
		animation.Update(0, deltaTime);
		player.setTextureRect(animation.uvRect);

		window.clear();
		window.draw(sprite);
		window.draw(player);
		window.display();
	}

	return 0;
}