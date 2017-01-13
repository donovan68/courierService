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
                DrawableObject *where = (*i)->CurrentAsset();
                if(where == nullptr)
                    throw std::logic_error("Cannot resolve current asset");
                Customer *customer = dynamic_cast<Customer*>(where);
                Branch *branch = dynamic_cast<Branch*>(where);
                Hub *hub = dynamic_cast<Hub*>(where);
                if(customer!=nullptr)
                {
                    //Deliver and take packages//
                    while(customer->PackageCount())
                    {
                        vector<Package*>::const_iterator p = customer->begin();
                        while(p != customer->end())
                        {
                            Package *pack = customer->GetPackage(p);
                            pack->SetStatus(Package::TransitToPickupBranch);
                            (*i)->PutPackage(pack);
                        }

                    }
                }
                else if(branch != nullptr)
                {
                    //Put all packages to branch//
                    vector<Package*>::const_iterator p = (*i)->begin();
                    while(p != (*i)->end())
                    {
                        Package *pack = (*i)->GetPackage(p);
                        //If recipent exists in database of current branch//
                        bool branchCustomer = false;
                        for(vector<Customer*>::iterator i = _customers.begin(); i != _customers.end(); ++i)
                        {
                            if((*i)->GetId() == pack->recipentId)
                            {
                                branchCustomer = true;
                                break;
                            }
                        }
                        if(branchCustomer)
                            pack->SetStatus(Package::AwaitingDelivery);
                        else
                            pack->SetStatus(Package::TransitToHub);
                        PutPackage(*p);

                    }
                }
                else if(hub != nullptr)
                {
                    //Deliver packages to hub//
                }
                else
                    throw std::logic_error("Unknown type");

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
    distrroute.push_back(this);
    if(distrroute.size() > 1)
    {
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
