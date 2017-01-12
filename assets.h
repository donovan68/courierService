#ifndef ASSETS_H
#define ASSETS_H

#include <random>
#include "package.h"
#include "vehicle.h"
#include "drawing.h"
#include "customer.h"
#include "point.h"

class Branch : public DrawableObject, public PackageContainer, public VehicleContainer
{
    friend class Hub;
public:
    Branch(int id):
        _id(id)
    {
        _position.x = rand()%sizex;
        _position.y = rand()%sizey;
    }
    void Draw();
    void Step();


private:
    void AddCustomers(size_t no)
    {
        for(size_t j =0; j < no; ++j)
        {
            _customers.push_back(new Customer(_position, _id));
        }
    }
    const int _id;
    std::vector<Customer*> _customers;
};
class Hub : public DrawableObject, public PackageContainer, public VehicleContainer
{
public:
    Hub(int x, int y)
    {
        _position.x = x%sizex;
        _position.y = y%sizey;
    }
    Hub()
    {
        _position.x = rand()%sizex;
        _position.y = rand()%sizey;
    }

    void Draw();
    void Step();
    void GenerateMap(size_t branches, size_t customers_min, size_t customers_max)
    {
        if(_branches.size() > 0)\
            throw std::logic_error("Map already created");
        //Force minimum 1 customer//
        if(customers_max < customers_min)
            throw std::out_of_range("customers_max < customers_min");
        for(size_t i = 0; i < branches; ++i)
        {
            _branches.push_back(new Branch(i));
            size_t customers_no = rand()% (customers_max - customers_min)+ customers_min;
            _branches.back()->AddCustomers(customers_no);
        }
    }

private:
    std::vector<Branch*> _branches;
};


#endif // ASSETS_H
