#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "package.h"
#include "drawing.h"
#include <random>
#include <vector>

class Customer : public DrawableObject, public PackageContainer
{
public:
    Customer(Point origin, int branchId):
        _branchId(branchId)
    {
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
    void Deliver(Package &p);
    void Draw();
    void Step();
private:
    const int _branchId;
    static const size_t _minRadius = 60;
    static const size_t _maxRadius = 600;
    static std::vector<Customer*> _customers;
};

#endif // CUSTOMER_H
