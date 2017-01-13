#ifndef PACKAGE_H
#define PACKAGE_H

#include <vector>

class Package
{
    //Friend it to accecs status fields//
    friend class PackageContainer;
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

protected:
    std::vector<Package*> _packages;
    unsigned int _workStart;
    unsigned int _workEnd;
};

#endif // PACKAGE_H
