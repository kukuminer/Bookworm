#include "button.h"
#include "audio.h"

sf::Texture button::buttonSheet;

button::button(buttonType in)
{
    type = in;
    switch(type)
    {
    case buttonType::attack:
        constructAttack();
        break;
    case buttonType::scramble:
        constructScramble();
        break;
    case buttonType::play:
        constructPlay();
        break;
    case buttonType::help:
        constructHelp();
        break;
    case buttonType::gomenu:
        constructGoMenu();
        break;
    case buttonType::mutemusic:
        constructMmusic();
        break;
    case buttonType::mutesound:
        constructMsound();
        break;
    case buttonType::quit:
        constructQuit();
        break;
    }
}

button::~button()
{
    //dtor
}

void button::click()
{
    if(!character::isPlayerTurn && game::currentState == adventure)
    {
        return;
    }
    util::buttonSound.play();
    switch(type)
    {
    case buttonType::attack:
        attack();
        break;
    case buttonType::scramble:
        util::scrambleSound.play();
        scramble();
        break;
    case buttonType::play:
        play();
        break;
    case buttonType::help:
        help();
        break;
    case buttonType::gomenu:
        gomenu();
        break;
    case buttonType::mutemusic:
        mutemusic();
        break;
    case buttonType::mutesound:
        mutesound();
        break;
    case buttonType::quit:
        quit();
        break;
    }
}

void button::loadbuttonSheet()
{
    if(!button::buttonSheet.loadFromFile("sprites\\buttons.png"))
    {
        std::cout << "ERROR LOADING BUTTONSHEET\n";
    }
}

/**Attack stuff*/
void button::attack()
{
    if(util::activeWord.check())
    {
        util::attackSound.play();
        util::player.attack(util::enemy, util::activeWord.getDmg());

        util::bank.popWord();
    }
}

void button::constructAttack()
{
    int w = 320;
    int h = 70;
    obj.setSize(sf::Vector2f(w, h));
    obj.setTexture(&buttonSheet);
    obj.setTextureRect(sf::Rect<int>(0, 0, 320, 80));
    obj.setPosition(util::WINDOWWIDTH/2 - w/2, 8*util::WINDOWHEIGHT/9);
    util::gameObjects.push_back(this);
}

bool button::intersects(sf::RenderWindow &win)
{
    if(type == buttonType::attack)
    {
        if(util::activeWord.check())
        {
            return object::intersects(win);
        }
        else
        {
            obj.setFillColor(sf::Color(50,50,50,255));
        }
    }
    else
    {
        return object::intersects(win);
    }
}



/**Scramble stuff*/
void button::scramble()
{
    util::bank.scrambleLetters();
    character::switchTurn();
}

void button::constructScramble()
{
    int w = 200;
    int h = 40;
    obj.setSize(sf::Vector2f(w, h));
    obj.setTexture(&buttonSheet);
    obj.setTextureRect(sf::Rect<int>(0,80,320,80));
    obj.setPosition(util::WINDOWWIDTH/8, 9*util::WINDOWHEIGHT/10);
    util::gameObjects.push_back(this);
}


/**Play stuff*/
void button::play()
{
    game::updateState(adventure);
}

void button::constructPlay()
{
    using namespace sf;
    int w = 400;
    int h = 100;
    obj.setSize(Vector2f(w, h));
    obj.setTexture(&buttonSheet);
    obj.setTextureRect(sf::Rect<int>(0,240,320,80));
    obj.setPosition(Vector2f(util::WINDOWWIDTH/2 - w/2, util::WINDOWHEIGHT/2 - h));
    util::menuObjects.push_back(this);
}



/**Help stuff*/
void button::help()
{
    game::updateState(howto);
}

void button::constructHelp()
{
    using namespace sf;
    int w = 300;
    int h = 80;
    obj.setSize(Vector2f(w, h));
    obj.setTexture(&buttonSheet);
    obj.setTextureRect(sf::Rect<int>(0,320,320,80));
    obj.setPosition(Vector2f(util::WINDOWWIDTH/2 - w/2, 2*util::WINDOWHEIGHT/3-h));
    util::menuObjects.push_back(this);

}

/**Go Menu stuff*/

void button::gomenu()
{
    if(util::player.getHP() <= 0)
    {
        game::reset();
    }
    game::updateState(menu);
}

void button::constructGoMenu()
{
    using namespace sf;
    int w = 200;
    int h = 40;
    obj.setSize(Vector2f(w, h));
    obj.setTexture(&buttonSheet);
    obj.setTextureRect(sf::Rect<int>(0,160,320,80));
    obj.setPosition(Vector2f(7*util::WINDOWWIDTH/8 - w, 9*util::WINDOWHEIGHT/10));
    util::gameObjects.push_back(this);
    util::loseObjects.push_back(this);
    util::helpObjects.push_back(this);
}

/**Mute stuff*/
void button::mutemusic()
{
    using namespace sf;
    audio::musicMuted = !audio::musicMuted;
    audio::updateMutes();
    if(audio::musicMuted)
    {
        obj.setTextureRect(Rect<int>(240, 400, 80, 80));
    }
    else
    {
        obj.setTextureRect(Rect<int>(160, 400, 80, 80));
    }
}

void button::mutesound()
{
    using namespace sf;
    audio::soundMuted = !audio::soundMuted;
    audio::updateMutes();
    if(audio::soundMuted)
    {
        obj.setTextureRect(Rect<int>(0, 400, 80, 80));
    }
    else
    {
        obj.setTextureRect(Rect<int>(80, 400, 80, 80));
    }

}

void button::constructMmusic()
{
    using namespace sf;
    int w = 50;
    int h = 50;
    obj.setSize(Vector2f(w, h));
    obj.setTexture(&buttonSheet);
    obj.setTextureRect(Rect<int>(160, 400, 80, 80));
    obj.setPosition(Vector2f(util::WINDOWWIDTH/2 + 50, 5*util::WINDOWHEIGHT/6-h));
    util::menuObjects.push_back(this);
}

void button::constructMsound()
{
    using namespace sf;
    int w = 50;
    int h = 50;
    obj.setSize(Vector2f(w, h));
    obj.setTexture(&buttonSheet);
    obj.setTextureRect(Rect<int>(80, 400, 80, 80));
    obj.setPosition(Vector2f(util::WINDOWWIDTH/2 - 50 - w, 5*util::WINDOWHEIGHT/6-h));
    util::menuObjects.push_back(this);
}

/**Quit stuff*/
void button::quit()
{
    exit(0);
}

void button::constructQuit()
{
    using namespace sf;
    int w = 200;
    int h = 60;
    obj.setSize(sf::Vector2f(w, h));
    obj.setTexture(&buttonSheet);
    obj.setTextureRect(sf::Rect<int>(0,480,320,80));
    obj.setPosition(util::WINDOWWIDTH/2-w/2, 9*util::WINDOWHEIGHT/10);
    util::menuObjects.push_back(this);
}
