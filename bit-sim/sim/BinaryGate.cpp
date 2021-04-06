#include <SFML/Graphics/RenderTarget.hpp>

#include "BinaryGate.h"
#include "../ui/common.h"

namespace sim {
	constexpr auto GATE_SIZE = 100.f;

	BinaryGate::BinaryGate(const sf::Vector2f& position, const std::string& opSymbol)
		: BaseElement(position),
		BaseComponent(),
		m_shape({ GATE_SIZE, GATE_SIZE }),
		m_opSymbol(opSymbol, ui::getFont()),
		m_in1(position + sf::Vector2f{0.f, GATE_SIZE/3}),
		m_in2(position + sf::Vector2f{ 0.f, 2*GATE_SIZE / 3 }),
		m_out(position + sf::Vector2f{ GATE_SIZE, GATE_SIZE / 2 })
	{
		m_shape.setPosition(position);
		m_shape.setFillColor(sf::Color::Black);
		m_shape.setOutlineColor(sf::Color(120, 120, 120));
		m_shape.setOutlineThickness(5.f);

		m_opSymbol.setPosition(position);
	}
	void BinaryGate::update(const std::chrono::nanoseconds& frametime)
	{
		m_out = op(m_in1, m_in2);
	}

	void BinaryGate::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_shape, states);
		target.draw(m_in1, states);
		target.draw(m_in2, states);
		target.draw(m_out, states);
		target.draw(m_opSymbol, states);
	}


	ui::BaseElement* BinaryGate::findMouseConsumer(const sf::Vector2f& point)
	{
		return nullptr;
	}



	ANDGate::ANDGate(const sf::Vector2f& position)
		: BinaryGate(position, "&")
	{
	}
}