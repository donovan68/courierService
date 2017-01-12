#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "package.h"
#include "drawing.h"
class Customer : public DrawableObject, PackageContainer
{
public:
    void GenerateTask();
    void Deliver(Package &p);
    void Draw();
};

#endif // CUSTOMER_H
