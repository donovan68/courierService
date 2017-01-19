#ifndef SIMULATION_H
#define SIMULATION_H
#include <vector>
#include <sstream>
#include <iostream>
#include "drawing.h"
#include "vehicle.h"
#include "assets.h"
#include "simtime.h"
class Simulation
{
public:
    Simulation(size_t x, size_t y):
        _sizex(x),
        _sizey(y),
        _time(0),
        _speed(60),
        _isRunning(true),
		_pause(false)
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
	bool _pause;
#ifdef USE_GRAPHICS
    sf::RenderWindow *_window;
#endif
    Hub * _hub;
};

#endif // SIMULATION_H
