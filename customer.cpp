#include "customer.h"

std::vector<Customer*> Customer::_customers;

void Customer::Draw()
{
#ifdef USE_GRAPHICS
    if(_window_s == nullptr)
        throw std::out_of_range("Cannot draw on null window");
    sf::CircleShape shape(2);
    if(_packages.size() > 0)
            shape.setFillColor(sf::Color(125, 255, 10));
    else
            shape.setFillColor(sf::Color(0, 255, 10));
    shape.setOrigin(sf::Vector2f(1,1));
    shape.setPosition(sf::Vector2f((float)_position.x,(float)_position.y));
    _window_s->draw(shape);
#endif
}
void Customer::Step()
{

}
void Customer::GenerateTask()
{

}

void Customer::Deliver(Package &p)
{
    delete &p;
}
