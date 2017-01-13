#include "assets.h"

using std::vector;
void Hub::Step()
{

}

void Branch::Step()
{
    for(vector<Vehicle*>::iterator i = _vehicles.begin(); i != _vehicles.end(); ++i)
    {
        if((*i)->isOnRoute())
        {
            if((*i)->Move())
            {

            }
        }
    }
    vector<DrawableObject*> distrroute;
    for(vector<Customer*>::iterator i = _customers.begin(); i != _customers.end(); ++i)
    {

        if((*i)->PackageCount() > 0)
        {
            distrroute.push_back(*i);
        }
    }
    for(vector<Vehicle*>::iterator i = _vehicles.begin(); i != _vehicles.end(); ++i)
    {
        if(!(*i)->isOnRoute())
        {
            DistributionVehicle *distr = dynamic_cast<DistributionVehicle*>(*i);
            if(distr != nullptr)
            {
                distr->PlanRoute(distrroute);
                distr->Distribute();
                break;
            }
        }
    }
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
