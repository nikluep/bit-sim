#include <vector>

#include "ListContainer.h"


namespace ui {
	ListContainer::ListContainer(const sf::Vector2f& position, const sf::Vector2f& size, const PositioningStrategy& posStrat)
		: BasicContainer(position, size), m_posStrat(posStrat)
	{
	}

	template <unsigned int DIM>
	void ListContainer::updatePositioningAsList()
	{
		BasicContainer::updatePositioning();

		// TODO: clean up this mess with a sf::Vector replacement
		auto getVectorDimension = [](const auto& vec) {
			return DIM == 0 ? vec.x : vec.y;
		};

		// TODO: filtering depending on absolute positioning
		const auto childCount = m_children.size();
		auto positions = std::vector<float[2]>(childCount);
		for (auto& pos : positions) {
			pos[0] = 0.f;
			pos[1] = 0.f;
		}

		// accumulate spacing
		positions[0][DIM] = m_posStrat.spacing[0];
		for (auto i = 1u; i < childCount; ++i) {
			positions[i][DIM] = positions[i - 1][DIM] + m_posStrat.spacing[i];
		}

		// relative spacing
		if (!m_posStrat.absoluteSpacing) {

			// calculate total available space
			auto totalPixelSpace = getVectorDimension(m_size);
			if (m_posStrat.includeElementSize) {
				for (const auto& child : m_children) {
					totalPixelSpace -= getVectorDimension(child->getSize());
				}
			}

			// convert to absolute distances
			const auto totalRelativeSpace =
				positions.back()[DIM] + m_posStrat.spacing.back();
			for (auto& pos : positions) {
				pos[DIM] *= totalPixelSpace / totalRelativeSpace;
			}
		}

		// convert distances to local coordinates
		auto elementSizeSum = 0.f;
		for (auto i = 0u; i < childCount; ++i) {
			positions[i][DIM] += elementSizeSum;
			elementSizeSum += getVectorDimension(m_children[i]->getSize());
		}


		// done
		for (auto i = 0u; i < childCount; ++i) {
			m_children[i]->moveBy(sf::Vector2f(positions[i][0], positions[i][1]));
		}
	}
	HListContainer::HListContainer(const sf::Vector2f& position, const sf::Vector2f& size, const PositioningStrategy& posStrat)
		: ListContainer(position, size, posStrat)
	{
	}
	VListContainer::VListContainer(const sf::Vector2f& position, const sf::Vector2f& size, const PositioningStrategy& posStrat)
		: ListContainer(position, size, posStrat)
	{
	}
}