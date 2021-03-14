#include <iostream>

#include <vector>
#include <memory>
#include <thread>
#include <chrono>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

#include "ui/common.h"
#include "ui/Button.h"
#include "ui/BaseContainer.h"
#include "sim/PowerNode.h"



int main()
{
	// base setup
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "BitSim");

	
	// ui-test setup
	sf::RectangleShape s(sf::Vector2f(200.f, 50.f));
	s.setPosition(400.f, 400.f);
	auto button = std::make_unique<ui::Button>(s, "Move me");
	button->addCallback([]() { std::cout << "Button pressed!" << std::endl; });

	ui::BaseContainer windowContainer(sf::FloatRect(0.f, 0.f, 1000.f, 1000.f));
	windowContainer.addChild(std::move(button));
	
	// sim-test setup
	auto node = std::make_unique<sim::PowerNode>(sf::Vector2f(400, 200 ));
	windowContainer.addChild(std::move(node));
	
	std::vector<const sf::Drawable*> drawables;
	drawables.reserve(windowContainer.countDrawables());
	windowContainer.gatherDrawables(drawables);

	ui::BaseElement* lastMouseConsumer = nullptr;
	while (window.isOpen())
	{

		using namespace std::chrono_literals;
		std::this_thread::sleep_for(10ms);

		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			switch (evnt.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
				if (evnt.mouseButton.button == sf::Mouse::Left) {
					const sf::Vector2f pos = { static_cast<float>(evnt.mouseButton.x), static_cast<float>(evnt.mouseButton.y) };
					//std::cout << pos.x << ' ' << pos.y << std::endl;
					auto* consumer = windowContainer.findMouseConsumer(pos);
					if (consumer) {
						consumer->onMouseDown();
					}
				}
				break;
			case sf::Event::MouseButtonReleased:
				if (evnt.mouseButton.button == sf::Mouse::Left) {
					const sf::Vector2f pos = { static_cast<float>(evnt.mouseButton.x), static_cast<float>(evnt.mouseButton.y) };
					//std::cout << pos.x << ' ' << pos.y << std::endl;
					auto* consumer = windowContainer.findMouseConsumer(pos);
					std::cout << consumer << std::endl;
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


		// render 
		window.clear();
		for (const auto* drawable : drawables) {
			window.draw(*drawable);
		}

		window.display();
	}

	return 0;
}