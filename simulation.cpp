#include "simulation.h"

using std::vector;

void Simulation::Init()
{
#ifdef USE_GRAPHICS
    _window = new sf::RenderWindow(sf::VideoMode(_sizex, _sizey), "DHL");
    //_window->setFramerateLimit(30);
    DrawableObject::_window_s = _window;
#endif
    //Set map size//
    DrawableObject::sizex = _sizex;
    DrawableObject::sizey = _sizey;
    //Generate Hub//
    _hub = new Hub;
    _hub->GenerateMap(25, 40,150);
	std::cout << "Initialization complete\r\n";
}
void Simulation::Step()
{
	if(!_pause)
	{
		SimTime::Step(_speed);
		for (vector<DrawableObject*>::iterator i = DrawableObject::objects.begin(); i < DrawableObject::objects.end(); ++i)
		{
			(*i)->Step();
		}
	}
#ifdef USE_GRAPHICS
    if (_window == nullptr)
        throw std::logic_error("Init() not called");
    sf::RectangleShape background(sf::Vector2f((float)_sizex, (float)_sizey));
    background.setOrigin(sf::Vector2f(0.0, 0.0));
    background.setFillColor(sf::Color(200, 200, 255));
    _window->clear();
    _window->draw(background);
    for(vector<DrawableObject*>::iterator i = DrawableObject::objects.begin(); i < DrawableObject::objects.end(); ++i)
    {
        (*i)->Draw();
    }
//Display simulation time//
    sf::Font font;
    sf::Text time;
    std::ostringstream oss;
    time.setFont(font);
    time.setCharacterSize(15);
    time.setColor(sf::Color::Black);
    if(!font.loadFromFile("arial-black.ttf"))
    {
        throw std::runtime_error("Cannot load text font arial-black.ttf");
    }
    oss.width(2);
    oss.fill('0');
    oss<< std::right << SimTime::Hour()<<":";
    oss.width(2);
    oss<<std::right<<SimTime::Minute();
	oss << " Package count:" << Package::TotalCount();
    time.setString(oss.str());
    time.setPosition(sf::Vector2f(5.0,5.0));
    _window->draw(time);
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
				//Report//
				_hub->Print();
                break;
            case sf::Keyboard::E:
				Package::reportStatus = !Package::reportStatus;
                break;
			case sf::Keyboard::G:
				Customer::PackageGenerateToggle();
				break;
			case sf::Keyboard::S:
				_pause= !_pause;
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
