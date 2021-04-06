#include "common.h"


namespace ui {
	const sf::Color defaultTextColor = sf::Color(0, 0, 0);
	const sf::Color primColor = sf::Color(25, 25, 255);
	const sf::Color secColor = sf::Color(25, 140, 255);
	const sf::Color outlineColor = sf::Color(255, 0, 0);
	const sf::Color hoverColor = sf::Color(180, 180, 180);


	constexpr auto FONT_LOC = "resources/ARIAL.TTF";
	sf::Font& getFont()
	{
		static std::unique_ptr<sf::Font> font;
		if (!font) {
			font = std::make_unique<sf::Font>();
			font->loadFromFile(FONT_LOC);
		}
		return *font;
	}
}