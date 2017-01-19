#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "package.h"
#include "drawing.h"
#include "simtime.h"

#include <random>
#include <vector>

class Customer : public DrawableObject, public PackageContainer
{
public:
    Customer(Point origin, int branchId):
        inService(false),
        _branchId(branchId),
        _id(_customers.size())
    {
        _workStart = 8;
        _workEnd = 22;
        int x, y;
        size_t radius;
        do
        {
            x = rand() % _maxRadius - _maxRadius / 2;
            y = rand() % _maxRadius - _maxRadius / 2;
            radius = x * x + y * y;
        }
        while(radius < _maxRadius * _maxRadius && radius > _minRadius * _minRadius);
        _position.x = x + origin.x;
        _position.y = y + origin.y;
        _position.Clip(Point(sizex,sizey));
        _customers.push_back(this);
    }

    void GenerateTask();
    void Deliver(Package *p);
    size_t PackageCount()
    {
        return _packages.size();
    }

    void Draw();
    void Step();
    int GetId()
    {
        return _id;
    }
	static int GetBranchId(int customerId)
	{
		if (_customers.size() < customerId)
			throw std::out_of_range("Invalid Id");
		return _customers.at(customerId)->_branchId;
	}
	static void PackageGenerateToggle()
	{
		_generatePackages = !_generatePackages;
	}
    bool inService;
private:
    const int _branchId;
    const int _id;
    static const size_t _minRadius = 60;
    static const size_t _maxRadius = 1200;
	static const int _dropRate = 50;//in promiles per hour
    unsigned int _lastHour;
    static std::vector<Customer*> _customers;
	static bool _generatePackages;
};

#endif // CUSTOMER_H
