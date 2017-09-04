#pragma once
#include "Object.h"
#include "Util.h"


// Line the axe up with the tree
const float AXE_POSITION_LEFT = 700;
const float AXE_POSITION_RIGHT = 1075;


class Player: public Object
{
private:
    side playerSide;

    Texture textureAxe;
    Sprite spriteAxe;

    Texture textureRIP;
    Sprite spriteRIP;
public:
    Player();

    void moveRight();
    void moveLeft();
    side getPlayerSide() const;

    void hidePlayer();
    void hideAxe();

    void hideGravestone();
    void showGravestone();

    virtual void update(RenderWindow& window, Time timedelta) override;
    virtual void draw(RenderWindow& window) override;
};
