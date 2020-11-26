#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
	sf::RectangleShape player(sf::Vector2f(100.0f,100.0f));
	player.setOrigin(50.0f, 50.0f);
	sf::Sprite sprite;
	sf::Texture playerTexture;
	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile("background.png");
	playerTexture.loadFromFile("test.png");
	player.setTexture(&playerTexture);
	sprite.setTexture(backgroundTexture);

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

		window.clear();
		window.draw(sprite);
		window.draw(player);
		window.display();
	}

	return 0;
}