#include "simulation.h"

using std::vector;

void Simulation::Init()
{
#ifdef USE_GRAPHICS
    _window = new sf::RenderWindow(sf::VideoMode(_sizex, _sizey), "DHL");
    _window->setFramerateLimit(30);
    DrawableObject::_window_s = _window;
#endif

}
void Simulation::Step()
{
#ifdef USE_GRAPHICS
    if (_window == nullptr)
        throw std::logic_error("Init() not called");
    sf::RectangleShape background(sf::Vector2f((float)_sizex, (float)_sizey));
    background.setOrigin(sf::Vector2f(0.0, 0.0));
    background.setFillColor(sf::Color(200, 200, 255));
    _window->clear();
    _window->draw(background);
    for(vector<DrawableObject*>::iterator i = _objects.begin(); i < _objects.end(); ++i)
    {
        (*i)->Draw();
    }

    _window->display();
#endif

    Input();
}
void Simulation::Input()
{
    #ifdef USE_GRAPHICS
    sf::Event event;
    while (_window->pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            _window->close();
            _isRunning = false;
            break;
        case sf::Event::KeyPressed:
            switch (event.key.code)
            {
            case sf::Keyboard::R:
                break;
            case sf::Keyboard::E:
                break;

            default:
                break;

            }
            break;
        default:
            break;
        }
    }
    #elif
#endif

}
