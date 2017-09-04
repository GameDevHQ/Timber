#include "stdafx.h"
#include "Log.h"


Log::Log(): 
Object("Resources/Graphics/log.png"),
logActive(false),
logSpeedX(1000),
logSpeedY(-1500)
{
    objectTexture.loadFromFile(pathToTexture);

    objectSprite.setTexture(objectTexture);
    objectSprite.setPosition(810, 720);

    // Some other useful log related variables
    bool logActive = false;
    float logSpeedX = 1000;
    float logSpeedY = -1500;
}


void Log::setIsFlyingRight()
{
    objectSprite.setPosition(810, 720);
    logSpeedX = -5000;
    logActive = true;
}


void Log::setIsFlyingLeft()
{
    objectSprite.setPosition(810, 720);
    logSpeedX = 5000;
    logActive = true;
}


void Log::update(RenderWindow & window, Time timedelta)
{
    if (logActive)
    {
        float newPositionX = objectSprite.getPosition().x + (logSpeedX * timedelta.asSeconds());
        float newPositionY = objectSprite.getPosition().y + (logSpeedY * timedelta.asSeconds());
        objectSprite.setPosition(newPositionX, newPositionY);

        // Has the log reached the right hand edge?
        if (objectSprite.getPosition().x < -100 || objectSprite.getPosition().x > 2000)
        {
            // Set it up ready to be a whole new log next frame
            logActive = false;
            objectSprite.setPosition(810, 720);
        }
    }
}


void Log::draw(RenderWindow & window)
{
    window.draw(objectSprite);
}

