#include "common.h"

namespace ui {
	const sf::Font font = []() {
		sf::Font f;
		f.loadFromFile(FONT_LOC);
		return f;
	}();

	const sf::Color defaultTextColor = sf::Color::Black;
	const sf::Color primColor = sf::Color(25, 25, 255);
	const sf::Color secColor = sf::Color(25, 140, 255);
	const sf::Color outlineColor = sf::Color::Black;
	const sf::Color hoverColor = sf::Color(180, 180, 180);
}