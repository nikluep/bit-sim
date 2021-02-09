#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Color.hpp>

constexpr auto FONT_LOC = "resources/ARIAL.TTF";

namespace ui {
	extern const sf::Font font;

	extern const sf::Color defaultTextColor;
	extern const sf::Color primColor;
	extern const sf::Color secColor;
	extern const sf::Color outlineColor;
	extern const sf::Color hoverColor;
}