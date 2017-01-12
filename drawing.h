#ifndef DRAWING_H
#define DRAWING_H

#define USE_GRAPHICS
#ifdef USE_GRAPHICS
#include <SFML/Graphics.hpp>
#endif
#include <vector>
#include "point.h"
class DrawableObject
{
public:
    DrawableObject()
    {
        objects.push_back(this);
    }

    virtual void Draw() = 0;
    virtual void Step() = 0;
#ifdef USE_GRAPHICS
    //Link window for graphics display of elements//
    static sf::RenderWindow *_window_s;
#endif
    //Vector of all objects in the simulation//
    static std::vector<DrawableObject *> objects;
    //Map limits for reference//
    static int sizex, sizey;
protected:
    Point _position;
};

#endif // DRAWING_H
