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
    bool playerIsDied = false;      // Player is squished by branch?

    HUD hud(&isPaused, &score, &timeRemaining, &playerIsDied);

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

    // Prepare the player
    Texture texturePlayer;
    texturePlayer.loadFromFile("Resources/Graphics/player.png");

    Sprite spritePlayer;
    spritePlayer.setTexture(texturePlayer);
    spritePlayer.setPosition(580, 720);

    // The player starts on the left
    side playerSide = side::LEFT;

    // Prepare the gravestone
    Texture textureRIP;
    textureRIP.loadFromFile("Resources/Graphics/rip.png");
    Sprite spriteRIP;
    spriteRIP.setTexture(textureRIP);
    spriteRIP.setPosition(600, 860);

    // Prepare the axe
    Texture textureAxe;
    textureAxe.loadFromFile("Resources/Graphics/axe.png");
    Sprite spriteAxe;
    spriteAxe.setTexture(textureAxe);
    spriteAxe.setPosition(700, 830);

    // Line the axe up with the tree
    const float AXE_POSITION_LEFT = 700;
    const float AXE_POSITION_RIGHT = 1075;

    // Prepare the flying log
    Texture textureLog;
    textureLog.loadFromFile("Resources/Graphics/log.png");

    Sprite spriteLog;
    spriteLog.setTexture(textureLog);
    spriteLog.setPosition(810, 720);

    // Some other useful log related variables
    bool logActive = false;
    float logSpeedX = 1000;
    float logSpeedY = -1500;

    // Control the player input
    bool acceptInput = false;

    while(window.isOpen())
    {
        //--------------------------------------------------
        // Handle the players input
        //--------------------------------------------------
        Event event;

        while (window.pollEvent(event))
        {
            if (event.type == Event::KeyReleased && !isPaused)
            {
                // Listen for key presses again
                acceptInput = true;
                
                // Hide the axe
                spriteAxe.setPosition(2000, spriteAxe.getPosition().y);
            }
        }

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
            playerIsDied = false;

            // Make all the branches disappear
            for (int i = 1; i < NUM_BRANCHES; i++)
            {
                branchPositions[i] = side::NONE;
            }

            // Make sure the gravestone is hidden
            spriteRIP.setPosition(675, 2000);

            // Move the player into position
            spritePlayer.setPosition(580, 720);
            acceptInput = true;
        }

        // Wrap the player controls to make sure we are accepting input
        if (acceptInput)
        {
            // First handle pressing the right cursor key
            if (Keyboard::isKeyPressed(Keyboard::Right))
            {
                // Make sure the player is on the right
                playerSide = side::RIGHT;
                score++;
                
                // Add to the amount of time remaining
                timeRemaining += (2 / score) + .15;
                spriteAxe.setPosition(AXE_POSITION_RIGHT, spriteAxe.getPosition().y);
                spritePlayer.setPosition(1200, 720);
                
                // Update the branches
                updateBranches(score);

                // Set the log flying to the left
                spriteLog.setPosition(810, 720);
                logSpeedX = -5000;
                logActive = true;
                acceptInput = false;
            }
            else if (Keyboard::isKeyPressed(Keyboard::Left))
            {
                // Make sure the player is on the left
                playerSide = side::LEFT;
                score++;

                // Add to the amount of time remaining
                timeRemaining += (2 / score) + .15;
                spriteAxe.setPosition(AXE_POSITION_LEFT, spriteAxe.getPosition().y);
                spritePlayer.setPosition(580, 720);

                // Update the branches
                updateBranches(score);

                // Set the log flying
                spriteLog.setPosition(810, 720);

                logSpeedX = 5000;
                logActive = true;

                acceptInput = false;
            }

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

            // Handle a flying log
            if (logActive)
            {
                float newPositionX = spriteLog.getPosition().x + (logSpeedX * timedelta.asSeconds());
                float newPositionY = spriteLog.getPosition().y + (logSpeedY * timedelta.asSeconds());
                spriteLog.setPosition(newPositionX, newPositionY);

                // Has the log reached the right hand edge?
                if (spriteLog.getPosition().x < -100 || spriteLog.getPosition().x > 2000)
                {
                    // Set it up ready to be a whole new log next frame
                    logActive = false;
                    spriteLog.setPosition(810, 720);
                }
            }

            // Has the player been squished by a branch?
            if (branchPositions[5] == playerSide)
            {
                // Death
                isPaused = true;
                playerIsDied = true;
                acceptInput = false;

                // Draw the gravestone
                spriteRIP.setPosition(525, 760);
                
                // Hide the player
                spritePlayer.setPosition(2000, 660);
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
        window.draw(spritePlayer);
        window.draw(spriteAxe);
        window.draw(spriteLog);
        window.draw(spriteRIP);

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
