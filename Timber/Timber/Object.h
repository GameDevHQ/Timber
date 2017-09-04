#pragma once


class Object
{
protected:
    Texture objectTexture;
    Sprite objectSprite;
    std::string pathToTexture;
public:	
    Object();
    Object(std::string pathToTexture);
    virtual ~Object() = default;

    virtual void update(RenderWindow& window, Time timedelta) = 0;
    virtual void draw(RenderWindow& window) = 0;
};
