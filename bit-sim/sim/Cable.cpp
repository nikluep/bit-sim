#define _USE_MATH_DEFINES
#include <cmath>

#include "Cable.h"
#include "PowerNode.h"
#include "../vectorutils.h"

namespace sim {
	const float Cable::CABLE_WIDTH = 7.f;


	Cable::Cable(const PowerNode& nodeIn, PowerNode& nodeOut)
		: ui::BaseElement({}), 
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
	const uint32_t Cable::countDrawables() const
	{
		return 1u;
	}
	const void Cable::gatherDrawables(std::vector<const sf::Drawable*>& drawables) const
	{
		drawables.push_back(&m_shape);
	}

	void Cable::update()
	{
		m_nodeOut->setPower(m_nodeIn->isPowered());
		m_shape.setFillColor(m_nodeIn->isPowered() ? 
			PowerNode::COLOR_POWERED : PowerNode::COLOR_UNPOWERED);
	}


}
