#include "stdafx.h"
#include "Bee.h"


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
}


void Bee::Draw(RenderWindow& window)
{
	window.draw(objectSprite);
}
