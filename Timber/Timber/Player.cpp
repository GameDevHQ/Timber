#include "stdafx.h"
#include "Player.h"


Player::Player() : Object("Resources/Graphics/player.png")
{
    // The player starts on the left
    side playerSide = side::LEFT;

    // Prepare the player sprite
    objectTexture.loadFromFile(pathToTexture);
    
    objectSprite.setTexture(objectTexture);
    objectSprite.setPosition(580, 720);

    // Prepare the gravestone
    textureRIP.loadFromFile("Resources/Graphics/rip.png");
    
    spriteRIP.setTexture(textureRIP);
    spriteRIP.setPosition(600, 860);

    // Prepare the axe
    textureAxe.loadFromFile("Resources/Graphics/axe.png");

    spriteAxe.setTexture(textureAxe);
    spriteAxe.setPosition(700, 830);
}


void Player::moveRight()
{
    playerSide = side::RIGHT;
    objectSprite.setPosition(1200, 720);
    spriteAxe.setPosition(AXE_POSITION_RIGHT, spriteAxe.getPosition().y);
}


void Player::moveLeft()
{
    playerSide = side::LEFT;
    objectSprite.setPosition(580, 720);
    spriteAxe.setPosition(AXE_POSITION_LEFT, spriteAxe.getPosition().y);
}


side Player::getPlayerSide() const
{
    return playerSide;
}



void Player::hidePlayer()
{
    objectSprite.setPosition(2000, 660);
}



void Player::hideAxe()
{
    spriteAxe.setPosition(2000, spriteAxe.getPosition().y);
}


void Player::hideGravestone()
{
    spriteRIP.setPosition(675, 2000);
}


void Player::showGravestone()
{
    spriteRIP.setPosition(525, 760);
}


void Player::update(RenderWindow & window, Time timedelta)
{
}


void Player::draw(RenderWindow & window)
{
    window.draw(objectSprite);
    window.draw(spriteAxe);
    window.draw(spriteRIP);
}
