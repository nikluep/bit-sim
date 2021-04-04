#include <SFML/Graphics/RenderTarget.hpp>

#include "BaseContainer.h"


namespace ui {
	void BaseContainer::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (const auto& child : m_children) {
			target.draw(*child, states);
		}
	}

	BaseElement* BaseContainer::findMouseConsumer(const sf::Vector2f& point)
	{
		for (const auto& child : m_children) {
			if (child->contains(point)) {
				return child->findMouseConsumer(point);
			}
		}
		return nullptr;
	}
}