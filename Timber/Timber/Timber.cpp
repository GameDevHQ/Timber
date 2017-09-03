#include "stdafx.h"

#include "SFML/Graphics.hpp"

using namespace sf;

const int windowHeight = 1920;
const int windowWidth  = 1080;


int main()
{
	// Create and open a SFML window
	VideoMode vm(windowHeight, windowWidth);
	RenderWindow window(vm, "Timber", Style::Fullscreen);

	// Get the background
	Texture textureBackground;
	textureBackground.loadFromFile("Resources/Graphics/background.png");

	Sprite spriteBackground;
	spriteBackground.setTexture(textureBackground);
	spriteBackground.setPosition(0, 0);

	// Add a tree on the scene
	Texture textureTree;
	textureTree.loadFromFile("Resources/Graphics/tree.png");

	Sprite spriteTree;
	spriteTree.setTexture(textureTree);
	spriteTree.setPosition(windowWidth / 2, 0);

	// Prepare a bee
	bool beeActive = false;
	float beeSpeed = 0.0f;

	Texture textureBee;
	textureBee.loadFromFile("Resources/Graphics/bee.png");

	Sprite spriteBee;
	spriteBee.setTexture(textureBee);
	spriteBee.setPosition(0, 800);

	// Make three cloud sprites from one texture
	Texture textureCloud;
	textureCloud.loadFromFile("Resources/Graphics/cloud.png");
	
	bool cloud1Active = false;
	bool cloud2Active = false;
	bool cloud3Active = false;

	float cloud1Speed = 0.0f;
	float cloud2Speed = 0.0f;
	float cloud3Speed = 0.0f;

	// 3 New sprites withe the same texture
	Sprite spriteCloud1;
	Sprite spriteCloud2;
	Sprite spriteCloud3;
	spriteCloud1.setTexture(textureCloud);
	spriteCloud2.setTexture(textureCloud);
	spriteCloud3.setTexture(textureCloud);

	spriteCloud1.setPosition(0, 0);
	spriteCloud2.setPosition(0, 150);
	spriteCloud3.setPosition(0, 300);


	while(window.isOpen())
	{
		/*
		**************************************************
		Handle the players input
		**************************************************
		*/
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		/*
		**************************************************
		Update the scene
		**************************************************
		*/

		/*
		**************************************************
		Draw the scene
		**************************************************
		*/
		window.clear();

		window.draw(spriteBackground);

		window.draw(spriteCloud1);
		window.draw(spriteCloud2);
		window.draw(spriteCloud3);

		window.draw(spriteTree);
		window.draw(spriteBee);

		window.display();
	}

	return 0;
}

