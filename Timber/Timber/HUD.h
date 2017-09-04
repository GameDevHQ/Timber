#pragma once
#include "Object.h"


const unsigned int MESSAGE_TEXT_SIZE = 75;
const unsigned int SCORE_TEXT_SIZE = 100;
const float TEXT_PADDING_TOP_LEFT = 20.0f;


class HUD: public Object
{
private:
    Text messageText;
    Text scoreText;
    Font font;

    RectangleShape timeBar;
    float timeBarStartWidth;
    float timeBarHeight;
    float timeBarWidthPerSecond;

    int oldScore;           // Previous value of the players score
    bool* pIsPaused;        // Only for reading purposes
    int* pScore;            // Only for reading purposes
    float* pTimeRemaining;  // Only for reading purposes
    bool* pPlayerIsDied;    // Only for reading purposes
public:
    HUD(bool* pIsPaused, int* score, float* pTimeRemaining, bool* playerIsDied);

    virtual void update(RenderWindow& window, Time timedelta) override;
    virtual void draw(RenderWindow& window) override;
private:
    void setMessageText(std::string text);
    void updateScore(int score);
    void updateTimeRemaining(float timeRemaining);
};
