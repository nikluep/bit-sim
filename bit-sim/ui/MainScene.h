#pragma once
#include <memory>
#include <functional>

#include <SFML/System/Vector2.hpp>

#include "Scene.h"
#include "Button.h"
#include "SimScene.h"

namespace ui {
	const auto START_POS = sf::Vector2f{ 400.f, 400.f };
	constexpr auto SPACING = 25.f;
	const auto BUTTON_SIZE = sf::Vector2f{ 200.f, 50.f };

	inline std::unique_ptr<Scene> loadMainScene(const sf::Vector2f& windowSize, bool& exitCondition) {
		// setup basic blocks
		auto scene = std::make_unique<Scene>(windowSize);
		auto simstart = std::make_unique<Button>(START_POS, BUTTON_SIZE, "START SIM");
		auto exit = std::make_unique<Button>(
			START_POS + sf::Vector2f{0.f, BUTTON_SIZE.y + SPACING}, BUTTON_SIZE, "EXIT");

		// add button functionality
		auto scenePtr = scene.get();
		simstart->addCallback([scenePtr, windowSize]() { scenePtr->switchTo(std::move(loadSimScene(windowSize))); });
		exit->addCallback([&exitCondition]() { exitCondition = true; });

		// bring everything together and construct scene
		scene->addChild(std::move(simstart));
		scene->addChild(std::move(exit));

		return std::move(scene);
	}
}

