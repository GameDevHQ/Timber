#include "stdafx.h"
#include "Background.h"


Background::Background(): Object("Resources/Graphics/background.png")
{
    objectTexture.loadFromFile(pathToTexture);

    objectSprite.setTexture(objectTexture);
    objectSprite.setPosition(0, 0);
}


void Background::update(RenderWindow& window, Time timedelta)
{
}


void Background::draw(RenderWindow& window)
{
    window.draw(objectSprite);
}
