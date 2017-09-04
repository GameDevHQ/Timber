#pragma once
#include "Object.h"


class Bee: public Object
{
private:
    bool isActive;
    float speed;
public:
    Bee(float positionX, float positionY);

    virtual void update(RenderWindow& window, Time timedelta) override;
    virtual void draw(RenderWindow& window) override;
};
