#include "vehicle.h"
using std::vector;
using std::list;

void DistributionVehicle::Step()
{
    if(_route.size() > 0)
    {

    }
    else
    {
        _isRoute = false;
    }
}
void Truck::Step()
{
	if (_route.size() > 0)
	{

	}
	else
	{
		_isRoute = false;
	}
}
bool Vehicle::Move()
{
    DrawableObject *target = _route.front();
    Point offset = target->GetPosition() - _position;
    //Modify offset to allow going through walls//
    if(abs(offset.x) > sizex / 2)
    {
        if(offset.x > 0)
            offset.x = -sizex + offset.x;
        else
            offset.x = sizex + offset.x;
    }
    if(abs(offset.y) > sizey / 2)
    {
        if(offset.y > 0)
            offset.y = -sizey + offset.y;
        else
            offset.y = sizey + offset.y;
    }
    double len = offset.length();

    if(len < _speed)
    {
        _position += offset;
        _asset = _route.front();
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
    _rotation = atan2f(offset.y,offset.x) * 180 / 3.141592;
    _position.Clip(Point(sizex,sizey));
    _asset = nullptr;
    return false;
}
void Vehicle::PlanRoute(std::vector<DrawableObject*> route)
{
    //Add the vector elemets one by one for now//
    for(vector<DrawableObject*>::iterator i = route.begin(); i != route.end(); ++i)
        _route.push_back(*i);
}
void Vehicle::PutPackage(Package *pack)
{
	if (_currentLoad + pack->mass > _capacity)
		throw std::out_of_range("Vehicle full");
	_currentLoad += pack->mass;
	PackageContainer::PutPackage(pack);
}
Package * Vehicle::GetPackage(ConstIterator &i)
{
	Package *pack = PackageContainer::GetPackage(i);
	_currentLoad -= pack->mass;
	return pack;
}
void Vehicle::Draw()
{
#ifdef USE_GRAPHICS
    if(!_isRoute)
        return;
    if(_window_s == nullptr)
        throw std::out_of_range("Cannot draw on null window");
    //sf::Transform t;
    sf::RectangleShape shape(sf::Vector2f(5,3));
    shape.setFillColor(sf::Color(255, 10, 10));
    shape.setOrigin(sf::Vector2f(2.5,1.5));
    shape.setPosition(sf::Vector2f((float)_position.x,(float)_position.y));
    shape.setRotation((float) _rotation);
    //t.rotate(_rotation, sf::Vector2f(0.0,0.0));

    _window_s->draw(shape);
#endif
}
void Van::Draw()
{
#ifdef USE_GRAPHICS
    if(!_isRoute)
        return;
    if(_window_s == nullptr)
        throw std::out_of_range("Cannot draw on null window");
    sf::Transform t;
    sf::RectangleShape shape(sf::Vector2f(5,3));
    shape.setFillColor(sf::Color(130, 10, 125));
    shape.setOrigin(sf::Vector2f(2.5,1.5));
    shape.setPosition(sf::Vector2f((float)_position.x,(float)_position.y));
    t.rotate(_rotation, sf::Vector2f((float)_position.x,(float)_position.y));
    _window_s->draw(shape,t);
#endif
}
void Scooter::Draw()
{
#ifdef USE_GRAPHICS
    if(!_isRoute)
        return;
    if(_window_s == nullptr)
        throw std::out_of_range("Cannot draw on null window");
    sf::Transform t;
    sf::RectangleShape shape(sf::Vector2f(3,2));
    shape.setFillColor(sf::Color(0, 0, 0));
    shape.setOrigin(sf::Vector2f(1.5,1));
    shape.setPosition(sf::Vector2f((float)_position.x,(float)_position.y));
    t.rotate(_rotation, sf::Vector2f((float)_position.x,(float)_position.y));
    _window_s->draw(shape, t);
#endif
}
