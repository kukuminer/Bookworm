#include "tile.h"
#include "utility.hpp"
#include "tilebank.h"
#include "audio.h"


using namespace std;
using namespace sf;

sf::Texture tile::tileSheet;
sf::Font tile::cour;


tile::tile(tilebank* par)
{
    parent = par;
    taken = 0;
    obj.setSize(sf::Vector2f(80,80));
    obj.setTexture(&tileSheet);
    display.setFont(cour);
    renewLetter();
    display.setFillColor(Color(0,0,0,255));
    display.setCharacterSize(50);
    util::gameObjects.push_back(this);
}

//tile::tile(char in)
//{
//    tile();
//    letter = in;
//}

void tile::genRandLetter()
{
    using namespace util;
    int token = rand() % 98; //Token will determine the letter
    int p = 0; //p is the rarity range for each letter (ie letter 'A' has range 0-8)

    for(int a = 1; a <= 26; a++)
    {
        if(token >= p && token < p + rarities[a])
        {
            letter = a+'@';
            value = letterVals[a-1] + 1; //-1 because a starts at 1 but the array starts at 0
            //^ +1 so no 0 values

            if(parent->letterCount[a] >= 4) //This limits the number of each letter to 4
            {
                genRandLetter();
            }
            else
            {
                parent->letterCount[a]++;
            }

            return;
        }
        p += rarities[a];
    }

}

char tile::getLetter()
{
    return letter;
}

void tile::renewLetter()
{
    taken = false;
    parent->letterCount[letter-'@']--;
    genRandLetter();
    obj.setTextureRect(Rect<int>((value-1)*80, 0, 80, 80));
    if(isQ())
    {
        string s;
        s.push_back(letter);
        s.push_back('U');
        display.setString(s);
        value = 4;
    }
    else
    {
        display.setString(letter);
    }
}

void tile::click()
{
    if(!taken)
    {
        util::clickSound.play();
        util::activeWord.addLetter(this);
        position = util::activeWord.getSize() - 1;
//        cout << "Added " << letter << " to word with position " << position << '\n';
        take();
    }
    else
    {
//        cout << "calling popletter on position " << position << '\n';
        util::activeWord.popLetter(position);
    }

    if(util::activeWord.check())
    {
        util::wordPower.snd.setPitch(1.0 + util::activeWord.getDmg()/30.0);
        util::wordPower.play();
        cout << util::activeWord.getDmg() << '\n';
    }
    util::activeWord.updatePos();
}

void tile::take()
{
    taken = !taken;
}

bool tile::isTaken()
{
    return taken;
}

void tile::draw(RenderWindow &win)
{
    win.draw(obj);
    win.draw(display);
}

void tile::setPosition(int x, int y)
{
    obj.setPosition(x, y);
    if(isQ())
    {
        display.setPosition(x+util::TILEDIMS/3 - 18, y);
    }
    else
    {
        display.setPosition(x+util::TILEDIMS/3 - 3, y);
    }
}

bool tile::isQ()
{
    return letter == 'Q';
}

int tile::getVal()
{
    return value;
}

void tile::loadtileSheet()
{
    if(!tile::tileSheet.loadFromFile("sprites\\tilesheet.png"))
    {
        cout << "ERROR LOADING TILESHEET\n";
    }
}

void tile::loadFont()
{
    if(!cour.loadFromFile("files\\cour.ttf"))
    {
        cout << "ERROR LOADING FONT COUR\n";
    }
}

tile::~tile()
{

}
