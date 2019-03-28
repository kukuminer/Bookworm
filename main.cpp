#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include "tile.h"
#include "word.h"
#include "utility.hpp"
#include "tilebank.h"
#include "object.h"
#include "button.h"
#include "game.h"
#include "character.h"
#include "background.h"
#include "audio.h"

//namespaces are similar to includes. Any x::y specifies variable y from namespace x
using namespace std;
using namespace sf;
using namespace util;

int main()
{
    RenderWindow window(VideoMode(WINDOWWIDTH,WINDOWHEIGHT), "Bookworm"); //Creates window
    util::readWords(); //util function for reading words from  file to array
    ///CALLED IN TILEBANK CONSTRUCTOR:
//    srand(time(NULL));  //Sets a new seed for rand()
//    util::setRarities();
//    util::readLetterValues();
    tile::loadtileSheet(); //loads tile sprite sheet
    tile::loadFont(); //loads tile font
    character::loadCharSheet(); //loads player sprite
    character::loadMonsters(); //loads monster sprites
    button::loadbuttonSheet(); //loads button sprite sheet
    background::loadBG(); //loads background images


    //Debug (cout is output)
//    cout << util::gameObjects.size() << '\n';
//    cout << util::menuObjects.size() << '\n';
//    cout << util::helpObjects.size() << '\n';
//    cout << util::loseObjects.size() << '\n';
//    cout << "gameMusic size is " << util::gameMusics.size() << '\n';
//    cout << "gameSound size is " << util::gameSounds.size() << '\n';
    game::updateState(menu); //Sets gamestate to menu

    /***********Main Loop begins***********/
    while (window.isOpen())
    {
        Event event; //Window polling, do not touch
        while (window.pollEvent(event)) //Window polls events every tick (iteration of while loop)
        {
            if (event.type == Event::Closed) window.close(); //If window is closed, exit the game
            if (event.type == Event::Resized) //If window is resized
            {
                //WINDOWWIDTH = event.size.width;
                //WINDOWHEIGHT = event.size.height;
                window.setSize(Vector2u(WINDOWWIDTH, WINDOWHEIGHT)); //Prevents resizing of the window
//                cout << "resized to " << WINDOWWIDTH << "x" << WINDOWHEIGHT << '\n';
//                cout << "window.getsize returns " << window.getSize().x << "x" << window.getSize().y << '\n';
            }
            if (event.type == Event::MouseButtonPressed)
            {
                if(event.mouseButton.button == Mouse::Left) //Left mouse pressed
                {
                    for(int a = 0; a < util::gameObjects.size(); a++) //Loops through game objects
                    {
                        if(util::gameObjects[a]->intersects(window)) //If the mouse is intersecting the object
                        {
                            util::gameObjects[a]->click();//Clicks the object
                            break;
                        }
                    }
                    for(int a = 0; a < util::menuObjects.size(); a++)
                    {
                        if(util::menuObjects[a]->intersects(window))
                        {
                            util::menuObjects[a]->click();
                            break;
                        }
                    }
                    for(int a = 0; a < util::helpObjects.size(); a++)
                    {
                        if(util::helpObjects[a]->intersects(window))
                        {
                            util::helpObjects[a]->click();
                            break;
                        }
                    }
                }
                if(event.mouseButton.button == Mouse::Right && game::currentState == adventure) //Right clicked
                {
                    util::activeWord.popLetter(0); //Clears word
                    util::activeWord.updatePos(); //updates tile positions
                }
            }
        }

        if(!character::isPlayerTurn && character::animTimer.getElapsedTime().asSeconds() > 1)
        { //Allows a delay before the enemy attacks
            enemy.attack(player, (character::killCount/6+2));
            util::enemyAttack[rand()%audio::numAttackSounds].play();
        }

        /*******************************************/

        window.clear(Color::Black); //Clears the window after/before each draw

        /*************DRAW GOES IN HERE*************/

        game::drawGame(window); //Draws all game features

        /*******************************************/
        window.display(); //Displays the drawn things to the window
        //cout << 'b';
        frameLimit(60); //Sets the frame (iteration) limit to ~60/second
    }
}
