#include "stdafx.h"
#include "Cloud.h"


Cloud::Cloud(float positionX, float positionY, Texture& texture, int movementScale):
Object(),
isActive(false),
speed(0.0f),
startPositionY(positionY),
movementScale(movementScale)
{
    objectTexture = std::move(texture);

    objectSprite.setTexture(objectTexture);
    objectSprite.setPosition(positionX, positionY);
}


void Cloud::Update(RenderWindow& window, Time timedelta)
{
    if (!isActive)
    {
        // How fast is the cloud
        srand(static_cast<int>(time(0) * movementScale));
        speed = (rand() % 200);

        // How high is the cloud
        srand(static_cast<int>(time(0) * movementScale));
        float height = (rand() % (150 + static_cast<int>(startPositionY))) - startPositionY;
        objectSprite.setPosition(-200, height);
        isActive = true;
    }
    else
    {
        float newPositionX = objectSprite.getPosition().x + (speed * timedelta.asSeconds());
        objectSprite.setPosition(newPositionX, objectSprite.getPosition().y);

        // Has the cloud reached the right hand edge of the screen?
        if (objectSprite.getPosition().x > WINDOW_WIDTH)
        {
            // Set it up ready to be a whole new cloud next frame
            isActive = false;
        }
    }
}


void Cloud::Draw(RenderWindow& window)
{
    window.draw(objectSprite);
}
