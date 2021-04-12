#pragma once
#include "BasicContainer.h"

namespace ui {
	struct PositioningStrategy {
		bool absoluteSpacing{ false };
		bool includeElementSize{ false };
		std::vector<float> spacing{ {0.f} };
	};

	class ListContainer :
		public BasicContainer
	{
	public:

		virtual ~ListContainer() = 0;

	protected:
		ListContainer(const sf::Vector2f& position, const sf::Vector2f& size, const PositioningStrategy& posStrat);

		template <unsigned int DIM>
		void updatePositioningAsList();

		PositioningStrategy m_posStrat;
	};

	inline ListContainer::~ListContainer() = default;

	class HListContainer :
		public ListContainer
	{
	public:
		HListContainer(const sf::Vector2f& position, const sf::Vector2f& size, const PositioningStrategy& posStrat);
		~HListContainer() = default;

		virtual void updatePositioning() override {
			ListContainer::updatePositioningAsList<0u>();
		};
	};

	class VListContainer :
		public ListContainer
	{
	public:
		VListContainer(const sf::Vector2f& position, const sf::Vector2f& size, const PositioningStrategy& posStrat);
		~VListContainer() = default;

		virtual void updatePositioning() override {
			ListContainer::updatePositioningAsList<1u>();
		};
	};
}
