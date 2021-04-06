#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include "BaseComponent.h"
#include "PowerNode.h"
#include "../ui/BaseElement.h"

namespace sim {
    class BinaryGate :
        public BaseComponent, public ui::BaseElement
    {
    public:
        virtual ~BinaryGate() = 0;

        // Inherited via BaseComponent
        virtual void update(const std::chrono::nanoseconds& frametime) override;

        // Inherited via BaseElement
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        virtual BaseElement* findMouseConsumer(const sf::Vector2f& point) override;

        PowerNode& getInput1() { return m_in1; };
        PowerNode& getInput2() { return m_in2; };
        const PowerNode& getOutput() const { return m_out; };

    protected:
        BinaryGate() = delete;
        BinaryGate(const sf::Vector2f& position, const std::string& opSymbol);

        virtual bool op(bool lhs, bool rhs) const = 0;

    private:
        PowerNode m_in1, m_in2, m_out;
        sf::RectangleShape m_shape;
        sf::Text m_opSymbol;
    };
    inline BinaryGate::~BinaryGate() = default;

    class ANDGate :
        public BinaryGate
    {
    public:
        ANDGate(const sf::Vector2f& position);
        virtual ~ANDGate() = default;
    private:
        virtual bool op(bool lhs, bool rhs) const override { return lhs & rhs; };
    };
}
