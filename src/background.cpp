#include "background.h"
#include "game.h"
#include "utility.hpp"
using namespace sf;

Texture background::advimage;
Texture background::loseimage;
Texture background::menuimage;
Texture background::helpimage;
Font background::fontin;


background::background(gameState in)
{
    intersectable = 0;
    active = 0;
    obj.setSize(Vector2f(util::WINDOWWIDTH, util::WINDOWHEIGHT));
    obj.setPosition(0,0);
    tex.setFont(fontin);
    switch(in)
    {
    case adventure:
        obj.setTexture(&advimage);
        obj.setTextureRect(Rect<int>(0, 0, 1280, 720));
        tex.setString("Kills: 0");
        tex.setPosition(4*util::WINDOWWIDTH/5, 2*util::WINDOWHEIGHT/3);
        tex.setCharacterSize(42);
        util::gameObjects.insert(util::gameObjects.begin(), this);
        break;
    case menu:
        obj.setTexture(&menuimage);
        obj.setTextureRect(Rect<int>(0, 0, 1280, 720));
        util::menuObjects.insert(util::menuObjects.begin(), this);
        break;
    case howto:
        obj.setTexture(&helpimage);
        obj.setTextureRect(Rect<int>(0,0,1280, 800));
        util::helpObjects.insert(util::helpObjects.begin(), this);
        break;
    case lose:
        obj.setTexture(&loseimage);
        obj.setTextureRect(Rect<int>(0,0, 1280, 720));
        util::loseObjects.push_back(this);
        break;
    }
}


void background::loadBG()
{
    using namespace std;
    if(!advimage.loadFromFile("sprites\\bg.png"))
    {
        cout << "FAILED TO LOAD GAME BG\n";
    }
    if(!loseimage.loadFromFile("sprites\\lose.png"))
    {
        cout << "FAILED TO LOAD LOSE BG\n";
    }
    if(!menuimage.loadFromFile("sprites\\menu.png"))
    {
        cout << "FAILED TO LOAD MENU BG\n";
    }
    if(!helpimage.loadFromFile("sprites\\help.png"))
    {
        cout << "FAILED TO LOAD HELP BG\n";
    }
    if(!fontin.loadFromFile("files\\fontin.ttf"))
    {
        cout << "FAILED TO LOAD FONTIN\n";
    }
}

void background::draw(RenderWindow& win)
{
    object::draw(win);
//    if(game::currentState == adventure)
//    {
        win.draw(tex);
//    }
}

background::~background()
{
    //dtor
}
