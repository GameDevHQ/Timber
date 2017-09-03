#include "stdafx.h"
#include "Background.h"


Background::Background(): Object("Resources/Graphics/background.png")
{
    objectTexture.loadFromFile(pathToTexture);

    objectSprite.setTexture(objectTexture);
    objectSprite.setPosition(0, 0);
}


void Background::Update(RenderWindow& window, Time timedelta)
{
}


void Background::Draw(RenderWindow& window)
{
    window.draw(objectSprite);
}
