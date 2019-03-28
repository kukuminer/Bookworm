#ifndef BUTTON_H
#define BUTTON_H
#pragma once
#include "object.h"
#include "utility.hpp"
#include "game.h"
#include "character.h"


enum buttonType { attack, scramble, play, help, gomenu, mutemusic, mutesound, quit }; //Enum for each type of button in the game

class button : public object //Extends object
{
    public:
        button(buttonType in);
        virtual ~button();
        void click(); //Performs click action based on which type of button it is

        //Each subheading below corresponds with a button type.

        /**Attack stuff*/
        void attack(); //When attack button clicked
        void constructAttack(); //Constructs parent's obj to have texture and size of the desired Attack button
        bool intersects(sf::RenderWindow &win); //Custom intersect function (because the button needs to be grayed out if the word is invalid)
        //This intersect function is only used if buttonType == attack, otherwise the parent's intersect function is called

        /**Scramble stuff*/
        void scramble(); //Scrambles the letters
        void constructScramble();

        /**Play stuff*/
        void play(); //Switches current game state to adventure
        void constructPlay();

        /**Help stuff*/
        void help(); //Switches current game state to howto
        void constructHelp();

        /**Go Menu stuff*/
        void gomenu(); //Switches current game state to menu
        void constructGoMenu();

        /**Mute stuff*/
        void mutemusic(); //Mutes the music
        void mutesound(); //Mutes the sound
        void constructMmusic();
        void constructMsound();

        /**Quit stuff*/
        void quit(); //Quits the game
        void constructQuit();

        static void loadbuttonSheet(); //Loads button sprite sheet
    protected:
        buttonType type; //The type of button

        static sf::Texture buttonSheet; //Texture for the button. Applied to parent's RectangleShape obj

    private:
};

#endif // BUTTON_H
