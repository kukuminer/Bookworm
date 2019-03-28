#ifndef UTILITY_H
#define UTILITY_H
#pragma once
#include <bits/stdc++.h>
#include <SFML/System.hpp>
#include "word.h"
#include "tile.h"
#include "object.h"
#include "tilebank.h"
#include "audio.h"

//Forward declarations of classes: States they exist, and are included in the source file
class button;
class character;
class background;


//This class is for all external declarations of objects that need to be accessible from multiple other classes
namespace util //Most things in this namespace are declarations of things meant to be accessible from any class
{
    extern int WINDOWHEIGHT; //Window resolution dimensions
    extern int WINDOWWIDTH;

    extern int rarities[26]; //Chances of getting each letter. Values are read from file
    extern std::vector<std::string> wordlist; //Vectors function like array list. This one is meant to be the entire dictionary
    extern int letterVals[26]; //Damage values of each letter. Values are read from file

    extern word activeWord; //The current word the player has


    /**gameObjects*/
    extern std::vector<object*> gameObjects; //All objects belonging to this vector are drawn during the "adventure" game state
    extern tilebank bank;
    extern character player;
    extern character enemy;
    extern button attackButton;
    extern button scrambleButton;
    extern background gamebg;

    /**menuObjects*/
    extern std::vector<object*> menuObjects; //Objects in this vector are drawn during "menu" game state
    extern background menubg;
    extern button playButton;
    extern button helpButton;
    extern button muteMbutton;
    extern button muteSbutton;
    extern button quitButton;

    /**helpObjects*/
    extern std::vector<object*> helpObjects; //"howto" game state
    extern background helpbg;

    /**loseObjects*/
    extern std::vector<object*> loseObjects; //"lose" game state
    extern background losebg;
    extern button menuButton;


    /**Audio*///Custom class for audio files

    //**Sounds:
    extern std::vector<sf::Sound*> gameSounds;
    extern audio clickSound; //tile_select.ogg
    extern audio attackSound; //attack.wav
    extern audio deathSound; //death.wav
    extern audio scrambleSound; //scramble.ogg
    extern audio buttonSound; //click.ogg
    extern audio wordPower; //wordPower.ogg
    extern audio enemyAttack[audio::numAttackSounds]; //enemy_attack%i.ogg

    //**Music:
    extern std::vector<sf::Music*> gameMusics;
    extern audio menuMusic;
    extern audio advMusic[audio::numSongs];


    extern int TILEDIMS; //Default tile dimensions


    extern sf::Clock fps; //A clock used for the frame setter

    void setRarities(); //Function reads rarities[] from file
    void readWords(); //Reads wordlist vector from file
    void readLetterValues(); //Reads values[] from file
    void frameLimit(int target); //Sets the iteration limit per second to the target
};

namespace patch //This is copy pasted from the Internet, and patches the dysfunctional 'to_string' function, as my IDE does not support it for some reason
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

#endif // UTILITY_H
