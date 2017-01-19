#include "assets.h"
using std::vector;
void Hub::Step()
{

}
void Hub::GetBranchPackages(std::vector<Package*> &packs, int branchid)
{
	vector<Package*>::const_iterator p = _packages.begin();
	while (p != _packages.end())
	{
		if (Customer::GetBranchId((*p)->recipentId) == branchid)
		{
			Package *pack = GetPackage(p);
			packs.push_back(pack);
		}
		else
			++p;
	}
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
					//Deliver packages//
					PackageContainer::ConstIterator it = (*i)->FindId(customer->GetId());
					while (it != (*i)->end())
					{
						Package *pack = (*i)->GetPackage(it);
						pack->SetStatus(Package::Completed);
						customer->Deliver(pack);
						it = (*i)->FindId(customer->GetId());
					}
                    //Take packages//
					bool full = false;
                    while(customer->PackageCount())
                    {
                        vector<Package*>::const_iterator p = customer->begin();
						while (p != customer->end())
						{
							Package *pack = customer->GetPackage(p);
							pack->SetStatus(Package::TransitToPickupBranch);
							try
							{
								(*i)->PutPackage(pack);
							}
							catch (std::out_of_range)
							{
								//We end up here if the vehicle is full//
								pack->SetStatus(Package::Announced);
								customer->PutPackage(pack);
								//std::cout << "Vehicle full\r\n";
								full = true;
								break;
							}

                        }
						if (full)
							break;
                    }
                    //Mark as not in service//
                    customer->inService = false;
                }
                else if(branch != nullptr)
                {
					//std::cout << "Arrived at branch\r\n";
					if (dynamic_cast<Truck*>(*i) != nullptr)
					{
						_hubSent = false; 
					}
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
                            pack->SetStatus(Package::AwaitingHubTransport);

						PutPackage(pack);
                    }
                }
                else if(hub != nullptr)
                {
                    //Deliver packages to hub//
					vector<Package*>::const_iterator p = (*i)->begin();
					while (p != (*i)->end())
					{
						Package *pack = (*i)->GetPackage(p);
						pack->SetStatus(Package::AwaitingBranchTransport);
						hub->PutPackage(pack); // Put to hub//
					}
					//Take all packages from the hub to the respective branch//
					vector<Package*> branchpack;
					hub->GetBranchPackages(branchpack, _id); // Extract from hub//
					while (branchpack.size() != 0)
					{
						Package *pack = branchpack.back();
						pack->SetStatus(Package::TransitToDestinationBranch);
						try
						{
							(*i)->PutPackage(pack);//Put back to truck//
						}
						catch (std::out_of_range)
						{
							pack->SetStatus(Package::AwaitingBranchTransport);
							std::cout << "Truck full (branch)\r\n";
							break;
						}
						branchpack.pop_back();
					}
					//If any packages left//
					if (branchpack.size() != 0)
					{
						for (vector<Package*>::const_iterator pit = branchpack.begin(); pit < branchpack.end(); ++pit)
						{
							hub->PutPackage(*pit);
						}
						branchpack.clear();
					}
                }
                else
                    throw std::logic_error("Unknown type");

            }
        }
    }
	//Check for working hours//
	if (SimTime::Hour() > _workEnd || SimTime::Hour() < _workStart)
		return;
    //Plan Hub transport for Hub//
    if((SimTime::Hour() == 9 || SimTime::Hour() == 15) && _hubSent == false)
    {
		_hubSent = true;
         vector<Package*> hubpack;
         vector<Package*>::const_iterator htmp = _packages.begin();
		 //Load packages into temporary inventory//
         while(htmp != _packages.end())
         {
             if((*htmp)->GetStatus() == Package::AwaitingHubTransport)
             {
                 hubpack.push_back(GetPackage(htmp));
             }
             else
                 ++htmp;
         }
         if(true)
         {
             //Find available truck//
             for(vector<Vehicle*>::iterator i = _vehicles.begin(); i != _vehicles.end(); ++i)
             {
                 if(!(*i)->isOnRoute())
                 {
                     Truck *truck = dynamic_cast<Truck*>(*i);
                     if(truck != nullptr)
                     {
                         vector<DrawableObject*> truckroute;
                         truckroute.push_back(_hub);
                         truckroute.push_back(this);
                         //Transfer packages for transit into vehicle//
                         while(hubpack.size()!=0)
                         {
                             hubpack.back()->SetStatus(Package::TransitToHub);
							 try
							 { 
								 truck->PutPackage(hubpack.back());
							 }
							 catch (std::out_of_range)
							 {
								 hubpack.back()->SetStatus(Package::AwaitingHubTransport);
								 std::cout << "Truck full (branch)\r\n";
								 break;
							 }
                             hubpack.pop_back();
                         }

                         truck->PlanRoute(truckroute);
                         truckroute.clear();
                         truck->Transit();
                     }
                 }
             }
         }

		 //Return unused packages to storage//
		 if (hubpack.size() != 0)
		 {
			 for (vector<Package*>::const_iterator pit = hubpack.begin(); pit < hubpack.end(); ++pit)
			 {
				 PutPackage(*pit);
			 }
			 hubpack.clear();
		 }
    }
    //Plan pickup route for vehicles//
	vector<DrawableObject*> pickuproute;
    for(vector<Customer*>::iterator i = _customers.begin(); i != _customers.end(); ++i)
    {
        if((*i)->PackageCount() > 0 && (*i)->inService == false)
        {
            pickuproute.push_back(*i);
        }
    }
    vector<Package*> tmppack;
    vector<Package*>::const_iterator ptmp = _packages.begin();
	//Plan delivery route for vehicles and store packages in the buffer//
    while(ptmp != _packages.end())
    {
        if((*ptmp)->GetStatus() == Package::AwaitingDelivery)
        {
            tmppack.push_back(GetPackage(ptmp));
        }
        else
            ++ptmp;
    }
    //Check if we need to go anywhere with distribution vehicle//
    if(tmppack.size() > 0 || pickuproute.size() > 0)
    {
		//Iterate available vehicles//
        for(vector<Vehicle*>::iterator i = _vehicles.begin(); i != _vehicles.end(); ++i)
        {
			//If available (not on route to customers)//
            if(!(*i)->isOnRoute())
            {
                DistributionVehicle *distr = dynamic_cast<DistributionVehicle*>(*i);
                if(distr != nullptr)
                {
					if (tmppack.size() == 0 && pickuproute.size() == 0)
						break;
					//First try to exhaust all pickup options//
					vector<DrawableObject*> vehroute;
					double capacity_used = 0.0;
					while (pickuproute.size() > 0)
					{
						double packweight = dynamic_cast<Customer*>(pickuproute.back())->GetWeight();
						if (capacity_used + packweight > distr->Capacity())
						{
							//Cannot plan more on this route//
							break;
						}
						vehroute.push_back(pickuproute.back());
						pickuproute.pop_back();
						capacity_used += packweight;
					}
					//Try to exhaust all delivery options//
					while (tmppack.size() > 0)
					{
						//Verify mass constraint//
						if (capacity_used + tmppack.back()->mass > distr->Capacity())
						{
							//Cannot plan more on this route//
							break;
						}
						//Find respective customer//
						Customer *cust = FindCustomer(tmppack.back()->recipentId);
						//Check route for duplicate//
						if (cust == nullptr)
							throw std::logic_error("No such customer");
						//Check if he is already in delivery route we are planning//
						bool exists = false;
						for (vector<DrawableObject*>::iterator tmpit = vehroute.begin(); tmpit != vehroute.end(); ++tmpit)
						{
							if (dynamic_cast<Customer*>(*tmpit) == cust)
							{
								exists = true;
								break;
							}
						}
						if (!exists)
							vehroute.push_back(cust);
						//Load vehicle//
						capacity_used += tmppack.back()->mass;
						tmppack.back()->SetStatus(Package::InDelivery);
						distr->PutPackage(tmppack.back());
						tmppack.pop_back();
					}
					//Mark customers as in service//
					for (vector<DrawableObject*>::iterator tmpit = vehroute.begin(); tmpit != vehroute.end(); ++tmpit)
					{
						Customer *tmpcust = dynamic_cast<Customer*>(*tmpit);
						if (tmpcust != nullptr)
						{
							tmpcust->inService = true;
						}
					}
					vehroute.push_back(this);
                    distr->PlanRoute(vehroute);
                    distr->Distribute();
                    vehroute.clear();
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

}
void Branch::Print()
{
	std::cout << "Branch no: " << _id << "\r\n";
	PackageContainer::Print();
}
void Hub::Print()
{
	std::cout << "Hub: " << "\r\n";
	PackageContainer::Print();
	for (std::vector<Branch*>::iterator i = _branches.begin(); i != _branches.end(); ++i)
	{
		(*i)->Print();
	}
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
