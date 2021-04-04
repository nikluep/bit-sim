#pragma once

#include <vector>
#include <memory>

#include <SFML/Graphics/Drawable.hpp>

#include "BaseElement.h"


namespace ui {
	class BaseContainer
		: public BaseElement
	{
	public:
		BaseContainer(const sf::Vector2f& position, const sf::Vector2f& size);
		virtual ~BaseContainer() {};

		// visual
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		virtual BaseElement* findMouseConsumer(const sf::Vector2f& point) override;


		// actions
		std::unique_ptr<BaseElement>& getChild(const int i) { return m_children[i]; }
		const std::unique_ptr<BaseElement>& getChild(const int i) const { return m_children[i]; }

		void addChild(std::unique_ptr<BaseElement>&& pNewChild);

	protected:
		std::vector<std::unique_ptr<BaseElement>> m_children;
		sf::Vector2f m_size;
	};
}