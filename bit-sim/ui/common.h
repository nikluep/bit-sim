#pragma once
#include <chrono>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Color.hpp>


namespace ui {
	extern const sf::Color defaultTextColor;
	extern const sf::Color primColor;
	extern const sf::Color secColor;
	extern const sf::Color outlineColor;
	extern const sf::Color hoverColor;

	extern sf::Font& getFont();
}