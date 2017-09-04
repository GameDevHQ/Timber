#include "stdafx.h"
#include <array>
#include "Background.h"
#include "Bee.h"
#include "Cloud.h"
#include "Tree.h"
#include "HUD.h"


void updateBranches(int seed);
enum class side
{
    LEFT,
    RIGHT,
    NONE
};

const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];
side branchPositions[NUM_BRANCHES];



int main()
{
    // Create and open a SFML window
    VideoMode vm(WINDOW_HEIGHT, WINDOW_WIDTH);
    RenderWindow window(vm, "Timber", Style::Fullscreen);

    // Prepare rendered objects...
    Background background;
    Tree tree(810.f, 0.0f);
    Bee bee(0.0f, 800.f);

    // Make three cloud sprites from one texture
    Texture textureCloud;
    textureCloud.loadFromFile("Resources/Graphics/cloud.png");
    
    std::array<Cloud, 3> clouds = {
        Cloud(0.0f, 0.0f, textureCloud, 10),
        Cloud(0.0f, 150.0f, textureCloud, 20),
        Cloud(0.0f, 300.0f, textureCloud, 30)
    };

    Clock clock;

    Time gameTimeTotal;
    bool isPaused = true;           // Track whether the game is running
    int score = 0;                  // Score per game
    float timeRemaining = 6.0f;     // Time remaining

    HUD hud(&isPaused, &score, &timeRemaining);

    // Prepare branches
    Texture textureBranch;
    textureBranch.loadFromFile("Resources/Graphics/branch.png");

    // Set the texture for each branch sprite
    for (int i = 0; i < NUM_BRANCHES; i++)
    {
        branches[i].setTexture(textureBranch);
        branches[i].setPosition(-2000, -2000);
        // Set the sprite's origin to dead center
        // We can then spin it round without changing its position
        branches[i].setOrigin(220, 20);
    }

    while(window.isOpen())
    {
        //--------------------------------------------------
        // Handle the players input
        //--------------------------------------------------
        // Exit from the game
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }
        // Start the game
        else if (Keyboard::isKeyPressed(Keyboard::Return))
        {
            isPaused = false;
            score = 0;
            timeRemaining = 5;
        }

        //--------------------------------------------------
        // Update the scene
        //--------------------------------------------------
        if (!isPaused)
        {
            // Time elapsed after previous frame
            Time timedelta = clock.restart();

            // Subtract from the amount of time remaining
            timeRemaining -= timedelta.asSeconds();

            if (timeRemaining <= 0.0f)
            {
                // Pause the game
                isPaused = true;
            }

            bee.update(window, timedelta);

            for (auto it = clouds.begin(); it != clouds.end(); it++)
                it->update(window, timedelta);

            // update the branch sprites
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

            hud.update(window, timedelta);
        }

        //--------------------------------------------------
        // Draw the scene
        //--------------------------------------------------
        window.clear();

        background.draw(window);

        for (auto it = clouds.begin(); it != clouds.end(); it++)
            it->draw(window);

        tree.draw(window);
        for (int i = 0; i < NUM_BRANCHES; i++)
        {
            window.draw(branches[i]);
        }

        bee.draw(window);
        hud.draw(window);

        window.display();
    }

    return 0;
}


void updateBranches(int seed)
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
