#pragma once
#include "Object.h"


class Tree : public Object
{
public:
	Tree(float positionX, float positionY);

	virtual void Update(RenderWindow& window, Time timedelta) override;
	virtual void Draw(RenderWindow& window) override;
};
