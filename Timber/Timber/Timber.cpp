#include "stdafx.h"
#include <array>
#include "Background.h"
#include "Bee.h"
#include "Cloud.h"
#include "Tree.h"
#include "HUD.h"
#include "Player.h"
#include "Log.h"
#include "Sound.h"


SoundManager soundManager = soundManager.getInstance();


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

    Player player;
    Log log;
    HUD hud(&isPaused, &score, &timeRemaining, &playerIsDied);

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
                player.hideAxe();
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
            tree.dissapearAllBranches();

            // Make sure the gravestone is hidden
            player.hideGravestone();

            // Move the player into position
            player.moveRight();

            acceptInput = true;
        }

        // Wrap the player controls to make sure we are accepting input
        if (acceptInput)
        {
            // First handle pressing the right cursor key
            if (Keyboard::isKeyPressed(Keyboard::Right))
            {
                player.moveRight();
                score++;

                // Add to the amount of time remaining
                timeRemaining += (2 / score) + .15;
                
                // Update the branches
                tree.updateBranches(score);

                // Set the log flying to the left
                log.setIsFlyingLeft();

                acceptInput = false;

                // Play a chop sound
                soundManager.play("chop");
            }
            else if (Keyboard::isKeyPressed(Keyboard::Left))
            {
                player.moveLeft();
                score++;

                // Add to the amount of time remaining
                timeRemaining += (2 / score) + .15;

                // Update the branches
                tree.updateBranches(score);

                // Set the log flying to the right
                log.setIsFlyingRight();

                acceptInput = false;

                // Play a chop sound
                soundManager.play("chop");
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

                // Play the out of time sound
                soundManager.play("out_of_time");
            }

            bee.update(window, timedelta);

            for (auto it = clouds.begin(); it != clouds.end(); it++)
                it->update(window, timedelta);

            // Update the branch sprites
            tree.update(window, timedelta);

            // Handle a flying log
            log.update(window, timedelta);

            // Has the player been squished by a branch?
            if (tree.getNearestBranch() == player.getPlayerSide())
            {
                // Death
                isPaused = true;
                playerIsDied = true;
                acceptInput = false;

                // Draw the gravestone
                player.showGravestone();
                
                // Hide the player
                player.hidePlayer();

                // Play the death sound
                soundManager.play("death");
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
        player.draw(window);
        log.draw(window);
        bee.draw(window);
        hud.draw(window);

        window.display();
    }

    return 0;
}
