#include "utility.hpp"
#include "button.h"
#include "character.h"
#include "background.h"

using namespace std;
using namespace sf;

int util::rarities[26];
std::vector<std::string> util::wordlist;
int util::letterVals[26];
int util::WINDOWHEIGHT = 800;
int util::WINDOWWIDTH = 1280;
int util::TILEDIMS = 80;
Clock util::fps;

word util::activeWord;


/**gameObjects*/
vector<object*> util::gameObjects;
tilebank util::bank;
button util::attackButton(attack);
button util::scrambleButton(scramble);
character util::player(1, 20);
character util::enemy(0, 5);
background util::gamebg(adventure);

/**menuObjects*/
vector<object*> util::menuObjects;
background util::menubg(menu);
button util::helpButton(help);
button util::playButton(play);
button util::muteMbutton(mutemusic);
button util::muteSbutton(mutesound);
button util::quitButton(quit);

/**howToObjects*/
vector<object*> util::helpObjects;
background util::helpbg(howto);

/**loseObjects*/
vector<object*> util::loseObjects;
background util::losebg(lose);
button util::menuButton(gomenu);


///**Audio*/

//**Sounds:
vector<Sound*> util::gameSounds;
audio util::clickSound(0, "tile_select.ogg", 0);
audio util::attackSound(0, "attack.wav", 0);
audio util::deathSound(0, "death.wav", 0);
audio util::scrambleSound(0, "scramble.ogg", 0);
audio util::buttonSound(0, "click.ogg", 0);
audio util::wordPower(0, "word_power.ogg", 0);
audio util::enemyAttack[audio::numAttackSounds] = {
{0, "enemy_attack0.ogg", 0},
{0, "enemy_attack1.ogg", 0}
};

//**Music:
vector<Music*> util::gameMusics;
audio util::menuMusic(1, "mainMenu.wav", 1);
audio util::advMusic[audio::numSongs] = {
{1, "music0.wav", 0},
{1, "music1.wav", 0},
{1, "music2.wav", 0}
};



void util::setRarities()
{
//    cout << "READING RARITIES\n";
    ifstream read;
    read.open("rarity.txt");
    int cnt = 0;
    while(!read.eof() && read.is_open())
    {
        read >> rarities[cnt];
        cnt++;
    }
    read.close();
}

void util::readWords()
{
    ifstream read;
    read.open("words.txt");
    while(!read.eof() && read.is_open())
    {
        string s;
        read >> s;
        wordlist.push_back(s);
        //cout << wordlist[cnt] << '\n';
    }
    read.close();
//    cout << "Done reading!\n";
}

void util::readLetterValues()
{
    ifstream read;
    read.open("values.txt");
    int cnt = 0;
    while(!read.eof() && read.is_open())
    {
        read >> letterVals[cnt];
        cnt++;
    }
    read.close();
}


void util::frameLimit(int target)
{
    while(util::fps.getElapsedTime().asMilliseconds() < 1000/target)
    {
        sleep(milliseconds(0.5));
    }
    fps.restart();
}
