#include "graphic.h"
using namespace sf;

graphic::graphic()
{
    //ctor
}

void graphic::setPosition(int x, int y)
{
    obj.setPosition(x,y);
}

int graphic::getX()
{
    return obj.getPosition().x;
}

int graphic::getY()
{
    return obj.getPosition().y;
}

void graphic::draw(RenderWindow &win)
{
    win.draw(obj);
}

graphic::~graphic()
{
    //dtor
}
