#include "stdafx.h"
#include "Game.h"

int main()
{
	srand(static_cast<unsigned>(time(NULL)));

	Game game;

	while (game.getWindow().isOpen() && game.gameRunning())
	{
		game.update();
		game.render();
	}
}