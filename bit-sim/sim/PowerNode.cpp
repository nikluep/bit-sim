#include <SFML/Graphics/RenderTarget.hpp>

#include "PowerNode.h"
#include "../ui/hitbox.h"

namespace sim {
	
	const float PowerNode::RADIUS = 10.f;
	const sf::Color PowerNode::COLOR_POWERED(255, 255, 255);
	const sf::Color PowerNode::COLOR_UNPOWERED(255, 30, 30);

	
	PowerNode::PowerNode(const sf::Vector2f& position, bool clickable)
		: ui::BaseElement(position), 
		m_shape(RADIUS), m_powered(false), m_clickable(clickable)
	{
		m_shape.setPosition(position);
		m_shape.setFillColor(COLOR_UNPOWERED);
	}

	void PowerNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_shape);
	}

	void PowerNode::onMouseUp()
	{
		if (m_clickable) {
			setPower(!m_powered);
		}
	}

	ui::BaseElement* PowerNode::findMouseConsumer(const sf::Vector2f& point)
	{

		return m_clickable && containedByCircle(m_position, RADIUS, point)
			? this : nullptr;
	}
	void PowerNode::setPower(bool powered)
	{
		m_powered = powered;
		m_shape.setFillColor(m_powered ? COLOR_POWERED : COLOR_UNPOWERED);
	}
}