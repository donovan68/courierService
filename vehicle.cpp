#include "vehicle.h"
void Vehicle::Step()
{

}
void Vehicle::Draw()
{
#ifdef USE_GRAPHICS
    if(_window_s == nullptr)
        throw std::out_of_range("Cannot draw on null window");
    sf::RectangleShape shape(sf::Vector2f(5,3));
    shape.setFillColor(sf::Color(255, 10, 10));
    shape.setOrigin(sf::Vector2f(2.5,1.5));
    shape.setPosition(sf::Vector2f((float)_position.x,(float)_position.y));
    _window_s->draw(shape);
#endif
}
