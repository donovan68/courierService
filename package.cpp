#include "package.h"

PackageContainer::ConstIterator PackageContainer::FindId(int customerId)
{
    ConstIterator i = begin();
    while(i != end())
    {
        if((*i)->recipentId == customerId)
        {
			std::cout << "Found:" << customerId << "\r\n";
            return i;
        }
        ++i;
    }
    return i;
}
std::ostream& operator<<(std::ostream& os, const Package &p)
{
	os << "Package from " << p.senderId << " to " << p.recipentId << " of mass " << p.mass << ", status: " << p.GetStatusString();
	return os;
}
std::string Package::GetStatusString() const
{
	switch (_status)
	{
	case Announced:
		return "Announced";
		break;
	case InPickup:
		return "InPickup";
		break;
	case TransitToPickupBranch:
		return "TransitToPickupBranch";
		break;
	case AwaitingHubTransport:
		return "AwaitingHubTransport";
		break;
	case TransitToHub:
		return "TransitToHub";
		break;
	case AwaitingBranchTransport:
		return "AwaitingBranchTransport";
		break;
	case TransitToDestinationBranch:
		return "TransitToDestinationBranch";
		break;
	case AwaitingDelivery:
		return "AwaitingDelivery";
		break;
	case InDelivery:
		return "InDelivery";
		break;
	case Completed:
		return "Completed";
		break;
	default:
		return "Unknown status";
		break;
	}
	return "";
}