#pragma once
#include "Object.h"


class Log : public Object
{
private:
    bool logActive;
    float logSpeedX;
    float logSpeedY;
public:
    Log();

    void setIsFlyingRight();
    void setIsFlyingLeft();

    virtual void update(RenderWindow& window, Time timedelta) override;
    virtual void draw(RenderWindow& window) override;
};
