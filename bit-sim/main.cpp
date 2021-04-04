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
#include "sim/Cable.h"



int main()
{
	// base setup
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "BitSim");


	// ui-test setup
	auto button = std::make_unique<ui::Button>(sf::Vector2f{400, 600}, sf::Vector2f{ 200, 50 }, "Move me");
	button->addCallback([]() { std::cout << "Button pressed!" << std::endl; });

	ui::BaseContainer windowContainer({ 0.f, 0.f }, { 1000.f, 1000.f });
	windowContainer.addChild(std::move(button));
	
	// sim-test setup
	auto node1 = std::make_unique<sim::PowerNode>(sf::Vector2f(400, 200), true);
	auto node2 = std::make_unique<sim::PowerNode>(sf::Vector2f(500, 250));
	auto node3 = std::make_unique<sim::PowerNode>(sf::Vector2f(450, 300));
	auto node4 = std::make_unique<sim::PowerNode>(sf::Vector2f(600, 300));
	auto cable1 = std::make_unique<sim::Cable>(*node1, *node2);
	auto cable2 = std::make_unique<sim::Cable>(*node1, *node3);
	auto cable3 = std::make_unique<sim::Cable>(*node3, *node4);
	std::vector<sim::Cable*> cables{ cable1.get(), cable2.get(), cable3.get() };

	windowContainer.addChild(std::move(cable1));
	windowContainer.addChild(std::move(cable2));
	windowContainer.addChild(std::move(cable3));
	windowContainer.addChild(std::move(node1));
	windowContainer.addChild(std::move(node2));
	windowContainer.addChild(std::move(node3));
	windowContainer.addChild(std::move(node4));

	ui::BaseElement* lastMouseConsumer = nullptr;
	while (window.isOpen())
	{

		using namespace std::chrono_literals;
		std::this_thread::sleep_for(12ms);
		for (auto* cable : cables) {
			cable->update();
		}

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
		window.draw(windowContainer);
		window.display();
	}

	return 0;
}