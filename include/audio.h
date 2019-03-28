#ifndef AUDIO_H
#define AUDIO_H
#include <SFML/Audio.hpp>
#include <bits/stdc++.h>

class audio
{
    public:
        audio(bool isMusic, std::string file, bool loop);
        virtual ~audio();

        void play(); //Plays the audio clip
        void stop(); //Stops the audio clip
        sf::SoundSource::Status getStatus(); //Returns status enum (Playing, Paused, Stopped)

        static const int numSongs = 3; //Number of songs available
        static const int numAttackSounds = 2; //Number of attack sounds available
        static bool musicMuted; //If the game music is muted
        static bool soundMuted; //If the game sounds are muted
        static void updateMutes(); //Adjusts volume in line with the above mute bools

        sf::Sound snd; //Public so that other classes may modify it's pitch, speed, etc
        sf::Music msc; //All audio files contain both a sound and a music, but only load 1 (depending on isMusic from the constructor)
    protected:
        sf::SoundBuffer buf; //SoundBuffer for sounds
        bool isSound; //If this audio is a sound or music (so it knows whether to use snd or msc fields

    private:
};

#endif // AUDIO_H
