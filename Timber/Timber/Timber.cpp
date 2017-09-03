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
	clouds.emplace_back(Cloud(0.0f, 0.0f, textureCloud));
	clouds.emplace_back(Cloud(0.0f, 150.0f, textureCloud));
	clouds.emplace_back(Cloud(0.0f, 300.0f, textureCloud));

	Clock clock;

	while(window.isOpen())
	{
		//--------------------------------------------------
		// Handle the players input
		//--------------------------------------------------
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		//--------------------------------------------------
		// Update the scene
		//--------------------------------------------------
		// Measure time
		Time timedelta = clock.restart();
		
		bee.Update(window, timedelta);

		//--------------------------------------------------
		// Draw the scene
		//--------------------------------------------------
		
		window.clear();

		background.Draw(window);

		for (auto cloud: clouds)
			cloud.Draw(window);

		tree.Draw(window);
		bee.Draw(window);

		window.display();
	}

	return 0;
}
