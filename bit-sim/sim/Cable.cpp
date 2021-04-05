#define _USE_MATH_DEFINES
#include <cmath>

#include <SFML/Graphics/RenderTarget.hpp>

#include "Cable.h"
#include "PowerNode.h"
#include "../vectorutils.h"

namespace sim {
	const float Cable::CABLE_WIDTH = 7.f;


	Cable::Cable(const PowerNode& nodeIn, PowerNode& nodeOut)
		: ui::BaseElement(nodeIn.getPosition()), 
		m_nodeIn(&nodeIn), m_nodeOut(&nodeOut),
		m_shape()
	{
		m_shape.setPosition(nodeIn.getPosition() 
			+ sf::Vector2f{PowerNode::RADIUS, PowerNode::RADIUS - CABLE_WIDTH / 2});
		const auto posDiff = nodeOut.getPosition() - nodeIn.getPosition();
		m_shape.setSize({ length(posDiff), CABLE_WIDTH });
		m_shape.setRotation(180 * static_cast<float>(std::atan2(posDiff.y, posDiff.x) / M_PI));

		m_shape.setFillColor(PowerNode::COLOR_UNPOWERED);
	}

	void Cable::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_shape);
	}

	void Cable::update(std::chrono::nanoseconds frametime)
	{
		m_nodeOut->setPower(m_nodeIn->isPowered());
		m_shape.setFillColor(m_nodeIn->isPowered() ? 
			PowerNode::COLOR_POWERED : PowerNode::COLOR_UNPOWERED);
	}


}
