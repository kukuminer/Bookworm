#ifndef _TILE_H
#define _TILE_H


#include "object.h"

class tilebank;

class tile : public object {
  public:
    tile(tilebank* par); //Takes the parent tilebank to prevent excessive letter duplication

    //tile(char a); //UNUSED
    virtual ~tile();

    void genRandLetter(); //Sets this tile to a random letter

    char getLetter(); //Returns this tiles letter

    void renewLetter(); //Performs the rest of the initialization associated with creating a new tile

    void click(); //Performs click operations on this tile

    void take(); //Sets this tiles taken bool to true (taken == true means it's part of the word)

    bool isTaken(); //Returns taken bool

    void draw(sf::RenderWindow & win); //Draws this tile to window

    void setPosition(int x, int y); //Sets position to (x,y)

    bool isQ(); //If this tile is a 'Q' (adds a 'U' after)

    int getVal(); //Returns the damage value of this tile

    static void loadtileSheet(); //Loads the tile sprites

    static void loadFont(); //Loads the tile font


  protected:
    char letter; //The letter that this tile is

    int value; //The damage value of this letter

    int position; //This tiles position in the current word

    bool taken; //If this tile is part of the word

    sf::Text display; //The text of this tile

    tilebank* parent; //Pointer to the tilebank that this tile is a part of. Used for letter duplication prevention

    static sf::Texture tileSheet; //Texture to store the tile sprites

    static sf::Font cour; //Font that the tiles use for the letters

};
#endif
