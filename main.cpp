#include "Game.h"

int main(int argc, char* argv[])
{
	Game* game = new Game();
	game->Init();
	game->LoadMedia();
	game->HandleEvents();
	game->Close();
	return 0;
}


