#ifndef PACKAGE_H
#define PACKAGE_H

#include <vector>
#include <iostream>
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
    void SetStatus(Status status)
    {
        _status = status;
        std::cout<< "Package from " << senderId <<" to " << recipentId << ". status changed to: ";
        switch(_status)
        {
        case Announced:
            std::cout<<"Announced";
            break;
        case InPickup:
            std::cout<<"InPickup";
            break;
        case TransitToPickupBranch:
            std::cout<<"TransitToPickupBranch";
            break;
        case AwaitingHubTransport:
            std::cout<<"AwaitingHubTransport";
            break;
        case TransitToHub:
            std::cout<<"TransitToHub";
            break;
        case AwaitingBranchTransport:
            std::cout<<"AwaitingBranchTransport";
            break;
        case TransitToDestinationBranch:
            std::cout<<"TransitToDestinationBranch";
            break;
        case AwaitingDelivery:
            std::cout<<"AwaitingDelivery";
            break;
        case InDelivery:
            std::cout<<"InDelivery";
            break;
        case Completed:
            std::cout<<"Completed";
            break;
        default:
            break;
        }
        std::cout<<"\r\n";
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

    void PutPackage(Package *p)
    {
        _packages.push_back(p);
    }

    Package *GetPackage(ConstIterator i)
    {
        Package *p = const_cast<Package *>(*i);
        _packages.erase(i);
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
