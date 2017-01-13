#ifndef VEHICLE_H
#define VEHICLE_H

#include <vector>
#include <list>
#include "drawing.h"
#include "package.h"
#include "customer.h"

class Vehicle : public DrawableObject , public PackageContainer
{
public:
    Vehicle():
        _speed(1),
        _capacity(300),
        _isRoute(false)
    {}
    Vehicle(int speed, int capacity):
        _speed(speed),
        _capacity(capacity),
        _isRoute(false)
    {}
    void PlanRoute(std::vector<DrawableObject*> route);
    bool isOnRoute() const
    {
        return _isRoute;
    }
    void Step() = 0;
    void Draw();
    bool Move();

protected:


    int _speed;
    double _capacity;
    bool _isRoute;
    std::list<DrawableObject*> _route;
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

protected:
    std::vector<Vehicle*> _vehicles;
};

class DistributionVehicle : public Vehicle
{
public:
    DistributionVehicle()
    {}
    void Distribute()
    {
        _isRoute = true;
    }

    void Step();
};

class Truck : public Vehicle
{
public:
    Truck()
    {
        _speed = 5;
        _capacity = 15000;
        _isRoute = false;
    }

    void Transit()
    {
        _isRoute = true;
    }

    void Step();
};
class Van : public DistributionVehicle
{
public:
    Van()
    {
        _speed = 20;
        _capacity = 1000;
        _isRoute = false;
    }

};
class Scooter : public DistributionVehicle
{
public:
    Scooter()
    {
        _speed = 30;
        _capacity = 40;
        _isRoute = false;
    }

};

#endif // VEHICLE_H
