#include "animation.h"


	animation::animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime) {
		this->imageCount = imageCount;
		this->switchTime = switchTime;
		totalTime = 0.0f;
		currentImage.x = 3;

		uvRect.width = 150;
		uvRect.height = 150;
	}


	animation:: ~animation() {
	
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

