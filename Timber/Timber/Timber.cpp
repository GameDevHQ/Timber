#include "stdafx.h"

#include "SFML/Graphics.hpp"

using namespace sf;


int main()
{
	// Create and open a SFML window
	VideoMode vm(1920, 1080);
	RenderWindow window(vm, "Timber", Style::Fullscreen);

	// Get the background
	Texture textureBackground;
	textureBackground.loadFromFile("Resources/Graphics/background.png");

	Sprite spriteBackground;
	spriteBackground.setTexture(textureBackground);
	spriteBackground.setPosition(0, 0);

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
		window.display();
	}

	return 0;
}

