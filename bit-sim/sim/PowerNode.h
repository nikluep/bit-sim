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
		PowerNode(const sf::Vector2f& position);
		virtual ~PowerNode() {};

		virtual const uint32_t countDrawables() const override;
		virtual const void gatherDrawables(std::vector<const sf::Drawable*>& drawables) const override;

		// actions
		virtual void onMouseUp() override;
		virtual void onDrag(const sf::Vector2f& position) override;

		virtual BaseElement* findMouseConsumer(const sf::Vector2f& point) override;

		void setPower(bool powered) { m_powered = powered; };
		bool isPowered() const { return m_powered; };

	private:
		bool m_powered;
		sf::CircleShape m_shape;

	public:
		static const sf::Color COLOR_POWERED;
		static const sf::Color COLOR_UNPOWERED;
	};
}

