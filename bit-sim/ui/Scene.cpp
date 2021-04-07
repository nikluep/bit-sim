#include "Scene.h"




namespace ui {
	Scene::Scene(const sf::Vector2f& windowSize, const PositioningStrategy& posStrat)
		: BaseContainer({}, windowSize, posStrat)
	{
	}
}