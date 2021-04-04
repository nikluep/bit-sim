#include "PowerNode.h"


namespace sim {
	
	const float PowerNode::RADIUS = 10.f;
	const sf::Color PowerNode::COLOR_POWERED(255, 255, 255);
	const sf::Color PowerNode::COLOR_UNPOWERED(255, 30, 30);

	
	PowerNode::PowerNode(const sf::Vector2f& position, bool clickable)
		: ui::BaseElement({ position, {2*RADIUS, 2*RADIUS}}), 
		m_shape(RADIUS), m_powered(false), m_clickable(clickable)
	{
		m_shape.setPosition(position);
		m_shape.setFillColor(COLOR_UNPOWERED);
	}
	const uint32_t PowerNode::countDrawables() const
	{
		return 1u;
	}
	const void PowerNode::gatherDrawables(std::vector<const sf::Drawable*>& drawables) const
	{
		drawables.push_back(&m_shape);
	}

	void PowerNode::onMouseUp()
	{
		if (m_clickable) {
			setPower(!m_powered);
		}
	}

	ui::BaseElement* PowerNode::findMouseConsumer(const sf::Vector2f& point)
	{
		return this;
	}
	void PowerNode::setPower(bool powered)
	{
		m_powered = powered;
		m_shape.setFillColor(m_powered ? COLOR_POWERED : COLOR_UNPOWERED);
	}
}