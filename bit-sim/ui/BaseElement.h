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
		BaseElement(const sf::FloatRect& hitbox) : m_hitbox(hitbox) {};

		virtual ~BaseElement() {};
		// TODO: assignment operators, copy/move constructors


		// actions
		virtual void onMouseEnter() {};
		virtual void onMouseExit() {};
		virtual void onMouseDown() {};
		virtual void onMouseUp() {};
		virtual void onDrag(const sf::Vector2f& position) {};

		bool contains(const sf::Vector2f& point) const { return m_hitbox.contains(point); };
		virtual BaseElement* findMouseConsumer(const sf::Vector2f& point) = 0;

		sf::Vector2f getPosition() const;

	protected:

		// TODO: move to children
		sf::FloatRect m_hitbox;
	};
}