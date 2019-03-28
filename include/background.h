#ifndef BACKGROUND_H
#define BACKGROUND_H
#include "object.h"

//enum gameState { menu, adventure, howto };
enum gameState : int; //Forward declaration of the enum. States that it exists elsewhere. int states the amount of memory allocation required

class background : public object //Extends object
{
    public:
        background(gameState in);


        void draw(sf::RenderWindow& win); //Draws parent obj (sf::RectangleShape) to window
        static void loadBG(); //Loads background images
        static sf::Font cour; //A font for any text used
        virtual ~background();
        sf::Text tex; //Text
    protected:
        static sf::Texture advimage; //Texture for the adventure screen background
        static sf::Texture loseimage; //etc
        static sf::Texture menuimage;
        static sf::Texture helpimage;
        static sf::Font fontin; //Font to use for tex
    private:
};

#endif // BACKGROUND_H
