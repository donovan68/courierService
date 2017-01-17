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
                    //Take packages//
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
                    //Deliver packages//
                    PackageContainer::ConstIterator it = (*i)->FindId(customer->GetId());
                    while(it != (*i)->end())
                    {
                        Package *pack = (*i)->GetPackage(it);
                        pack->SetStatus(Package::Completed);
                        customer->Deliver(pack);
                        it = (*i)->FindId(customer->GetId());
                    }
                    //Mark as not in service//
                    customer->inService = false;
                }
                else if(branch != nullptr)
                {
					std::cout << "Arrived at branch\r\n";
                    //Put all packages to branch//
                    vector<Package*>::const_iterator p = (*i)->begin();
                    while(p != (*i)->end())
                    {
                        Package *pack = (*i)->GetPackage(p);
                        //If recipent exists in database of current branch//
                        bool branchCustomer = false;
                        for(vector<Customer*>::iterator c = _customers.begin(); c != _customers.end(); ++c)
                        {
                            if((*c)->GetId() == pack->recipentId)
                            {
                                branchCustomer = true;
                                break;
                            }
                        }
                        if(branchCustomer)
                            pack->SetStatus(Package::AwaitingDelivery);
                        else
                            pack->SetStatus(Package::TransitToHub);
                        
						PutPackage(pack);
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
    //Plan pickup route for vehicles//
    vector<DrawableObject*> distrroute;
    for(vector<Customer*>::iterator i = _customers.begin(); i != _customers.end(); ++i)
    {
        if((*i)->PackageCount() > 0 && (*i)->inService == false)
        {
            distrroute.push_back(*i);
        }
    }
    vector<Package*> tmppack;
    vector<Package*>::const_iterator ptmp = _packages.begin();
    while(ptmp != _packages.end())
    {
        if((*ptmp)->GetStatus() == Package::AwaitingDelivery)
        {
            tmppack.push_back(GetPackage(ptmp));
            //Add appropriate customer to route//
            Customer *cust = FindCustomer(tmppack.back()->recipentId);
            {
                 if(cust == nullptr)
                    throw std::logic_error("No such customer");
                 //Check if he is already in route we are travelling//
                 bool exists = false;
                 for(vector<DrawableObject*>::iterator tmpit = distrroute.begin(); tmpit != distrroute.end(); ++tmpit)
                 {
                     if(dynamic_cast<Customer*>(*tmpit) == cust)
                     {
                         exists = true;
                         break;
                     }
                 }
                 if(!exists)
                    distrroute.push_back(cust);
            }
        }
        else
            ++ptmp;
    }
    //Check if we need to go anywhere with distribution vehicle//
    if(distrroute.size() > 0)
    {
        distrroute.push_back(this);
        for(vector<Vehicle*>::iterator i = _vehicles.begin(); i != _vehicles.end(); ++i)
        {
            if(!(*i)->isOnRoute())
            {
                DistributionVehicle *distr = dynamic_cast<DistributionVehicle*>(*i);
                if(distr != nullptr)
                {
                    //One can add looking for most suitable vehicle//
                    if(distrroute.size() > 0)
                    {
                        //Transfer packages for distribution into vehicle//
                        while(tmppack.size()!=0)
                        {
                            tmppack.back()->SetStatus(Package::InDelivery);
                            distr->PutPackage(tmppack.back());
                            tmppack.pop_back();
                        }
                        //Mark customers as in service//
                        for(vector<DrawableObject*>::iterator tmpit = distrroute.begin(); tmpit != distrroute.end(); ++tmpit)
                        {
                            Customer *tmpcust = dynamic_cast<Customer*>(*tmpit);
                            if(tmpcust != nullptr)
                            {
                                tmpcust->inService = true;
                            }
                        }
                        distr->PlanRoute(distrroute);
                        distr->Distribute();
                        distrroute.clear();
                        break;
                    }
                }
            }
        }
    }
    //If no vehicle was available return packages to the inventory//
    if(tmppack.size() != 0)
    {
        for(vector<Package*>::const_iterator pit = tmppack.begin(); pit < tmppack.end(); ++pit)
        {
            PutPackage(*pit);
        }
        tmppack.clear();
    }
    //If no customer can be handled unmark them from used//

}
Customer *Branch::FindCustomer(int id)
{
    for(vector<Customer*>::iterator i = _customers.begin(); i != _customers.end(); ++i)
    {
        if((*i)->GetId() == id)
        {
            return *i;
        }
    }
    return nullptr;
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
