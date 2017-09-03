#include "stdafx.h"
#include "Cloud.h"


Cloud::Cloud(float positionX, float positionY, Texture& texture):
Object(),
isActive(false),
speed(0.0f)
{
	objectTexture = texture;

	objectSprite.setTexture(objectTexture);
	objectSprite.setPosition(positionX, positionY);
}


void Cloud::Update(RenderWindow& window, Time timedelta)
{
}


void Cloud::Draw(RenderWindow& window)
{
	window.draw(objectSprite);
}
