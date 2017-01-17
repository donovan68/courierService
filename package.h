#ifndef PACKAGE_H
#define PACKAGE_H

#include <vector>
#include <iostream>
#include <string>
class Package
{
public:
    Package(int sender, int recipent, double packageMass):
        senderId(sender),
        recipentId(recipent),
        mass(packageMass),
        _status(Announced)
    {

    }

    enum Status
    {
        Announced,
        InPickup,
        TransitToPickupBranch,
        AwaitingHubTransport,
        TransitToHub,
        AwaitingBranchTransport,
        TransitToDestinationBranch,
        AwaitingDelivery,
        InDelivery,
        Completed
    };
    Status GetStatus()
    {
        return _status;
    }
	friend std::ostream& operator<<(std::ostream& os, const Package & p);
	std::string GetStatusString()const;
    void SetStatus(Status status)
    {
        _status = status;
        std::cout << "Package from " << senderId <<" to " << recipentId << ". status changed to: ";
		std::cout << GetStatusString();
        std::cout << "\r\n";
    }
    //Sender and recipent//
    const int senderId, recipentId;
    const double mass;
private:
    Status _status;
};

class PackageContainer
{
public:
    using ConstIterator = std::vector<Package*>::const_iterator;
	using Iterator = std::vector<Package*>::iterator;
    void PutPackage(Package *p)
    {
		std::cout << "Loading: " << *p << "\r\n";
        _packages.push_back(p);
    }

    Package *GetPackage(ConstIterator &i)
    {
		if (i == _packages.end())
			throw std::out_of_range("Invalid iterator");
        Package *p = const_cast<Package *>(*i);
		Iterator in = _packages.erase(i, i);
		std::cout << "Removing: " << *p << " Packages  size: " << _packages.size() - 1<<"\r\n";
        i = _packages.erase(in);
		if (i != _packages.end())
			std::cout << "Iterator points to: " << (*i)->recipentId << "\r\n";
        return p;
    }
    ConstIterator FindId(int customerId);

    ConstIterator begin()
    {
        return _packages.begin();
    }
    ConstIterator end()
    {
        return _packages.end();
    }

protected:
    std::vector<Package*> _packages;
    unsigned int _workStart;
    unsigned int _workEnd;
};

#endif // PACKAGE_H
