#pragma once
#include "Object.h"


class Tree : public Object
{
public:
    Tree(float positionX, float positionY);

    virtual void update(RenderWindow& window, Time timedelta) override;
    virtual void draw(RenderWindow& window) override;
};
