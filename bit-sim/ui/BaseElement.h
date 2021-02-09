#pragma once

#include <cstdint>
#include <vector>
#include <memory>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>

namespace ui {
	class BaseElement
	{
	public:
		BaseElement(const sf::FloatRect& hitbox) : m_hitbox(hitbox) {};
		BaseElement(sf::FloatRect&& hitbox) : m_hitbox(std::move(hitbox)) {};

		virtual ~BaseElement() {};
		// TODO: assignment operators, copy/move constructors

		// visual
		virtual const uint32_t countDrawables() const = 0;
		virtual const void gatherDrawables(std::vector<const sf::Drawable*>& drawables) const = 0;

		// actions
		virtual void onMouseEnter() {};
		virtual void onMouseExit() {};
		virtual void onMouseDown() {};
		virtual void onMouseUp() {};
		virtual void onDrag(const sf::Vector2f& position) {};

		bool contains(const sf::Vector2f& point) const { return m_hitbox.contains(point); };
		virtual BaseElement* findMouseConsumer(const sf::Vector2f& point) = 0;


	protected:

		// TODO: create hitbox class e.g. with rects and circles
		sf::FloatRect m_hitbox;
	};
}