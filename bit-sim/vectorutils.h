#pragma once
#include <cmath>

#include <SFML/System/Vector2.hpp>



template <class T>
T length_squared(const sf::Vector2<T> vec) {
	return vec.x * vec.x + vec.y * vec.y;
}

template <class T>
T length(const sf::Vector2<T> vec) {
	return std::sqrt(length_squared(vec));
}
