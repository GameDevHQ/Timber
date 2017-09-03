#pragma once
#include "Object.h"


class Bee : public Object
{
private:
	bool isActive;
	float speed;
public:
	Bee(float positionX, float positionY);

	virtual void Update(RenderWindow& window, Time timedelta) override;
	virtual void Draw(RenderWindow& window) override;
};
