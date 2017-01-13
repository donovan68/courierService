#include "vehicle.h"
using std::vector;
using std::list;

void DistributionVehicle::Step()
{
    if(_route.size() > 0)
    {

        //if(Move(_route.front()))
        {
            //DrawableObject *arrived = _route.front();
            //_route.pop_front();
            /*
            Customer * customer = dynamic_cast<Customer*> arrived;
            Hub *hub = dynamic_cast<Hub*> arrived;
            Branch *branch = dynamic_cast<Branch*> arrived;
            if(customer != nullptr)
            {
                //Take and deliver packages//
            }
            else if(hub != nullptr)
            {
                throw std::logic_error("Distribution vehicles should not visit hub");
            }
            else if(branch != nullptr)
            {
                //Return to branch and deposit all packages//
                for(vector<Package*>::iterator i = _packages.begin(); i != _packages.end(); ++i)
                    branch->PutPackage(*(*i));
                _packages.clear();
                branch->Arrive(*this);
            }
            else
            {
                throw std::logic_error("Casting error");
            }*/
        }
    }
    else
    {
        _isRoute = false;
    }
}
void Truck::Step()
{
    if(_route.size() > 0)
    {
        //Move(*(_route.begin()));
    }
}
bool Vehicle::Move()
{
    DrawableObject *target = _route.front();
    Point offset = target->GetPosition() - _position;
    double len =offset.length();
    if(len < _speed)
    {
        _position += offset;
        _route.pop_front();
        return true;
    }
    else
    {
        double x,y;
        x = (double) offset.x * _speed / len;
        y =(double) offset.y * _speed/ len;
        _position += Point((int) x, (int) y);
    }

    return false;
}
void Vehicle::PlanRoute(std::vector<DrawableObject*> route)
{
    //Add the vector elemets one by one for now//
    for(vector<DrawableObject*>::iterator i = route.begin(); i != route.end(); ++i)
        _route.push_back(*i);
}

void Vehicle::Draw()
{
#ifdef USE_GRAPHICS
    if(!_isRoute)
        return;
    if(_window_s == nullptr)
        throw std::out_of_range("Cannot draw on null window");
    sf::RectangleShape shape(sf::Vector2f(5,3));
    shape.setFillColor(sf::Color(255, 10, 10));
    shape.setOrigin(sf::Vector2f(2.5,1.5));
    shape.setPosition(sf::Vector2f((float)_position.x,(float)_position.y));
    _window_s->draw(shape);
#endif
}
