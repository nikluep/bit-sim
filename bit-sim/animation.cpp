#include "animation.h"



/*
* Use initialization list like this:
* Animation::Animation(...)
*	: imageCount(imageCount), switchTime(switchTime), totalTime(0.0f), currentImage(0, 3), uvRect(0, 0, 150, 150)
* {}
*/
animation::animation(sf::Texture* texture /*unused*/, sf::Vector2u imageCount, float switchTime) 
{
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0.0f;
	currentImage.x = 3;

	// good practice: declare constants seperatly
	uvRect.width = 150;
	uvRect.height = 150;
}


animation:: ~animation() 
{
	
}

void animation::Update(int row, float deltaTime)
{
	currentImage.y = row;
	totalTime += deltaTime;

	if (totalTime >= switchTime) {
		totalTime -= switchTime;
		currentImage.x++;

		if(currentImage.x >= imageCount.x) {
			currentImage.x = 0;
		}

	}
	uvRect.left = currentImage.x * uvRect.width;
	uvRect.top = 0;
}

