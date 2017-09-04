#include "stdafx.h"
#include <array>
#include "Background.h"
#include "Bee.h"
#include "Cloud.h"
#include "Tree.h"
#include "HUD.h"


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
        bee.draw(window);
        hud.draw(window);

        window.display();
    }

    return 0;
}
