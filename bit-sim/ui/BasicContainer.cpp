#include <SFML/Graphics/RenderTarget.hpp>

#include "BasicContainer.h"
#include "hitbox.h"


namespace ui {
	BasicContainer::BasicContainer(const sf::Vector2f& position, const sf::Vector2f& size)
		: BaseElement(position), m_size(size)
	{
	}
	void BasicContainer::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (const auto& child : m_children) {
			target.draw(*child, states);
		}
	}

	BaseElement* BasicContainer::findMouseConsumer(const sf::Vector2f& point)
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

	void BasicContainer::addChild(std::unique_ptr<BaseElement>&& pNewChild)
	{
		m_children.push_back(std::move(pNewChild));
	}

	void BasicContainer::updatePositioning()
	{
		for (auto& child : m_children) {
			child->updatePositioning();
		}
	}
	void BasicContainer::moveBy(const sf::Vector2f& posChange)
	{
		BaseElement::moveBy(posChange);
		for (auto& child : m_children) {
			child->moveBy(posChange);
		}
	}

	sf::Vector2f BasicContainer::getSize() const
	{
		sf::Vector2f topLeft{}, bottomRight{};

		for (const auto& child : m_children) {
			const auto& pos = child->getPosition();
			const auto& size = child->getSize();

			topLeft = { std::min(topLeft.x, pos.x), std::min(topLeft.y, pos.y) };
			bottomRight = { std::max(bottomRight.x, pos.x + size.x), std::max(bottomRight.y, pos.y + size.y) };
		}
		
		return bottomRight - topLeft;
	}
}