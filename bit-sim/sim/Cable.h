#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

#include "../ui/BaseElement.h"

namespace sim {

	class PowerNode;

	class Cable
		: public ui::BaseElement
	{
	public:
		Cable(const PowerNode& nodeIn, PowerNode& nodeOut);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		virtual BaseElement* findMouseConsumer(const sf::Vector2f& point) override {
			return nullptr;
		};

		void update();
	private:
		const PowerNode* m_nodeIn;
		PowerNode* m_nodeOut;
		sf::RectangleShape m_shape;

	public:
		static const float CABLE_WIDTH;
	};
}


