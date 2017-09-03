#pragma once
#include "Object.h"


class Background : public Object
{
public:
    Background();

    virtual void Update(RenderWindow& window, Time timedelta) override;
    virtual void Draw(RenderWindow& window) override;
};
