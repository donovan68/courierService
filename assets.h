#ifndef ASSETS_H
#define ASSETS_H

#include "package.h"
#include "vehicle.h"
#include "drawing.h"
#include "point.h"

class Hub : public DrawableObject, public PackageContainer, public VehicleContainer
{
public:
    void Draw();
    void Step();
private:

};
class Branch : public DrawableObject, public PackageContainer, public VehicleContainer
{
public:
    void Draw();
    void Step();
private:
};

#endif // ASSETS_H
