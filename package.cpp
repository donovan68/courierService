#include "package.h"

PackageContainer::ConstIterator PackageContainer::FindId(int customerId)
{
    ConstIterator i = begin();
    while(i != end())
    {
        if((*i)->recipentId == customerId)
        {
            return i;
        }
        ++i;
    }
    return i;
}
