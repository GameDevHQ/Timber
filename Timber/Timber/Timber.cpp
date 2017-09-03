#include "stdafx.h"
#include "SFML/Graphics.hpp"

using namespace sf;


int main()
{
	// Create and open a SFML window
	VideoMode vm(1920, 1080);
	RenderWindow window(vm, "Timber", Style::Fullscreen);

	return 0;
}

