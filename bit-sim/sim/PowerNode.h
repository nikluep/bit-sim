#pragma once
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include <SFML/Graphics/Color.hpp>

#include "../ui/BaseElement.h"

namespace sim {
	class PowerNode
		: public ui::BaseElement
	{
	public:
		PowerNode(const sf::Vector2f& position, bool clickable = false);
		virtual ~PowerNode() {};

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		// actions
		virtual void onMouseUp() override;

		virtual BaseElement* findMouseConsumer(const sf::Vector2f& point) override;

		void setPower(bool powered);
		bool isPowered() const { return m_powered; };

	private:
		bool m_powered;
		const bool m_clickable;
		sf::CircleShape m_shape;

	public:
		static const float RADIUS;
		static const sf::Color COLOR_POWERED;
		static const sf::Color COLOR_UNPOWERED;
	};
}

