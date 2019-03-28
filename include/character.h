#ifndef CHARACTER_H
#define CHARACTER_H
#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include "object.h"
#include "utility.hpp"
#include "game.h"


class character : public object //Extends object
{
    public: //NB. HP stands for health points
        character(bool isP, int hp); //isPlayer, and max HP
        int getHP(); //Returns current HP
        void attack(character &opp, int dmg); //Attacks opp for dmg damage (directly subtracts from opp.curHP)
        void updateHP(); //Updates the RectangleShape curHPrect
        static void killEnemy(); //Increases killCount and updates the text
        static void killPlayer(); //Sets current game state to 'lose'
        void dmgAnimation(); //Uses the timer on each character to help manage the animation of damage effects
        void updateAnim(); //Uses the timer on each character to manage the breathing effect

        void renewChar(); //Refills the health, and if it's an enemy, applies a new sprite

        static void switchTurn(); //Switches the turn
        void draw(sf::RenderWindow &win); //Draws the character to window. Overrides object draw
        virtual ~character();

        static void loadCharSheet(); //Loads player sprite
        static void loadMonsters(); //Loads enemy sprites



        static bool isPlayerTurn; //if its the players turn
        static int killCount; //Number of monsters the player has killed
        static sf::Clock animTimer; //Clock for managing animations and enemy attack timer
    protected:
        bool isPlayer; //Is this character the player
        int maxHP; //Max HP of this character
        int curHP; //Current HP of this character
        sf::RectangleShape maxHPrect; //Max health bar of this char
        sf::RectangleShape curHPrect; //Current health bar
//        sf::RectangleShape obj;
        sf::Clock gifClock; //For managing the breathing of the characters

        static const int HPwidth = 150; //Dimensions of health bar
        static const int HPheight = 30;
        static sf::Texture charSheet;  //Texture for storing the player sprite
        static const int numPictures = 3; //The number of monster sprites available
        static sf::Texture monsters[];  //Textures for storing the monster sprites
    private:
};

#endif // CHARACTER_H
