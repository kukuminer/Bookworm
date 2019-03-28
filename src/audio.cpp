#include "audio.h"
#include "utility.hpp"
using namespace sf;
using namespace std;

bool audio::musicMuted = 0;
bool audio::soundMuted = 0;

audio::audio(bool isMusic, string file, bool loop)
{
    isSound = !isMusic;
    if(isMusic)
    {
        if(!msc.openFromFile("audio\\" + file))
        {
            cout << "ERROR LOADING " << file << '\n';
        }
        msc.setLoop(loop);
        util::gameMusics.push_back(&msc);
    }
    else
    {
        if(!buf.loadFromFile("audio\\" + file))
        {
            cout << "ERROR LOADING " << file << '\n';
        }
        snd.setBuffer(buf);
        snd.setLoop(loop);
        util::gameSounds.push_back(&snd);
    }
}

void audio::play()
{
    if(isSound)
    {
        snd.play();
    }
    else
    {
        msc.play();
    }
}

void audio::stop()
{
    snd.stop();
    msc.stop();
}

SoundSource::Status audio::getStatus()
{
    if(isSound)
    {
        return snd.getStatus();
    }
    else
    {
        return msc.getStatus();
    }
}


audio::~audio()
{

}

void audio::updateMutes()
{
    using namespace std;
    for(int a = 0; a < util::gameMusics.size(); a++)
    {
        if(musicMuted)
        {
//          std::cout << "muting music " << a << '\n';
            util::gameMusics[a]->setVolume(0);
        }
        else
        {
            util::gameMusics[a]->setVolume(100);
        }
    }
    for(int a = 0; a < util::gameSounds.size(); a++)
    {
        if(soundMuted)
        {
            util::gameSounds[a]->setVolume(0);
        }
        else
        {
            util::gameSounds[a]->setVolume(100);
        }
    }

}

