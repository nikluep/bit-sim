#include "BaseElement.h"


namespace ui {
    sf::Vector2f BaseElement::getPosition() const
    {
        return { m_hitbox.left, m_hitbox.top };
    }
}