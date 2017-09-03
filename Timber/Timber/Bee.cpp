#include "stdafx.h"
#include "Bee.h"
#include <time.h>


Bee::Bee(float positionX, float positionY): 
Object("Resources/Graphics/bee.png"),
isActive(false),
speed(0.0f)
{
    objectTexture.loadFromFile(pathToTexture);

    objectSprite.setTexture(objectTexture);
    objectSprite.setPosition(positionX, positionY);
}


void Bee::Update(RenderWindow& window, Time timedelta)
{
    if (!isActive)
    {
        // How fast is the bee
        srand((int)time(NULL) * 10);
        speed = (rand() % 200) + 200;

        // How high is the bee
        srand((int)time(NULL) * 10);
        float startPositionX = WINDOW_WIDTH + objectTexture.getSize().x;
        float startPositionY = (rand() % 500) + 500;
        objectSprite.setPosition(startPositionX, startPositionY);
        isActive = true;
    }
    // Move the bee
    else 
    {
        float newPositionX = objectSprite.getPosition().x - (speed * timedelta.asSeconds());
        objectSprite.setPosition(newPositionX, objectSprite.getPosition().y);

        // Has the bee reached the right hand edge of the screen?
        if (objectSprite.getPosition().x < -100)
        {
            // Set it up ready to be a whole new cloud next frame
            isActive = false;
        }
    }
}


void Bee::Draw(RenderWindow& window)
{
    window.draw(objectSprite);
}
