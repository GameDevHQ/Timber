#include "stdafx.h"
#include "Tree.h"


Tree::Tree(float positionX, float positionY): Object("Resources/Graphics/tree.png")
{
    objectTexture.loadFromFile(pathToTexture);

    objectSprite.setTexture(objectTexture);
    objectSprite.setPosition(positionX, positionY);

    // Prepare branches
    textureBranch.loadFromFile("Resources/Graphics/branch.png");

    // Set the texture for each branch sprite
    for (int i = 0; i < NUM_BRANCHES; i++)
    {
        branches[i].setTexture(textureBranch);
        branches[i].setPosition(-2000, -2000);
        // Set the sprite's origin to dead center, so that we can spin it round without changing its position
        branches[i].setOrigin(220, 20);
    }
}


void Tree::dissapearAllBranches()
{
    for (int i = 1; i < NUM_BRANCHES; i++)
    {
        branchPositions[i] = side::NONE;
    }
}


side Tree::getNearestBranch() const
{
    return branchPositions[NUM_BRANCHES - 1];
}


void Tree::updateBranches(int seed)
{
    // Move all the branches down one place
    for (int j = NUM_BRANCHES - 1; j > 0; j--)
    {
        branchPositions[j] = branchPositions[j - 1];
    }

    // Spawn a new branch at position 0
    // LEFT, RIGHT or NONE
    srand(static_cast<unsigned int>(time(0) + seed));
    int r = (rand() % 5);
    switch (r)
    {
    case 0:
        branchPositions[0] = side::LEFT;
        break;
    case 1:
        branchPositions[0] = side::RIGHT;
        break;
    default:
        branchPositions[0] = side::NONE;
        break;
    }
}


void Tree::update(RenderWindow& window, Time timedelta)
{
    for (int i = 0; i < NUM_BRANCHES; i++)
    {
        float height = i * 150;
        if (branchPositions[i] == side::LEFT)
        {
            // Move the sprite to the left side
            branches[i].setPosition(610, height);
            // Flip the sprite round the other way
            branches[i].setRotation(180);
        }
        else if (branchPositions[i] == side::RIGHT)
        {
            // Move the sprite to the right side
            branches[i].setPosition(1330, height);
            // Set the sprite rotation to normal
            branches[i].setRotation(0);
        }
        else
        {
            // Hide the branch
            branches[i].setPosition(3000, height);
        }
    }
}


void Tree::draw(RenderWindow& window)
{
    window.draw(objectSprite);

    for (int i = 0; i < NUM_BRANCHES; i++)
    {
        window.draw(branches[i]);
    }
}
