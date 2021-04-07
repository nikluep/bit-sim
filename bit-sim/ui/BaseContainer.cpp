#include <SFML/Graphics/RenderTarget.hpp>

#include "BaseContainer.h"
#include "hitbox.h"


namespace ui {
	BaseContainer::BaseContainer(const sf::Vector2f& position, const sf::Vector2f& size, const PositioningStrategy& posStrat)
		: BaseElement(position), m_size(size), m_posStrat(posStrat)
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

	void BaseContainer::updatePositioning()
	{
		// TODO: clean up this mess with a sf::Vector replacement
		auto get = [](const sf::Vector2f& vec, const unsigned int i) {
			return i == 0 ? vec.x : vec.y;
		};

		// TODO: filtering depending on absolute positioning
		const auto childCount = m_children.size();
		auto positions = std::vector<float[2]>(childCount);

		for (auto dim = 0u; dim < 2u; ++dim) {

			// accumulate spacing
			positions[0][dim] = m_posStrat.spacing[dim][0];
			for (auto i = 1u; i < childCount; ++i) {
				positions[i][dim] = positions[i - 1][dim] + m_posStrat.spacing[dim][i];		
			}

			// relative spacing
			if (!m_posStrat.absoluteSpacing[dim]) {
				
				// calculate total available space
				auto totalPixelSpace = get(m_size, dim);
				if (m_posStrat.includeElementSize[dim]) {
					for (const auto& child : m_children) {
						totalPixelSpace -= get(child->getSize(), dim);
					}
				}

				// convert to absolute distances
				const auto totalRelativeSpace = 
					positions.back()[dim] + m_posStrat.spacing[dim].back();
				for (auto& pos : positions) {
					pos[dim] *= totalPixelSpace / totalRelativeSpace;
				}
			}

			// convert distances to local coordinates
			auto elementSizeSum = 0.f;
			for (auto i = 0u; i < childCount; ++i) {
				positions[i][dim] += elementSizeSum;
				elementSizeSum += get(m_children[i]->getSize(), dim);
			}
		}
		
		// done
		for (auto i = 0u; i < childCount; ++i) {
			m_children[i]->moveBy(sf::Vector2f(positions[i][0], positions[i][1]));
		}
	}
}