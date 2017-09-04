#pragma once
#include "Object.h"


class Cloud : public Object
{
private:
    bool isActive;
    float speed;
    float startPositionY;
    int movementScale;
public:
    Cloud(float positionX, float positionY, Texture& texture, int movementScale);

    virtual void update(RenderWindow& window, Time timedelta) override;
    virtual void draw(RenderWindow& window) override;
};
