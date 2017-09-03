#include "stdafx.h"
#include <vector>
#include "Background.h"
#include "Bee.h"
#include "Cloud.h"
#include "Tree.h"


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
    
    std::vector<Cloud> clouds;
    clouds.emplace_back(Cloud(0.0f, 0.0f, textureCloud, 10));
    clouds.emplace_back(Cloud(0.0f, 150.0f, textureCloud, 20));
    clouds.emplace_back(Cloud(0.0f, 300.0f, textureCloud, 30));

    Clock clock;

    // Track whether the game is running
    bool isPaused = true;

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
        }

        //--------------------------------------------------
        // Update the scene
        //--------------------------------------------------
        if (!isPaused)
        {
            // Time elapsed after previous frame
            Time timedelta = clock.restart();

            bee.Update(window, timedelta);

            for (auto it = clouds.begin(); it != clouds.end(); it++)
                it->Update(window, timedelta);
        }

        //--------------------------------------------------
        // Draw the scene
        //--------------------------------------------------
        window.clear();

        background.Draw(window);

        for (Cloud cloud: clouds)
            cloud.Draw(window);

        tree.Draw(window);
        bee.Draw(window);

        window.display();
    }

    return 0;
}
