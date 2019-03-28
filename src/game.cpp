#include "game.h"
#include "background.h"
#include "button.h"
#include "audio.h"
#include <SFML/Audio.hpp>
using namespace sf;

gameState game::currentState = menu;

game::game()
{

}

void game::drawGame(RenderWindow &win)
{
    using namespace std;

    bool songPlaying = 0;
    int curSong = 0;
    for(int a = 0; a < audio::numSongs; a++)
    {
        if(util::advMusic[a].getStatus() == SoundSource::Playing)
        {
            songPlaying = 1;
        }
        else
        {
            curSong = a;
        }
    }
    if(!songPlaying && currentState == adventure)
    {
        util::advMusic[(curSong+1) % audio::numSongs].play();
    }


    switch (currentState)
    {
    case menu:
//        cout << "menu\n";
        for(int a = 0; a < util::menuObjects.size(); a++)
        {
            util::menuObjects[a]->intersects(win);
            util::menuObjects[a]->draw(win);
        }
        break;
    case adventure:
        for(int a = 0; a < util::gameObjects.size(); a++)
        {
//          cout << a << "adv\n";
            util::gameObjects[a]->intersects(win);
            util::gameObjects[a]->draw(win);
        }
        break;
    case howto:
//        cout << "howto\n";
        for(int a = 0; a < util::helpObjects.size(); a++)
        {
            util::helpObjects[a]->intersects(win);
            util::helpObjects[a]->draw(win);
        }
        break;
    case lose:
        for(int a = 0; a < util::gameObjects.size(); a++)
        {
            util::gameObjects[a]->draw(win);
        }
        for(int a = 0; a < util::loseObjects.size(); a++)
        {
            util::loseObjects[a]->intersects(win);
            util::loseObjects[a]->draw(win);
        }
        break;
    }
}

void game::updateState(gameState nextState)
{
    currentState = nextState;
    switch (currentState)
    {
    case menu:
        for(int a = 0; a < audio::numSongs; a++)
        {
            util::advMusic[a].stop();
        }
        if(util::menuMusic.getStatus() != SoundSource::Playing)
        {
            util::menuMusic.play();
        }
        for(int a = 0; a < util::gameObjects.size(); a++)
        {
            util::gameObjects[a]->setActive(0);
        }
        for(int a = 0; a < util::helpObjects.size(); a++)
        {
            util::helpObjects[a]->setActive(0);
        }
        for(int a = 0; a < util::loseObjects.size(); a++)
        {
            util::loseObjects[a]->setActive(0);
        }
        for(int a = 0; a < util::menuObjects.size(); a++)
        {
            util::menuObjects[a]->setActive(1);
        }
        break;

    case adventure:
        util::menuMusic.stop();
        util::advMusic[rand()%3].play();
        for(int a = 0; a < util::menuObjects.size(); a++)
        {
            util::menuObjects[a]->setActive(0);
        }
        for(int a = 0; a < util::helpObjects.size(); a++)
        {
            util::helpObjects[a]->setActive(0);
        }
        for(int a = 0; a < util::loseObjects.size(); a++)
        {
            util::loseObjects[a]->setActive(0);
        }
        for(int a = 0; a < util::gameObjects.size(); a++)
        {
            util::gameObjects[a]->setActive(1);
        }
        break;
    case howto:
        for(int a = 0; a < util::gameObjects.size(); a++)
        {
            util::gameObjects[a]->setActive(0);
        }
        for(int a = 0; a < util::menuObjects.size(); a++)
        {
            util::menuObjects[a]->setActive(0);
        }
        for(int a = 0; a < util::loseObjects.size(); a++)
        {
            util::loseObjects[a]->setActive(0);
        }
        for(int a = 0; a < util::helpObjects.size(); a++)
        {
            util::helpObjects[a]->setActive(1);
        }
        break;

    case lose:
        for(int a = 0; a < audio::numSongs; a++)
        {
            util::advMusic[a].stop();
        }
        util::deathSound.play();
        for(int a = 0; a < util::gameObjects.size(); a++)
        {
            util::gameObjects[a]->setActive(0);
        }
        for(int a = 0; a < util::menuObjects.size(); a++)
        {
            util::menuObjects[a]->setActive(0);
        }
        for(int a = 0; a < util::helpObjects.size(); a++)
        {
            util::helpObjects[a]->setActive(0);
        }
        for(int a = 0; a < util::loseObjects.size(); a++)
        {
            util::loseObjects[a]->setActive(1);
        }
        break;
    }
}

void game::reset()
{
    util::bank.scrambleLetters();
    util::gamebg.tex.setString("Kills: 0");
    character::killCount = 0;
    util::player.renewChar();
    util::enemy.renewChar();
    character::isPlayerTurn = 1;
}

game::~game()
{
    //dtor
}
