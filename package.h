#ifndef PACKAGE_H
#define PACKAGE_H

#include <vector>

class Package
{
public:
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
private:
    //Sender and recipent//
    double _mass;
    Status _status;
};
class PackageContainer
{
public:
    using ConstIterator = std::vector<Package*>::const_iterator;
    void PutPackage(Package &p)
    {
        _packages.push_back(&p);
    }

    Package &GetPackage(ConstIterator i)
    {
        Package *p = const_cast<Package *>(*i);
        _packages.erase(i);
        return *p;
    }

    ConstIterator begin()
    {
        return _packages.begin();
    }
    ConstIterator end()
    {
        return _packages.end();
    }
private:
    std::vector<Package*> _packages;
};

#endif // PACKAGE_H
