#include <SFML/Graphics/RenderTarget.hpp>

#include "BaseContainer.h"
#include "hitbox.h"


namespace ui {
	BaseContainer::BaseContainer(const sf::Vector2f& position, const sf::Vector2f& size)
		: BaseElement(position), m_size(size)
	{
	}
	void BaseContainer::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (const auto& child : m_children) {
			target.draw(*child, states);
		}
	}

	BaseElement* BaseContainer::findMouseConsumer(const sf::Vector2f& point)
	{
		if (!containedByRect(m_position, m_size, point)) {
			return nullptr;
		}

		for (const auto& child : m_children) {
			auto* consumer = child->findMouseConsumer(point);
			if (consumer != nullptr) {
				return consumer;
			}
		}
		return nullptr;
	}

	void BaseContainer::addChild(std::unique_ptr<BaseElement>&& pNewChild)
	{
		m_children.push_back(std::move(pNewChild));
	}
}