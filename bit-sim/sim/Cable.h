#pragma once
#include <chrono>

#include <SFML/Graphics/RectangleShape.hpp>

#include "BaseComponent.h"
#include "../ui/BaseElement.h"

namespace sim {

	class PowerNode;

	class Cable
		: public BaseComponent, public ui::BaseElement
	{
	public:
		Cable(const PowerNode& nodeIn, PowerNode& nodeOut);
		virtual ~Cable() = default;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		virtual BaseElement* findMouseConsumer(const sf::Vector2f& point) override {
			return nullptr;
		};

		virtual void update(const std::chrono::nanoseconds& frametime) override;
	private:
		const PowerNode* m_nodeIn;
		PowerNode* m_nodeOut;
		sf::RectangleShape m_shape;

	public:
		static const float CABLE_WIDTH;
	};
}


