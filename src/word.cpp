#include "word.h"
#include "utility.hpp"
using namespace std;

word::word()
{
    //ctor
}

word::~word()
{
    //dtor
}

void word::addLetter(tile *in)
{
    currentWord.push_back(in);
    damage += in->getVal();
}

void word::popLetter(int pos)
{
    int s = currentWord.size();
    for(int a = pos; a < s; a++)
    {
        currentWord.back()->take();
        damage -= currentWord.back()->getVal();
        currentWord.pop_back();
    }
}

bool word::check()
{
    string s = getString();
    if(s.size() < 3) return 0; //Words must be at least 3 letters long
    int l = 0, r = util::wordlist.size()-1;

    while(l <= r) //Binary search!
    { //Loop until left and right bounds are on the same spot (nowhere left to search)
        int mid = (r+l)/2; //Middle of the bounds
        string cur = util::wordlist[mid];

        if(cur == s) return 1; //Found the word
        else if(s < cur) r = mid - 1; //Word is less, shift right bound left
        else l = mid + 1; //Word is greater, shift left bound right
    }
    return 0;


//    for(int a = 0; a < util::wordlist.size(); a++) //Checks the word through the dictionary
//    {
//        if(s == util::wordlist[a]) return 1;
//    }
//    return 0;
}

string word::getString() //Returns the word as a string
{
    string s;
    for(int a = 0; a < currentWord.size(); a++)
    {
        s += currentWord[a]->getLetter();
        if(currentWord[a]->isQ())
        {
            s += 'U';
        }
    }
    return s;
}

void word::updatePos()
{
    const int y = util::WINDOWHEIGHT/3;
    int s = currentWord.size();
    for(int a = 0; a < s; a++)
    {
        currentWord[a]->setPosition
        (util::WINDOWWIDTH/2 - s*util::TILEDIMS/2 + a*util::TILEDIMS,
         y);
    }
    util::bank.updatePos();
}

int word::getSize()
{
    return currentWord.size();
}

int word::getDmg()
{
    double dmg = damage * (currentWord.size()/10.0 + 1);
    return dmg;
}

void word::clearWord()
{
    for(int a = 0; a < currentWord.size(); a++)
    {
        currentWord.pop_back();
    }
    damage = 0;
}

/**TEMP*/
void word::printWord()
{
    cout << getString() << '\n';
}

