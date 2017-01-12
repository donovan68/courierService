#ifndef SIMULATION_H
#define SIMULATION_H
#include <vector>
#include "drawing.h"
#include "vehicle.h"
#include "assets.h"

class Simulation
{
public:
    Simulation(size_t x, size_t y):
        _sizex(x),
        _sizey(y),
        _time(0),
        _speed(1),
        _isRunning(true)
    {

    }

    void Init();
    void Step();
    void Input();
    bool IsRunning() const
    {
        return _isRunning;
    }

private:
    const size_t _sizex,_sizey;
    unsigned long _time;
    unsigned int _speed;
    bool _isRunning;
    std::vector<DrawableObject*> _objects;
#ifdef USE_GRAPHICS
    sf::RenderWindow *_window;
#endif
};

#endif // SIMULATION_H
