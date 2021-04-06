#pragma once
#include <SFML/System/Vector2.hpp>

#include "../vectorutils.h"

inline bool containedByRect(const sf::Vector2f& pos, const sf::Vector2f& size, const sf::Vector2f& point) {
	return
		(point.x >= pos.x && point.x <= pos.x + size.x) &&
		(point.y >= pos.y && point.y <= pos.y + size.y);
}

inline bool containedByCircle(const sf::Vector2f& pos, const float radius, const sf::Vector2f& point) {
	return length_squared(point - (pos + sf::Vector2f{radius, radius})) <= radius * radius;
}

//TODO: triangles