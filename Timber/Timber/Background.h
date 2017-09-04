#pragma once
#include "Object.h"


class Background : public Object
{
public:
    Background();

    virtual void update(RenderWindow& window, Time timedelta) override;
    virtual void draw(RenderWindow& window) override;
};
