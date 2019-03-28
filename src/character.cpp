#include "character.h"
#include "background.h"

using namespace sf;
using namespace std;

bool character::isPlayerTurn = 1;
int character::killCount = 0;
Clock character::animTimer;
Texture character::charSheet;
Texture character::monsters[numPictures];

character::character(bool isP, int hp)
{
    isPlayer = isP;
    maxHPrect.setSize(Vector2f(HPwidth, HPheight));
    maxHPrect.setFillColor(Color(200,0,0,255));
    maxHPrect.setOutlineColor(Color(255, 255, 255, 255));
    maxHPrect.setOutlineThickness(1);
    curHPrect.setSize(Vector2f(HPwidth, HPheight));
    curHPrect.setFillColor(Color(0,200,0,255));
    obj.setSize(Vector2f(150, 225));
    obj.setOrigin(0, obj.getLocalBounds().height);
    if(isP)
    {
        maxHP = hp;
        obj.setTexture(&charSheet);
        obj.setTextureRect(Rect<int>(0,0,201,311)); //Dims are the width/height of the sprite
        obj.setPosition(util::WINDOWWIDTH/10, util::WINDOWHEIGHT/7 + obj.getLocalBounds().height);
        curHPrect.setPosition(util::WINDOWWIDTH/10, util::WINDOWHEIGHT/12);
        maxHPrect.setPosition(util::WINDOWWIDTH/10, util::WINDOWHEIGHT/12);
    }
    else
    {
        obj.setPosition(9*util::WINDOWWIDTH/10 - obj.getLocalBounds().width, util::WINDOWHEIGHT/6 + obj.getLocalBounds().height);
        obj.setTextureRect(Rect<int>(0, 0, 500, 700));
        curHPrect.setPosition(9*util::WINDOWWIDTH/10 - HPwidth, util::WINDOWHEIGHT/12);
        maxHPrect.setPosition(9*util::WINDOWWIDTH/10 - HPwidth, util::WINDOWHEIGHT/12);
    }
    renewChar();
    intersectable = false;
    active = false;
    util::gameObjects.push_back(this);
}

void character::attack(character &opp, int dmg)
{
//    std::cout << "attack enemy for " << dmg << "!\n";
    opp.curHP = std::max(opp.curHP - dmg, 0);
    if(!opp.isPlayer && opp.curHP <= 0)
    {
        killEnemy();
        if(killCount % 3 == 0)
        {
            curHP = maxHP;
        }
        updateHP();
    }
    else if(opp.isPlayer && opp.curHP <= 0)
    {
        killPlayer();
    }
    opp.obj.setFillColor(Color(255, 50, 50, 255));
    opp.updateHP();
    switchTurn();
}

void character::updateHP()
{
    curHPrect.setSize(Vector2f(HPwidth*curHP/maxHP, HPheight));
}

void character::killEnemy()
{
    killCount++;
    util::gamebg.tex.setString("Kills: " + patch::to_string(killCount));
    switchTurn();
}

void character::renewChar()
{
    if(!isPlayer)
    {
        int t = rand();
        t %= numPictures;
        obj.setTexture(&monsters[t]);
        //obj.setTextureRect(Rect<int>(0, 0, character::picDims[t][0], character::picDims[t][1])); //Grabs the dimensions of the sprite that was chosen
        maxHP = (killCount/3+1)*5+5;
//        std::cout << "new enemy has " << maxHP << " HP!\n";
    }
    curHP = maxHP;
    updateHP();
}

void character::killPlayer()
{
    game::updateState(lose);
}

void character::dmgAnimation()
{
    if(animTimer.getElapsedTime().asMilliseconds() > 500)
    {
        obj.setFillColor(Color(255, 255, 255, 255));
        if(curHP <= 0 && !isPlayer)
        {
            renewChar();
        }
    }
}

void character::updateAnim()
{
    //obj.setTextureRect(Rect<int>(201*(gifClock.getElapsedTime().asMilliseconds()/200 % 6), 0, 201, 311));
    obj.setScale(Vector2f(1, 0.07*std::abs(sin((1.0*maxHP/curHP)*gifClock.getElapsedTime().asSeconds())) + 0.93));
}

void character::switchTurn()
{
    isPlayerTurn = !isPlayerTurn;
    animTimer.restart();
}

void character::draw(RenderWindow &win)
{
//    if(isPlayer)
    {
        updateAnim();
    }


    dmgAnimation();
    win.draw(maxHPrect);
    win.draw(curHPrect);
    win.draw(obj);
}

void character::loadCharSheet()
{
    if(!charSheet.loadFromFile("sprites\\lex.png"))
    {
        std::cout << "ERROR LOADING CHARSHEET\n";
    }
}

void character::loadMonsters()
{
    for(int a = 0; a < numPictures; a++)
    {
        char s = a + 48;
//        cout << s << '\n';
        //string ss = "sprites\\monsters\\monster" + s + ".png";
        string ss = "sprites\\monsters\\monster";
        ss += s;
        ss += ".png";
//        cout << ss << '\n';
        if(!monsters[a].loadFromFile(ss))
        {
            std::cout << "ERROR LOADING MONSTER " << a << '\n';
        }
    }
}

int character::getHP()
{
    return curHP;
}

character::~character()
{
    //dtor
}
