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
		using BaseElement::BaseElement; // inherit Baseclass constructors

		virtual ~BaseContainer() {};

		// visual
		virtual const uint32_t countDrawables() const override;
		virtual const void gatherDrawables(std::vector<const sf::Drawable*>& drawables) const override;

		virtual BaseElement* findMouseConsumer(const sf::Vector2f& point) override;

		// actions
		std::unique_ptr<BaseElement>& getChild(const int i) { return m_children[i]; }
		const std::unique_ptr<BaseElement>& getChild(const int i) const { return m_children[i]; }

		void addChild(std::unique_ptr<BaseElement>&& pNewChild) {
			m_children.push_back(std::move(pNewChild));
		};

	protected:
		std::vector<std::unique_ptr<BaseElement>> m_children;
	};
}