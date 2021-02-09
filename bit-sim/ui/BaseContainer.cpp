#include "BaseContainer.h"


namespace ui {

	const uint32_t BaseContainer::countDrawables() const
	{
		uint32_t count = 0u;
		for (const auto& child : m_children) {
			count += child->countDrawables();
		}
		return count;
	}

	const void BaseContainer::gatherDrawables(std::vector<const sf::Drawable*>& drawables) const
	{
		for (const auto& child : m_children) {
			child->gatherDrawables(drawables);
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