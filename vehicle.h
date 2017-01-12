#ifndef VEHICLE_H
#define VEHICLE_H

#include <vector>
#include "drawing.h"
#include "package.h"

class Vehicle : public DrawableObject , public PackageContainer
{
public:
    Vehicle(int speed, int capacity):
        _speed(speed),
        _capacity(capacity),
        _isRoute(false)
    {}
    void PlanRoute();
    void Move();
    bool isOnRoute() const
    {
        return _isRoute;
    }
    void Step();
    void Draw();

private:
    const int _speed;
    const double _capacity;
    bool _isRoute;
    std::vector<DrawableObject*> _route;
};

class VehicleContainer
{
public:
    using ConstIterator = std::vector<Vehicle*>::const_iterator;
    void Arrive(Vehicle &v);
    void Dispatch(Vehicle &v);
    ConstIterator begin()
    {
        return _vehicles.begin();
    }
    ConstIterator end()
    {
        return _vehicles.end();
    }

private:
    std::vector<Vehicle*> _vehicles;
};

#endif // VEHICLE_H
