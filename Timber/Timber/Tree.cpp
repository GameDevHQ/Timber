#include "stdafx.h"
#include "Tree.h"


Tree::Tree(float positionX, float positionY): Object("Resources/Graphics/tree.png")
{
    objectTexture.loadFromFile(pathToTexture);

    objectSprite.setTexture(objectTexture);
    objectSprite.setPosition(positionX, positionY);
}


void Tree::update(RenderWindow& window, Time timedelta)
{
}


void Tree::draw(RenderWindow& window)
{
    window.draw(objectSprite);
}
