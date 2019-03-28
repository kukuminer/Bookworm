#ifndef _TILEBANK_H
#define _TILEBANK_H


class tile;

class tilebank {
  public:
    tilebank();

    bool has(char in); //If the bank has a tile with this letter

    void popWord(); //Destroys (and renews) all the letters that are part of the current word

    tile* getTile(int a); //Returns a pointer to a tile in the bank

    void updatePos(); //Updates position of the tiles in the bank (for animation)

    void scrambleLetters(); //Scrambles all the tiles to new ones

    int letterCount[26]; //An array that keeps track of how many of each letter are in the bank.

    virtual ~tilebank();

    static const int BANKSIZE=  16; //The default size of the tile bank


  protected:
    tile* bank[BANKSIZE]; //The actual tile bank itself. Array of pointers to tiles

};
#endif
