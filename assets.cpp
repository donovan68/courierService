#include "assets.h"

void Hub::Step()
{

}

void Branch::Step()
{

}

void Hub::Draw()
{
#ifdef USE_GRAPHICS
    if(_window_s == nullptr)
        throw std::out_of_range("Cannot draw on null window");
    sf::RectangleShape shape(sf::Vector2f(10,10));
    shape.setFillColor(sf::Color(0, 10, 255));
    shape.setOrigin(sf::Vector2f(5,5));
    shape.setPosition(sf::Vector2f((float)_position.x,(float)_position.y));
    _window_s->draw(shape);
#endif
}
void Branch::Draw()
{
#ifdef USE_GRAPHICS
    if(_window_s == nullptr)
        throw std::out_of_range("Cannot draw on null window");
    sf::RectangleShape shape(sf::Vector2f(6,6));
    shape.setFillColor(sf::Color(255, 10, 255));
    shape.setOrigin(sf::Vector2f(3,3));
    shape.setPosition(sf::Vector2f((float)_position.x,(float)_position.y));
    _window_s->draw(shape);
#endif
}
