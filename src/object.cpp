#include "object.h"
#include "utility.hpp"
using namespace std;
using namespace sf;


object::object()
{
    intersectable = 1;
    active = 1;
}

object::~object()
{
    //dtor
}

bool object::intersects(RenderWindow &win)
{
    if(!active)
    {
        return 0;
    }
    if(Mouse::getPosition(win).x >= obj.getPosition().x &&
       Mouse::getPosition(win).x <= obj.getPosition().x + obj.getLocalBounds().width &&
       Mouse::getPosition(win).y >= obj.getPosition().y &&
       Mouse::getPosition(win).y <= obj.getPosition().y + obj.getLocalBounds().height)
    {
        obj.setFillColor(Color(255, 255, 255, 255));
        return 1;
    }
    obj.setFillColor(Color(220,220,220,255));
    return 0;
}

void object::setPosition(int x, int y)
{
    obj.setPosition(x,y);
}

void object::setActive(bool in)
{
    if(intersectable)
    {
        active = in;
    }
}

int object::getX()
{
    return obj.getPosition().x;
}

int object::getY()
{
    return obj.getPosition().y;
}

void object::draw(RenderWindow &win)
{
    win.draw(obj);
}

void object::click()
{

}

