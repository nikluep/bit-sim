#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <functional>

#include "BaseElement.h"


#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>

namespace ui {
    class Button :
        public BaseElement
    {
    public:
        Button(const sf::RectangleShape& shape, const std::string& text);

        virtual ~Button() override = default;
        
        // visual
        virtual const uint32_t countDrawables() const override;
        virtual const void gatherDrawables(std::vector<const sf::Drawable*>& drawables) const override;

        // actions
        virtual void onMouseEnter() override;
        virtual void onMouseExit() override;
        virtual void onMouseDown() override;
        virtual void onMouseUp() override;
        virtual void onDrag(const sf::Vector2f& position) override {};

        virtual BaseElement* findMouseConsumer(const sf::Vector2f& point) override;

        using callback_t = std::function<void()>;
        void addCallback(const callback_t& callback);
    protected:
        sf::RectangleShape m_shape;
        sf::Text m_text;

        std::vector<callback_t> m_callbacks;
    private:
        void setupShape();
    };
}
