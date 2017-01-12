#include "drawing.h"

#ifdef USE_GRAPHICS
sf::RenderWindow * DrawableObject::_window_s = nullptr;
#endif
std::vector<DrawableObject *> DrawableObject::objects;
int DrawableObject::sizex, DrawableObject::sizey;
