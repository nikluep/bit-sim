#pragma once

#include <cstdint>
#include <vector>
#include <memory>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

namespace ui {
	class BaseElement
		: public sf::Drawable
	{
	public:
		BaseElement(const sf::Vector2f& position) : m_position(position) {};

		virtual ~BaseElement() {};
		// TODO: assignment operators, copy/move constructors


		// actions
		virtual void onMouseEnter() {};
		virtual void onMouseExit() {};
		virtual void onMouseDown() {};
		virtual void onMouseUp() {};
		virtual void onDrag(const sf::Vector2f& position) {};

		virtual BaseElement* findMouseConsumer(const sf::Vector2f& point) = 0;

		const sf::Vector2f& getPosition() const { return m_position; };

	protected:
		sf::Vector2f m_position;
	};
}