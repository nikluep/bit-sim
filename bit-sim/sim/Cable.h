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

		virtual const uint32_t countDrawables() const override;
		virtual const void gatherDrawables(std::vector<const sf::Drawable*>& drawables) const override;

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


