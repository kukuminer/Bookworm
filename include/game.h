#ifndef _GAME_H
#define _GAME_H
#include <SFML/Graphics.hpp>


enum gameState : int { menu, adventure, howto, lose };

class game {
  public:
    game();

    static void drawGame(sf::RenderWindow& win); //Draws all the objects in object* vectors (basically draws the whole game)

    static gameState currentState; //The current game state (see enum above)

    static void reset(); //Resets the game (when the player loses)

    static void updateState(gameState nextState); //Updates the game state to the given one

    virtual ~game();

};
#endif
