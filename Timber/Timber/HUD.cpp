#include "stdafx.h"
#include "HUD.h"
#include <sstream>


HUD::HUD(bool* pIsPaused, int* pScore, float* pTimeRemaining, bool* pPlayerIsDied):
Object(),
pIsPaused(pIsPaused),
pScore(pScore),
pTimeRemaining(pTimeRemaining),
pPlayerIsDied(pPlayerIsDied),
timeBarWidthPerSecond(60)
{
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

    // Time bar
    timeBarStartWidth = 400;
    timeBarHeight = 80;

    if (pTimeRemaining)
        timeBarWidthPerSecond = timeBarStartWidth / (*pTimeRemaining);

    timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
    timeBar.setFillColor(Color::Red);
    timeBar.setPosition((WINDOW_WIDTH / 2) - timeBarStartWidth / 2, 980);
}


void HUD::setMessageText(std::string text)
{
    // Change the message shown to the player
    messageText.setString(text);

    // Reposition the text based on its new size
    FloatRect textRect = messageText.getLocalBounds();
    messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    messageText.setPosition(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f);
}


void HUD::updateScore(int score)
{
    std::stringstream ss;
    ss << "Score = " << score;
    scoreText.setString(ss.str());
}


void HUD::updateTimeRemaining(float timeRemaining)
{
    // Size up the time bar
    timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));
}


void HUD::update(RenderWindow& window, Time timedelta)
{
    updateTimeRemaining(*pTimeRemaining);

    if (pIsPaused && (*pIsPaused))
    {
        if (pTimeRemaining && (*pTimeRemaining <= 0.0f))
            setMessageText("Out of time!!");

        if (pPlayerIsDied && (*pPlayerIsDied))
            setMessageText("SQUISHED!!");
    }

    if (pScore && (*pScore) != oldScore)
    {
        oldScore = *pScore;
        updateScore(oldScore);
    }
}


void HUD::draw(RenderWindow& window)
{
    // Draw the timebar
    window.draw(timeBar);

    // Display messages on the screen
    window.draw(scoreText);
    if (pIsPaused && (*pIsPaused))
    {
        window.draw(messageText);
    }
}
