#ifndef _WORD_H
#define _WORD_H
#include <bits/stdc++.h>


class tile;


//This class is the current word that the player has spelled
class word {
  public:
    word();

    virtual ~word();

    void addLetter(tile* in); //Adds a pointer to a tile from the tile bank

    void popLetter(int pos); //Pops letters (pos -> end)

    bool check(); //Checks if the current word is a valid English word

    std::string getString(); //Returns the current word as a string (instead of tile vector)

    void updatePos(); //Updates position of the tiles

    int getSize(); //Returns the size of the word

    int getDmg(); //Returns the damage of the word

    void clearWord(); //Clears the word, returning the tiles back to the tile bank

    //Temp *
    void printWord(); //Prints word to console


  protected:
    std::vector<tile*> currentWord; //The word itself- a vector of tile pointers

    double damage; //The current damage of the word

};
#endif
