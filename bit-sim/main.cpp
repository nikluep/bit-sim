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

#include "ui/Scene.h"
#include "ui/MainScene.h"
#include "ui/BaseElement.h"

#include "sim/PowerNode.h"
#include "sim/Cable.h"




int main()
{
	// base setup
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "BitSim");

	ui::BaseElement* lastMouseConsumer = nullptr;
	bool exitTriggered = false;
	auto scene = std::move(ui::loadMainScene(
		static_cast<sf::Vector2f>(window.getSize()), exitTriggered));
	auto clock = std::chrono::steady_clock();
	auto framestart = clock.now();
	auto frametime = clock.now() - framestart;


	while (window.isOpen() && !exitTriggered)
	{
		framestart = clock.now();
		if (scene->isSwitchTriggered()) {
			scene = std::move(scene->getNextScene());
			lastMouseConsumer = nullptr;
		}

		scene->onFrameStart(frametime);
		

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
					auto* consumer = scene->findMouseConsumer(pos);
					if (consumer) {
						consumer->onMouseDown();
					}
				}
				break;
			case sf::Event::MouseButtonReleased:
				if (evnt.mouseButton.button == sf::Mouse::Left) {
					const sf::Vector2f pos = { static_cast<float>(evnt.mouseButton.x), static_cast<float>(evnt.mouseButton.y) };
					auto* consumer = scene->findMouseConsumer(pos);
					if (consumer) {
						consumer->onMouseUp();
					}
				}
				break;			
			case sf::Event::MouseMoved:
				const sf::Vector2f pos = { static_cast<float>(evnt.mouseMove.x), static_cast<float>(evnt.mouseMove.y) };
				auto* consumer = scene->findMouseConsumer(pos);
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

		scene->onFrameEnd(frametime);


		// render 
		window.clear();
		window.draw(*scene);
		window.display();


		frametime = clock.now() - framestart;
	}
	if (window.isOpen()) {
		window.close();
	}

	return 0;
}