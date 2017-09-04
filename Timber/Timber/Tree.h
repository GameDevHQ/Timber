#pragma once
#include "Object.h"
#include "Util.h"

const int NUM_BRANCHES = 6;


class Tree : public Object
{
private:
    Sprite branches[NUM_BRANCHES];
    side branchPositions[NUM_BRANCHES];
    Texture textureBranch;
public:
    Tree(float positionX, float positionY);

    void dissapearAllBranches();
    side getNearestBranch() const;
    void updateBranches(int seed);

    virtual void update(RenderWindow& window, Time timedelta) override;
    virtual void draw(RenderWindow& window) override;
};
