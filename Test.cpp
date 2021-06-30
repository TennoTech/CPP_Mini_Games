#include "Game.h"
#include <ctime>

int main()
{
	Game game;

	srand(static_cast<unsigned>(time(NULL)));

	// Game Loop
	while (game.IsWindowOpen() && !game.GetHasGameEnded())
	{
		// Update
		game.Update();

		// Render
		game.Render();
	}

	return 0;
}
