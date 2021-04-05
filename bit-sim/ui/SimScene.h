#pragma once
#include <memory>
#include <vector>
#include <chrono>

#include "Scene.h"
#include "Button.h"
#include "../sim/PowerNode.h"
#include "../sim/Cable.h"

namespace ui {
	class SimScene
		: public Scene
	{
	public:
		using Scene::Scene;

		virtual void onFrameStart(const std::chrono::nanoseconds& lastFrametime) override {
			for (auto* cable : m_cables) {
				cable->update(lastFrametime);
			}
		}

		void addCable(sim::Cable* cable) {
			m_cables.push_back(cable);
		}
	private:
		std::vector<sim::Cable*> m_cables;
	};

	inline std::unique_ptr<Scene> loadSimScene(const sf::Vector2f& windowSize) {
		// sim-test setup
		auto node1 = std::make_unique<sim::PowerNode>(sf::Vector2f(400, 200), true);
		auto node2 = std::make_unique<sim::PowerNode>(sf::Vector2f(500, 250));
		auto node3 = std::make_unique<sim::PowerNode>(sf::Vector2f(450, 300));
		auto node4 = std::make_unique<sim::PowerNode>(sf::Vector2f(600, 300));
		auto cable1 = std::make_unique<sim::Cable>(*node1, *node2);
		auto cable2 = std::make_unique<sim::Cable>(*node1, *node3);
		auto cable3 = std::make_unique<sim::Cable>(*node3, *node4);

		auto scene = std::make_unique<SimScene>(windowSize);

		scene->addCable(cable1.get());
		scene->addCable(cable2.get());
		scene->addCable(cable3.get());

		scene->addChild(std::move(cable1));
		scene->addChild(std::move(cable2));
		scene->addChild(std::move(cable3));
		scene->addChild(std::move(node1));
		scene->addChild(std::move(node2));
		scene->addChild(std::move(node3));
		scene->addChild(std::move(node4));


		return std::move(scene);
	}
}