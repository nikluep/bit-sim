#pragma once
#include <memory>
#include <vector>
#include <chrono>

#include "Scene.h"
#include "Button.h"
#include "../sim/BaseComponent.h"
#include "../sim/PowerNode.h"
#include "../sim/Cable.h"
#include "../sim/BinaryGate.h"

namespace ui {
	class SimScene
		: public Scene
	{
	public:
		using Scene::Scene;
		virtual ~SimScene() = default;

		virtual void onFrameStart(const std::chrono::nanoseconds& lastFrametime) override {
			for (auto* component : m_components) {
				component->update(lastFrametime);
			}
		}

		void addComponent(sim::BaseComponent* component) {
			m_components.push_back(component);
		}
	private:
		std::vector<sim::BaseComponent*> m_components;
	};

	inline std::unique_ptr<Scene> loadSimScene(const sf::Vector2f& windowSize) {

		// sim-test setup
		auto nodeMeshStart = std::make_unique<sim::PowerNode>(sf::Vector2f(400, 200), true);
		auto nodeMesh1 = std::make_unique<sim::PowerNode>(sf::Vector2f(500, 250));
		auto nodeMesh2 = std::make_unique<sim::PowerNode>(sf::Vector2f(450, 300));
		auto nodeMeshEnd = std::make_unique<sim::PowerNode>(sf::Vector2f(600, 300));
		auto nodeInput2 = std::make_unique<sim::PowerNode>(sf::Vector2f(600, 400), true);
		auto nodeOutput = std::make_unique<sim::PowerNode>(sf::Vector2f(900, 350));

		auto gate = std::make_unique<sim::ANDGate>(sf::Vector2f(700, 300));

		auto cableMesh1 = std::make_unique<sim::Cable>(*nodeMeshStart, *nodeMesh1);
		auto cableMesh2 = std::make_unique<sim::Cable>(*nodeMeshStart, *nodeMesh2);
		auto cableMesh3 = std::make_unique<sim::Cable>(*nodeMesh2, *nodeMeshEnd);
		auto cableGate1 = std::make_unique<sim::Cable>(*nodeMeshEnd, gate->getInput1());
		auto cableGate2 = std::make_unique<sim::Cable>(*nodeInput2, gate->getInput2());
		auto cableGateOut = std::make_unique<sim::Cable>(gate->getOutput(), *nodeOutput);

		auto scene = std::make_unique<SimScene>(windowSize, PositioningStrategy{});

		scene->addComponent(cableMesh1.get());
		scene->addComponent(cableMesh2.get());
		scene->addComponent(cableMesh3.get());
		scene->addComponent(cableGate1.get());
		scene->addComponent(cableGate2.get());
		scene->addComponent(cableGateOut.get());
		scene->addComponent(gate.get());

		scene->addChild(std::move(cableMesh1));
		scene->addChild(std::move(cableMesh2));
		scene->addChild(std::move(cableMesh3));
		scene->addChild(std::move(cableGate1));
		scene->addChild(std::move(cableGate2));
		scene->addChild(std::move(cableGateOut));
		scene->addChild(std::move(nodeMeshStart));
		scene->addChild(std::move(nodeMesh1));
		scene->addChild(std::move(nodeMesh2));
		scene->addChild(std::move(nodeMeshEnd));
		scene->addChild(std::move(nodeInput2));
		scene->addChild(std::move(nodeOutput));
		scene->addChild(std::move(gate));


		return std::move(scene);
	}
}