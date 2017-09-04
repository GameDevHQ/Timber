#pragma once
#include <map>
#include "SFML/Audio.hpp"

using namespace sf;


class SoundManager
{
private:
    std::map<std::string, SoundBuffer*> soundBuffers;
    std::map<std::string, Sound*> sounds;
public:
    SoundManager& getInstance();
    void play(std::string soundName);
private:
    SoundManager();
};
