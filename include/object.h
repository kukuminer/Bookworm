#ifndef OBJECT_H
#define OBJECT_H
#pragma once
#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

class object //Everything that is drawn to the window extends this class
{
    public:
        object();
        virtual ~object(); //Destructor - pre made for every class. I don't use these

        //Virtual functions try to call the child's version of the function first, before calling the parent's
        virtual bool intersects(sf::RenderWindow &win); //Checks if the mouse intersects this object
        virtual void click(); //Performs click operation on this object

        void setPosition(int x, int y); //Sets position of this object
        virtual void draw(sf::RenderWindow &win); //Draws this object to window

        void setActive(bool in); //Changes whether the object is interactable or not

        int getX(); //Returns x position of obj
        int getY(); //Returns y position of obj


    protected:
        sf::RectangleShape obj; //The shape that is this object itself
        bool intersectable; //If the object is ever interactable
        bool active; //If the object is currently interactable


    private:
};

#endif // OBJECT_H
