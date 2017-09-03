#include "stdafx.h"
#include <array>
#include <sstream>
#include "Background.h"
#include "Bee.h"
#include "Cloud.h"
#include "Tree.h"


// TODO: Move messages/timebar/etc. into separate HUD class


const unsigned int MESSAGE_TEXT_SIZE = 75;
const unsigned int SCORE_TEXT_SIZE = 100;
const float TEXT_PADDING_TOP_LEFT = 20.0f;


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

    // Time bar
    RectangleShape timeBar;
    float timeBarStartWidth = 400;
    float timeBarHeight = 80;
    timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
    timeBar.setFillColor(Color::Red);
    timeBar.setPosition((WINDOW_WIDTH / 2) - timeBarStartWidth / 2, 980);

    Time gameTimeTotal;
    float timeRemaining = 6.0f;
    float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

    // Track whether the game is running
    bool isPaused = true;

    // Game HUD
    int score = 0;
    Text messageText;
    Text scoreText;

    // We need to choose a font
    Font font;
    font.loadFromFile("Resources/Fonts/KOMIKAP_.ttf");

    // Set the font to our message
    messageText.setFont(font);
    scoreText.setFont(font);

    // Assign the actual message
    messageText.setString("Press Enter to start!");
    scoreText.setString("Score = 0");

    // Change the default size to a custom
    messageText.setCharacterSize(MESSAGE_TEXT_SIZE);
    scoreText.setCharacterSize(SCORE_TEXT_SIZE);

    // Choose a color
    messageText.setFillColor(Color::White);
    scoreText.setFillColor(Color::White);

    // Position the text
    FloatRect textRect = messageText.getLocalBounds();
    messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    messageText.setPosition(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f);
    scoreText.setPosition(TEXT_PADDING_TOP_LEFT, TEXT_PADDING_TOP_LEFT);

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
            // size up the time bar
            timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));

            if (timeRemaining <= 0.0f)
            {
                // Pause the game
                isPaused = true;

                // Change the message shown to the player
                messageText.setString("Out of time!!");

                //Reposition the text based on its new size
                FloatRect textRect = messageText.getLocalBounds();
                messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
                messageText.setPosition(WINDOW_WIDTH / 2.0f, 1080 / 2.0f);
            }

            bee.Update(window, timedelta);

            for (auto it = clouds.begin(); it != clouds.end(); it++)
                it->Update(window, timedelta);

            // Update score
            std::stringstream ss;
            ss << "Score = " << score;
            scoreText.setString(ss.str());
        }

        //--------------------------------------------------
        // Draw the scene
        //--------------------------------------------------
        window.clear();

        background.Draw(window);

        for (auto it = clouds.begin(); it != clouds.end(); it++)
            it->Draw(window);

        tree.Draw(window);
        bee.Draw(window);

        // Draw the timebar
        window.draw(timeBar);

        window.draw(scoreText);
        if (isPaused)
        {
            // Draw our message
            window.draw(messageText);
        }

        window.display();
    }

    return 0;
}
