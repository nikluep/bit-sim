#include "Button.h"
#include "common.h"

namespace ui {
	Button::Button(const sf::RectangleShape& shape, const std::string& text)
		: BaseElement(shape.getGlobalBounds()), 
		m_shape(shape),
		m_text(text, ui::font), 
		m_callbacks()
	{
		setupShape();
	}

	const uint32_t Button::countDrawables() const
	{
		return 2u;
	}

	const void Button::gatherDrawables(std::vector<const sf::Drawable*>& drawables) const
	{
		drawables.push_back(&m_shape);
		drawables.push_back(&m_text);
	}

	void Button::onMouseEnter()
	{
		m_shape.setOutlineColor(ui::hoverColor);
	}

	void Button::onMouseExit()
	{
		m_shape.setFillColor(ui::primColor);
		m_shape.setOutlineColor(ui::outlineColor);
	}

	void Button::onMouseDown()
	{
		m_shape.setFillColor(ui::secColor);
	}

	void Button::onMouseUp()
	{
		m_shape.setFillColor(ui::primColor);
		for (const auto callback : m_callbacks) {
			callback();
		}
	}

	BaseElement* Button::findMouseConsumer(const sf::Vector2f& point)
	{
		return this;
	}

	void Button::addCallback(const callback_t& callback)
	{
		m_callbacks.push_back(callback);
	}

	void Button::setupShape()
	{
		m_text.setPosition(m_shape.getPosition());

		m_shape.setFillColor(ui::primColor);
		m_shape.setOutlineColor(ui::outlineColor);

		m_shape.setOutlineThickness(4.f);
	}
}