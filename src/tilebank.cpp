#include "tilebank.h"
#include "utility.hpp"


tilebank::tilebank()
{
    srand(time(NULL));
    util::setRarities();
    util::readLetterValues();
    int cnt = 0;
    for(int a = 0; a < BANKSIZE; a++)
    {
        bank[a] = new tile(this);
    }
    updatePos();
//    for(int a = 0; a < BANKSIZE/4; a++)
//    {
//        for(int b = 0; b < BANKSIZE/4; b++)
//        {
//            bank[cnt] = new tile();
//            bank[cnt]->setPosition
//            ((util::WINDOWWIDTH/2-2*util::TILEDIMS) + util::TILEDIMS*b,
//            (util::WINDOWHEIGHT/2+util::TILEDIMS*a - 20));
//            cnt++;
//        }
//    }
}

bool tilebank::has(char in)
{
    for(int a = 0; a < BANKSIZE; a++)
    {
        if(bank[a]->getLetter() == in)
        {
            return 1;
        }
    }
    return 0;
}

void tilebank::popWord()
{
    for(int a = 0; a < BANKSIZE; a++)
    {
        if(bank[a]->isTaken())
        {
            bank[a]->renewLetter();
            util::activeWord.clearWord();
            updatePos();
        }
    }
}

void tilebank::updatePos()
{
    int cnt = 0;
    for(int a = 0; a < BANKSIZE/4; a++)
    {
        for(int b = 0; b < BANKSIZE/4; b++)
        {
            if(!bank[cnt]->isTaken())
            {
                bank[cnt]->setPosition
                ((util::WINDOWWIDTH/2-2*util::TILEDIMS) + util::TILEDIMS*b,
                (util::WINDOWHEIGHT/2+util::TILEDIMS*a - 20));
            }
            cnt++;
        }
    }

}

void tilebank::scrambleLetters()
{
//    if(util::player.getHP() > 0)
//    {
//        util::scrambleSound.play();
//    }
    util::activeWord.popLetter(0);
    for(int a = 0; a < BANKSIZE; a++)
    {
        bank[a]->renewLetter();
    }
    util::activeWord.updatePos();
}

tile* tilebank::getTile(int a)
{
    return bank[a];
}

tilebank::~tilebank()
{
    //dtor
}
