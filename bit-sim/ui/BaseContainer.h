#pragma once

#include <vector>
#include <memory>

#include <SFML/Graphics/Drawable.hpp>

#include "BaseElement.h"


namespace ui {
	struct PositioningStrategy {
		bool absoluteSpacing[2]{ false, false };
		bool includeElementSize[2]{ false, false };
		std::vector<float> spacing[2]{ {0.f}, {0.f} };
	};

	class BaseContainer
		: public BaseElement
	{
	public:
		BaseContainer(const sf::Vector2f& position, const sf::Vector2f& size, const PositioningStrategy& posStrat);
		virtual ~BaseContainer() = default;

		// visual
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		virtual BaseElement* findMouseConsumer(const sf::Vector2f& point) override;


		// actions
		std::unique_ptr<BaseElement>& getChild(const int i) { return m_children[i]; }
		const std::unique_ptr<BaseElement>& getChild(const int i) const { return m_children[i]; }

		void addChild(std::unique_ptr<BaseElement>&& pNewChild);

		virtual void updatePositioning() override;
	protected:
		std::vector<std::unique_ptr<BaseElement>> m_children;
		sf::Vector2f m_size;
		PositioningStrategy m_posStrat;
	};
}