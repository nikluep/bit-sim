#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>


class animation // convention: class names start with an uppercase letter
{
public:
	// refernces are cant be null -> safer than pointer
	animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
	~animation();

	// convention: method names start with a lower case letter
	// good practive: declare paramaters const
	void Update(int row, float deltaTime); 



public: // unnessecary
	sf::IntRect uvRect;
private:
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;
	
	float totalTime;
	float switchTime;

};

