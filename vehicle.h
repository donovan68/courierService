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
        _rotation(0),
        _speed(1),
        _capacity(300),
		_currentLoad(0.0),
        _isRoute(false),
        _asset(nullptr)
    {}
    Vehicle(int speed, int capacity):
        _speed(speed),
        _capacity(capacity),
		_currentLoad(0.0),
        _isRoute(false)
    {}
    void PlanRoute(std::vector<DrawableObject*> route);
    bool isOnRoute() const
    {
        return _isRoute;
    }
    DrawableObject *CurrentAsset()
    {
        return _asset;
    }
	//Override package load handlers to add capacity handling (exception thrown)//
	void PutPackage(Package *pack);
	Package *GetPackage(ConstIterator &i);
	
    void Step() = 0;
    void Draw();
    bool Move();

protected:

    double _rotation;
    int _speed;
    double _capacity;
	double _currentLoad;
    bool _isRoute;
    std::list<DrawableObject*> _route;
    DrawableObject *_asset;
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
    Truck(Point startpos)
    {
        _position = startpos;
        _speed = 3;
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
    Van(Point startpos)
    {
        _position = startpos;
        _speed = 5;
        _capacity = 1000;
        _isRoute = false;
    }
    void Draw();
};
class Scooter : public DistributionVehicle
{
public:
    Scooter(Point startpos)
    {
        _position = startpos;
        _speed = 8;
        _capacity = 40;
        _isRoute = false;
    }
    void Draw();
};

#endif // VEHICLE_H
