#include "PowerNode.h"


namespace sim {
	
	constexpr auto RADIUS = 10.f;
	const sf::Color PowerNode::COLOR_POWERED(255, 255, 255);
	const sf::Color PowerNode::COLOR_UNPOWERED(255, 30, 30);

	
	PowerNode::PowerNode(const sf::Vector2f& position)
		: ui::BaseElement({ position, {2*RADIUS, 2*RADIUS}}), 
		m_shape(RADIUS), m_powered(false)
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
		m_powered = !m_powered;
		m_shape.setFillColor(m_powered ? COLOR_POWERED : COLOR_UNPOWERED);
	}
	void PowerNode::onDrag(const sf::Vector2f& position)
	{
	}

	ui::BaseElement* PowerNode::findMouseConsumer(const sf::Vector2f& point)
	{
		return this;
	}
}