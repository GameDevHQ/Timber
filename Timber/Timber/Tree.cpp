#include "stdafx.h"
#include "Tree.h"


Tree::Tree(float positionX, float positionY): Object("Resources/Graphics/tree.png")
{
    objectTexture.loadFromFile(pathToTexture);

    objectSprite.setTexture(objectTexture);
    objectSprite.setPosition(positionX, positionY);
}


void Tree::Update(RenderWindow& window, Time timedelta)
{
}


void Tree::Draw(RenderWindow& window)
{
    window.draw(objectSprite);
}
