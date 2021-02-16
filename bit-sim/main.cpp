#include <iostream>

#include <vector>
#include <memory>
#include <cstdlib>

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

#include "animation.h"
#include "ui/common.h"
#include "ui/Button.h"
#include "ui/BaseContainer.h"



int main()
{
	std::srand(1337);

	// gimme some space m8
	// make objects
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
	sf::RectangleShape player(sf::Vector2f(150.0f,150.0f));
	sf::Sprite sprite;
	sf::Texture playerTexture;
	sf::Texture backgroundTexture;
	sf::Clock clock;
	sf::Text text("Test", ui::font);
	text.setFillColor(ui::defaultTextColor);
	animation animation(&playerTexture, sf::Vector2u(3, 3), 0.2f);
	
	// ui test
	sf::RectangleShape s(sf::Vector2f(200.f, 50.f));
	s.setPosition(400.f, 400.f);
	auto button = std::make_unique<ui::Button>(s, "Move me");
	button->addCallback([]() { std::cout << "Button pressed!" << std::endl; });
	button->addCallback([&player]() {
			const auto x = static_cast<float>(std::rand() % 1000);
			const auto y = static_cast<float>(std::rand() % 1000);
			player.setPosition(x, y);
		});

	ui::BaseContainer windowContainer(sf::FloatRect(0.f, 0.f, 1000.f, 1000.f));
	windowContainer.addChild(std::move(button));

	std::vector<const sf::Drawable*> drawables;
	drawables.reserve(windowContainer.countDrawables());
	windowContainer.gatherDrawables(drawables);
	



	// set spawn and spwn on click pos
	player.setOrigin(75.0f, 75.0f);
	player.setPosition(500.0f, 500.0f);
	// load texture files
	backgroundTexture.loadFromFile("background.png");
	playerTexture.loadFromFile("aniMatiOn.png");
	

	// set textures in objct
	player.setTexture(&playerTexture);
	sprite.setTexture(backgroundTexture);

	// float to save time
	float deltaTime = 0.0f;
	

	ui::BaseElement* lastMouseConsumer = nullptr;
	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
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
				break;
			case sf::Event::MouseButtonPressed:
				if (evnt.mouseButton.button == sf::Mouse::Left) {
					const sf::Vector2f pos = { static_cast<float>(evnt.mouseButton.x), static_cast<float>(evnt.mouseButton.y) };
					auto* consumer = windowContainer.findMouseConsumer(pos);
					if (consumer) {
						consumer->onMouseDown();
					}
				}
				break;
			case sf::Event::MouseButtonReleased:
				if (evnt.mouseButton.button == sf::Mouse::Left) {
					const sf::Vector2f pos = { static_cast<float>(evnt.mouseButton.x), static_cast<float>(evnt.mouseButton.y) };
					auto* consumer = windowContainer.findMouseConsumer(pos);
					if (consumer) {
						consumer->onMouseUp();
					}
				}
				break;			
			case sf::Event::MouseMoved:
				const sf::Vector2f pos = { static_cast<float>(evnt.mouseMove.x), static_cast<float>(evnt.mouseMove.y) };
				auto* consumer = windowContainer.findMouseConsumer(pos);
				if (lastMouseConsumer && lastMouseConsumer != consumer) {
					lastMouseConsumer->onMouseExit();
				}
				if (consumer) {
					consumer->onMouseEnter();
				}
				lastMouseConsumer = consumer;
				break;
			}
		}


		animation.Update(0, deltaTime);
		player.setTextureRect(animation.uvRect);

		window.clear();
		window.draw(sprite);
		window.draw(player);
		window.draw(text);

		for (const auto* drawable : drawables) {
			window.draw(*drawable);
		}

		window.display();
	}

	return 0;
}