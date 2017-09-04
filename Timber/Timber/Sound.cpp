#include "stdafx.h"
#include "Sound.h"
#include <vector>
#include <sstream>

SoundManager::SoundManager()
{
    std::vector<std::string> soundNames = { "chop", "death", "out_of_time" };

    for (auto soundName : soundNames)
    {
        SoundBuffer* soundBuffer = new SoundBuffer();
        soundBuffer->loadFromFile("Resources/Sound/" + soundName + ".wav");
        Sound* sound = new Sound();
        sound->setBuffer(*soundBuffer);

        soundBuffers[soundName] = soundBuffer;
        sounds[soundName] = sound;
    }
}


SoundManager& SoundManager:: getInstance()
{
    static SoundManager* instance = new SoundManager();
    return *instance;
}


void SoundManager::play(std::string soundName)
{
    std::map<std::string, Sound*>::iterator it = sounds.find(soundName);
    if (it != sounds.end())
    {
        it->second->play();
    }
}
