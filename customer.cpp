#include "customer.h"

std::vector<Customer*> Customer::_customers;

void Customer::Draw()
{
#ifdef USE_GRAPHICS
    if(_window_s == nullptr)
        throw std::out_of_range("Cannot draw on null window");
    sf::CircleShape shape(2);
    if(_packages.size() > 0)
            shape.setFillColor(sf::Color::Yellow);
    else
            shape.setFillColor(sf::Color::Green);
    shape.setOrigin(sf::Vector2f(1,1));
    shape.setPosition(sf::Vector2f((float)_position.x,(float)_position.y));
    _window_s->draw(shape);
#endif
}
void Customer::Step()
{
    if(SimTime::Hour() < _workStart || SimTime::Hour() > _workEnd)
        return;
    if((rand() % 1000 < _dropRate) && _lastHour != SimTime::Hour())
    {
        GenerateTask();
    }
    _lastHour = SimTime::Hour();
}


void Customer::GenerateTask()
{
    int rid, mass;
    do
    {
        rid = rand() % _customers.size();
    } while(rid == _id);
    mass = rand() % 14950 + 50;// In g: 50g - 15000g//
    Package* package = new Package(_id,rid,(double) mass / 1000.0);
    _packages.push_back(package);
}

void Customer::Deliver(Package *p)
{
	if (p == nullptr)
		throw std::out_of_range("Cannot delete nullptr");
    delete p;
	p = nullptr;
}
