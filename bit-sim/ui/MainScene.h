#pragma once
#include <memory>
#include <functional>

#include <SFML/System/Vector2.hpp>

#include "Scene.h"
#include "Button.h"
#include "SimScene.h"
#include "ListContainer.h"

namespace ui {
	const auto START_POS = sf::Vector2f{ 400.f, 400.f };
	constexpr auto SPACING = 25.f;
	const auto BUTTON_SIZE = sf::Vector2f{ 200.f, 50.f };

	inline std::unique_ptr<Scene> loadMainScene(const sf::Vector2f& windowSize, bool& exitCondition) {
		// setup basic blocks
		PositioningStrategy posStratH{ false, true, {1.f, 1.f} };
		PositioningStrategy posStratV{ false, true, {1.f, 1.f, 1.f} };
		auto scene = std::make_unique<Scene>(windowSize);
		auto sceneHContainer = std::make_unique<HListContainer>(sf::Vector2f{ 0.f, 0.f }, windowSize, posStratH);
		auto sceneVContainer = std::make_unique<VListContainer>(sf::Vector2f{ 0.f, 0.f }, windowSize, posStratV);
		auto simstart = std::make_unique<Button>(sf::Vector2f{}, BUTTON_SIZE, "START SIM");
		auto exit = std::make_unique<Button>(sf::Vector2f{}, BUTTON_SIZE, "EXIT");

		// add button functionality
		auto scenePtr = scene.get();
		simstart->addCallback([scenePtr, windowSize]() { scenePtr->switchTo(std::move(loadSimScene(windowSize))); });
		exit->addCallback([&exitCondition]() { exitCondition = true; });

		// bring everything together and construct scene
		sceneVContainer->addChild(std::move(simstart));
		sceneVContainer->addChild(std::move(exit));
		sceneHContainer->addChild(std::move(sceneVContainer));
		scene->addChild(std::move(sceneHContainer));
		scene->updatePositioning();

		return std::move(scene);
	}
}

