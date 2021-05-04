#include "Game.h"
#include "Game_Base.h"
#include "Game_Utils.h"
#include "LTexture.h"
#include "Button.h"
#include "Character.h"
#include "Enemy.h"
#include <vector>
using namespace std;
SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
SDL_Color textColor = { 0, 0, 0 };
TTF_Font* gFont = nullptr;
Mix_Music* gMusic = nullptr;
Mix_Music* gMenuMusic = nullptr;
Mix_Chunk* gClick = nullptr;
Mix_Chunk* gJump = nullptr;
Mix_Chunk* gLose = nullptr;
const std::string SCENCE1[BACKGROUND_LAYER] = {
	"imgs/background/Scence_01.png",
	"imgs/background/Scence_02.png",
	"imgs/background/Scence_03.png",
	"imgs/background/Scence_04.png",
	"imgs/background/Scence_05.png",
	"imgs/background/Scence_06.png",
	"imgs/background/Scence_07.png",
	"imgs/background/Scence_08.png",
	"imgs/background/Scence_09.png",
};
const std::string SCENCE2[BACKGROUND_LAYER] = {
	"imgs/background/1.png",
	"imgs/background/2.png",
	"imgs/background/3.png",
	"imgs/background/4.png",
	"imgs/background/5.png",
	"imgs/background/6.png",
	"imgs/background/7.png",
	"imgs/background/8.png",
	"imgs/background/9.png",
};

const std::string SCENCE3[BACKGROUND_LAYER] = {
	"imgs/background/Scence3_01.png",
	"imgs/background/Scence3_02.png",
	"imgs/background/Scence3_03.png",
	"imgs/background/Scence3_04.png",
	"imgs/background/Scence3_05.png",
	"imgs/background/Scence3_06.png",
	"imgs/background/Scence3_07.png",
	"imgs/background/Scence3_08.png",
	"imgs/background/Scence3_09.png",
};
SDL_Rect gPlayButton[BUTTON_TOTAL];
SDL_Rect gHelpButton[BUTTON_TOTAL];
SDL_Rect gExitButton[BUTTON_TOTAL];
SDL_Rect gBackButton[BUTTON_TOTAL];
SDL_Rect gPauseButton[BUTTON_TOTAL];
SDL_Rect gContinueButton[BUTTON_TOTAL];
SDL_Rect gPlayAgainButton[BUTTON_TOTAL];
SDL_Rect gCharacterClips[RUNNING_FRAMES];
SDL_Rect gEnemyClips3[FLYING_FRAMES]; 
SDL_Rect gPortalClips[16];
SDL_Rect gEnemyClips1[12];
SDL_Rect gEnemyClips2[12];
SDL_Rect gEnemyClipsGolem[18];
LTexture gMenuTexture;
LTexture gInstructionTexture;
LTexture g_BackgroundTexture[BACKGROUND_LAYER];
LTexture g_BackgroundTexture1[BACKGROUND_LAYER];
LTexture g_BackgroundTexture2[BACKGROUND_LAYER];
LTexture g_BackgroundTexture3[BACKGROUND_LAYER];
LTexture gGroundTexture;
LTexture gPlayButtonTexture;
LTexture gHelpButtonTexture;
LTexture gExitButtonTexture;
LTexture gBackButtonTexture;
LTexture gPauseButtonTexture;
LTexture gContinueButtonTexture;
LTexture gLoseTexture;
LTexture gText1Texture;
LTexture gScoreTexture;
LTexture gDeathCountTexture;
LTexture gText2Texture;
LTexture gText3Texture;
LTexture gHighScoreTexture;
Button PlayButton(PLAY_BUTON_POSX, PLAY_BUTTON_POSY);
Button HelpButton(HELP_BUTTON_POSX, HELP_BUTTON_POSY);
Button ExitButton(EXIT_BUTTON_POSX, EXIT_BUTTON_POSY);
Button BackButton(BACK_BUTTON_POSX, BACK_BUTTON_POSY);
Button PauseButton(PAUSE_BUTTON_POSX, PAUSE_BUTTON_POSY);
Button ContinueButton(CONTINUE_BUTTON_POSX, CONTINUE_BUTTON_POSY);
Character character;
bool Game::Init() {
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_VIDEO) < 0)
	{
		LogError("Can not initialize SDL.", SDL_ERROR);
		success = false;
	}

	else
	{
		SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			std::cout << "Warning: Linear texture filtering not enabled!";
		}

		gWindow = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			LogError("Can not create window", SDL_ERROR);
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_WINDOW_OPENGL);
			if (gRenderer == NULL)
			{
				LogError("Can not create renderer", SDL_ERROR);
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					LogError("Can not initialize SDL_image", IMG_ERROR);
					success = false;
				}

				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}

				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
			}
		}
	}
	return success;
}

void Game::HandleEvents() {
	bool Quit_Menu = false;
	bool Play_Again = false;
	Mix_PlayMusic(gMenuMusic, IS_REPEATITIVE);
	while (!Quit_Menu)
	{
		SDL_Event e_mouse;
		while (SDL_PollEvent(&e_mouse) != 0)
		{
			if (e_mouse.type == SDL_QUIT)
			{
				Quit_Menu = true;
			}

			bool Quit_Game = false;
			HandlePlayButton(&e_mouse, PlayButton, Quit_Menu, Play_Again, gClick);

			HandleHelpButton(&e_mouse, gBackButton,
				HelpButton, BackButton,
				gInstructionTexture, gBackButtonTexture,
				gRenderer, Quit_Game, gClick);

			HandleExitButton(&e_mouse, ExitButton, Quit_Menu, gClick);
		}
		gMenuTexture.Render(0, 0, gRenderer);
		SDL_Rect* currentClip_Play = &gPlayButton[PlayButton.currentSprite];
		PlayButton.Render(currentClip_Play, gRenderer, gPlayButtonTexture);
		SDL_Rect* currentClip_Help = &gHelpButton[HelpButton.currentSprite];
		HelpButton.Render(currentClip_Help, gRenderer, gHelpButtonTexture);
		SDL_Rect* currentClip_Exit = &gExitButton[ExitButton.currentSprite];
		ExitButton.Render(currentClip_Exit, gRenderer, gExitButtonTexture);
		SDL_RenderPresent(gRenderer);
	}
	int deathCount = 0;
	while (Play_Again)
	{
		for (int i = 0; i < 9; i++) {
			g_BackgroundTexture[i] = g_BackgroundTexture1[i];
		}
		bool desert = false;
		bool winter = true;
		bool night = false;
		bool createPortal = false;
		srand(time(NULL));
		int time = 0;
		int score = 0;
		int acceleration = 2;
		int frame_Character = 0;
		int frame_Enemy = 0;
		int frame_Enemy1 = 0;
		int frame_Enemy2 = 0;
		int frame_Enemy3 = 0;
		int frame_Portal = 0;
		int count = 0;
		std::string highscore = GetHighScoreFromFile("high_score.txt");
		SDL_Event e;
		Enemy enemy1(GOLEM);
		Enemy enemy2(GOLEM);
		Enemy enemy3(IN_AIR_ENEMY);
		Enemy portal(PORTAL);
		Mix_PlayMusic(gMusic, IS_REPEATITIVE);
		enemy1.GenerateGolem(enemy1, gEnemyClips1, gRenderer);
		enemy2.GenerateGolem(enemy2, gEnemyClips2, gRenderer);
		enemy3.GenerateBat(enemy3, gEnemyClips3, gRenderer);
		//portal.GeneratePortal(portal, gPortalClips, gRenderer);
		character.GenerateCharacter(character, gCharacterClips, gRenderer);
		int OffsetSpeed_Ground = BASE_OFFSET_SPEED;
		std::vector <double> OffsetSpeed_Bkgr(BACKGROUND_LAYER, BASE_OFFSET_SPEED);
		bool Quit = false;
		bool Game_State = true;
		int next = 0;
		bool lose = false;
		while (!Quit)
		{
			
			if (Game_State)
			{		
				if (enemy1.GetPosX() >= 0 && abs(enemy1.GetPosX() - enemy2.GetPosX()) < 170 + 20 * acceleration) {
					enemy2.posX = enemy1.posX - (170 + 20 * acceleration);
				}
				UpdateGameTimeAndScore(time, acceleration, score);
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						Quit = true;
						Play_Again = false;
					}
					else HandlePauseButton(&e, gRenderer, gContinueButton,
						PauseButton, ContinueButton,
						gContinueButtonTexture, Game_State, gClick);
					character.HandleEvent(e, gJump);
				}
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);
				if (winter) {
					enemy1.GenerateGolem(enemy1, gEnemyClips1, gRenderer);
					enemy2.GenerateGolem(enemy2, gEnemyClips2, gRenderer);
					enemy1.pathID = "imgs/enemy/golem.png";
					enemy2.pathID = "imgs/enemy/golem.png";
					RenderScrollingBackground(OffsetSpeed_Bkgr, g_BackgroundTexture1, gRenderer);
				}
				else if (night) {
					enemy1.GenerateGolem(enemy1, gEnemyClips1, gRenderer);
					enemy2.GenerateGolem(enemy2, gEnemyClips2, gRenderer);
					enemy1.pathID = "imgs/enemy/golem3.png";
					enemy2.pathID = "imgs/enemy/golem3.png";
					RenderScrollingBackground(OffsetSpeed_Bkgr, g_BackgroundTexture2, gRenderer);
				}
				else {
					enemy1.GenerateGolem(enemy1, gEnemyClips1, gRenderer);
					enemy2.GenerateGolem(enemy2, gEnemyClips2, gRenderer);
					enemy1.pathID = "imgs/enemy/golem2.png";
					enemy2.pathID = "imgs/enemy/golem2.png";
					RenderScrollingBackground(OffsetSpeed_Bkgr, g_BackgroundTexture3, gRenderer);
				}
				if (score >= 150 && score % 150 ==0 )
				{
					createPortal = true;
				}
				character.Move();
				SDL_Rect* currentClip_Character = nullptr;
				if (character.OnGround())
				{
					currentClip_Character = &gCharacterClips[frame_Character / SLOW_FRAME_CHAR];
					character.Render(gRenderer, currentClip_Character);
				}
				else if (character.GetPosY() < GROUND)
				{
					currentClip_Character = &gCharacterClips[0];
					character.Render(gRenderer, currentClip_Character);
				}
				SDL_Rect* currentClip_Enemy1 = &gEnemyClips1[frame_Enemy1 / SLOW_FRAME_ENEMY];
				SDL_Rect* currentClip_Enemy2 = &gEnemyClips2[frame_Enemy2 / SLOW_FRAME_ENEMY];
				SDL_Rect* currentClip_Enemy3 = &gEnemyClips3[frame_Enemy3 / SLOW_FRAME_ENEMY];
				SDL_Rect* currentClip_Portal = &gPortalClips[frame_Portal / SLOW_FRAME_ENEMY];
				enemy1.Move(acceleration);
				enemy1.Render(gRenderer, currentClip_Enemy1);
				enemy2.Move(acceleration);
				enemy2.Render(gRenderer, currentClip_Enemy2);
				enemy3.Move(acceleration);
				enemy3.Render(gRenderer, currentClip_Enemy3);
				if (createPortal) {
					if (desert) {
						portal.pathID = "imgs/enemy/portal3.png";
						portal.GeneratePortal(portal, gPortalClips, gRenderer);
					}
					else if (night) {
						portal.pathID = "imgs/enemy/portal2.png";
						portal.GeneratePortal(portal, gPortalClips, gRenderer);
					}
					else {
						portal.pathID = "imgs/enemy/portal.png";
						portal.GeneratePortal(portal, gPortalClips, gRenderer);
					}
					portal.Move(acceleration);
					portal.Render(gRenderer, currentClip_Portal);
				}
				SDL_Rect* currentClip_Pause = &gPauseButton[PauseButton.currentSprite];
				PauseButton.Render(currentClip_Pause, gRenderer, gPauseButtonTexture);
				DrawPlayerScore(gText1Texture, gScoreTexture, textColor, gRenderer, gFont, score);
				DrawPlayerHighScore(gText2Texture, gHighScoreTexture, textColor, gRenderer, gFont, highscore);
				DrawDeath(gText3Texture, gDeathCountTexture, textColor, gRenderer, gFont, deathCount);
				if (CheckEnemyColission(character,
					enemy1, enemy2, enemy3,
					currentClip_Character, currentClip_Enemy1, currentClip_Enemy2, currentClip_Enemy3))
				{
					deathCount++;
					Mix_PauseMusic();
					Mix_PlayChannel(MIX_CHANNEL, gLose, NOT_REPEATITIVE);
					UpdateHighScore("high_score.txt", score, highscore);
					Quit = true;
					DrawEndGameSelection(gLoseTexture, &e, gRenderer, Play_Again);
					if (!Play_Again)
					{
						enemy1.~Enemy();
						enemy2.~Enemy();
						enemy3.~Enemy();
					}			
				}
				if (CheckColission(character, currentClip_Character, portal, currentClip_Portal)) {			
					createPortal = false;
					if (desert) {
						desert = false;
						winter = true;
						SDL_RenderClear(gRenderer);
						SDL_Delay(38);
						RenderScrollingBackground(OffsetSpeed_Bkgr, g_BackgroundTexture3, gRenderer);
						SDL_RenderPresent(gRenderer);
						SDL_RenderClear(gRenderer);
						SDL_Delay(38);
						RenderScrollingBackground(OffsetSpeed_Bkgr, g_BackgroundTexture2, gRenderer);
						SDL_RenderPresent(gRenderer);
						SDL_RenderClear(gRenderer);
						SDL_Delay(38);
						RenderScrollingBackground(OffsetSpeed_Bkgr, g_BackgroundTexture1, gRenderer);
						SDL_RenderPresent(gRenderer);
						SDL_RenderClear(gRenderer);
						SDL_Delay(38);
						RenderScrollingBackground(OffsetSpeed_Bkgr, g_BackgroundTexture3, gRenderer);
						SDL_RenderPresent(gRenderer);
						SDL_RenderClear(gRenderer);
						SDL_Delay(38);
						RenderScrollingBackground(OffsetSpeed_Bkgr, g_BackgroundTexture2, gRenderer);
						SDL_RenderPresent(gRenderer);
						SDL_RenderClear(gRenderer);
						SDL_Delay(38);
						ControlCharFrame(frame_Character);
						ControlBatFrame(frame_Enemy3);
						ControlGolemFrame(frame_Enemy1);
						ControlGolemFrame(frame_Enemy2);
						ControlPortalFrame(frame_Portal);
						portal.posX = -100;
						enemy1.posX = -100;
						enemy2.posX = -100;
						enemy3.posX = -100;
						continue;
					}
					else if (night) {
						night = false;
						desert = true;
						SDL_Delay(38);
						RenderScrollingBackground(OffsetSpeed_Bkgr, g_BackgroundTexture3, gRenderer);
						SDL_RenderPresent(gRenderer);
						SDL_RenderClear(gRenderer);
						SDL_Delay(38);
						RenderScrollingBackground(OffsetSpeed_Bkgr, g_BackgroundTexture2, gRenderer);
						SDL_RenderPresent(gRenderer);
						SDL_RenderClear(gRenderer);
						SDL_Delay(38);
						RenderScrollingBackground(OffsetSpeed_Bkgr, g_BackgroundTexture1, gRenderer);
						SDL_RenderPresent(gRenderer);
						SDL_RenderClear(gRenderer);
						SDL_Delay(38);
						RenderScrollingBackground(OffsetSpeed_Bkgr, g_BackgroundTexture3, gRenderer);
						SDL_RenderPresent(gRenderer);
						SDL_RenderClear(gRenderer);
						SDL_Delay(38);
						RenderScrollingBackground(OffsetSpeed_Bkgr, g_BackgroundTexture2, gRenderer);
						SDL_RenderPresent(gRenderer);
						SDL_RenderClear(gRenderer);
						SDL_Delay(38);
						ControlCharFrame(frame_Character);
						ControlBatFrame(frame_Enemy3);
						ControlGolemFrame(frame_Enemy1);
						ControlGolemFrame(frame_Enemy2);
						ControlPortalFrame(frame_Portal);
						portal.~Enemy();
						enemy1.posX = -100;
						enemy2.posX = -100;
						enemy3.posX = -100;
						continue;
					}
					else if (winter) {
						winter = false;
						night = true;	
						SDL_RenderClear(gRenderer);
						SDL_Delay(38);
						RenderScrollingBackground(OffsetSpeed_Bkgr, g_BackgroundTexture3, gRenderer);
						SDL_RenderPresent(gRenderer);
						SDL_RenderClear(gRenderer);
						SDL_Delay(38);
						RenderScrollingBackground(OffsetSpeed_Bkgr, g_BackgroundTexture2, gRenderer);
						SDL_RenderPresent(gRenderer);
						SDL_RenderClear(gRenderer);
						SDL_Delay(38);
						RenderScrollingBackground(OffsetSpeed_Bkgr, g_BackgroundTexture1, gRenderer);
						SDL_RenderPresent(gRenderer);
						SDL_RenderClear(gRenderer);
						SDL_Delay(38);
						RenderScrollingBackground(OffsetSpeed_Bkgr, g_BackgroundTexture3, gRenderer);
						SDL_RenderPresent(gRenderer);
						SDL_RenderClear(gRenderer);
						SDL_Delay(38);
						RenderScrollingBackground(OffsetSpeed_Bkgr, g_BackgroundTexture2, gRenderer);
						SDL_RenderPresent(gRenderer);
						SDL_RenderClear(gRenderer);
						SDL_Delay(38);
						ControlCharFrame(frame_Character);
						ControlBatFrame(frame_Enemy3);
						ControlGolemFrame(frame_Enemy1);
						ControlGolemFrame(frame_Enemy2);
						ControlPortalFrame(frame_Portal);
						portal.~Enemy();
						enemy1.posX = -100;
						enemy2.posX = -100;
						enemy3.posX = -100;
						continue;
					}
				}
				SDL_RenderPresent(gRenderer);
				ControlCharFrame(frame_Character);
				ControlBatFrame(frame_Enemy3);
				ControlGolemFrame(frame_Enemy1);
				ControlGolemFrame(frame_Enemy2);
				ControlPortalFrame(frame_Portal);	
			}
			
		}
		
	}

}
bool Game:: LoadMedia() {
	bool success = true;

	gMusic = Mix_LoadMUS("sound/bkgr_audio.wav");
	if (gMusic == nullptr)
	{
		LogError("Failed to load background music", MIX_ERROR);
		success = false;
	}

	gMenuMusic = Mix_LoadMUS("sound/menu_audio.wav");
	if (gMenuMusic == nullptr)
	{
		LogError("Failed to load menu music", MIX_ERROR);
		success = false;
	}

	gClick = Mix_LoadWAV("sound/mouse_click.wav");
	if (gClick == nullptr)
	{
		LogError("Failed to load mouse click sound", MIX_ERROR);
		success = false;
	}

	gJump = Mix_LoadWAV("sound/jump_sound.wav");
	if (gJump == nullptr)
	{
		LogError("Failed to load jumping sound", MIX_ERROR);
		success = false;
	}

	gLose = Mix_LoadWAV("sound/lose_sound.wav");
	if (gLose == nullptr)
	{
		LogError("Failed to load lose sound", MIX_ERROR);
		success = false;
	}

	else
	{
		gFont = TTF_OpenFont("font/PressStart2P.ttf", 15);
		if (gFont == NULL)
		{
			LogError("Failed to load font", MIX_ERROR);
			success = false;
		}
		else
		{
			if (!gText1Texture.LoadFromRenderedText("Your score: ", gFont, textColor, gRenderer))
			{
				std::cout << "Failed to render text1 texture" << std::endl;
				success = false;
			}

			if (!gText2Texture.LoadFromRenderedText("High score: ", gFont, textColor, gRenderer))
			{
				std::cout << "Failed to render text2 texture" << std::endl;
				success = false;
			}
			if (!gText3Texture.LoadFromRenderedText("Death: ", gFont, textColor, gRenderer))
			{
				std::cout << "Failed to render text3 texture" << std::endl;
				success = false;
			}

			if (!gMenuTexture.LoadFromFile("imgs/background/menu.png", gRenderer))
			{
				std::cout << "Failed to load menu image" << std::endl;
				success = false;
			}

			if (!gInstructionTexture.LoadFromFile("imgs/background/instruction.png", gRenderer))
			{
				std::cout << "Failed to load instruction image" << std::endl;
				success = false;
			}

			if (!gPlayButtonTexture.LoadFromFile("imgs/button/big_button/play_button.png", gRenderer))
			{
				std::cout << "Failed to load play_button image" << std::endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					gPlayButton[i].x = 150 * i;
					gPlayButton[i].y = 0;
					gPlayButton[i].w = 150;
					gPlayButton[i].h = 98;
				}
			}

			if (!gHelpButtonTexture.LoadFromFile("imgs/button/big_button/help_button.png", gRenderer))
			{
				std::cout << "Failed to load help_button image" << std::endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					gHelpButton[i].x = 150 * i;
					gHelpButton[i].y = 0;
					gHelpButton[i].w = 150;
					gHelpButton[i].h = 98;
				}
			}

			if (!gBackButtonTexture.LoadFromFile("imgs/button/big_button/back_button.png", gRenderer))
			{
				std::cout << "Failed to load back_button image" << std::endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					gBackButton[i].x = 100 * i;
					gBackButton[i].y = 0;
					gBackButton[i].w = 100;
					gBackButton[i].h = 78;
				}
			}

			if (!gExitButtonTexture.LoadFromFile("imgs/button/big_button/exit_button.png", gRenderer))
			{
				std::cout << "Failed to load exit_button image" << std::endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					gExitButton[i].x = 150 * i;
					gExitButton[i].y = 0;
					gExitButton[i].w = 150;
					gExitButton[i].h = 98;
				}
			}

			if (!gPauseButtonTexture.LoadFromFile("imgs/button/big_button/pause_button.png", gRenderer))
			{
				std::cout << "Failed to load pause_button image " << std::endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					gPauseButton[i].x = 22 * i;
					gPauseButton[i].y = 0;
					gPauseButton[i].w = 22;
					gPauseButton[i].h = 34;
				}
			}

			if (!gContinueButtonTexture.LoadFromFile("imgs/button/big_button/continue_button.png", gRenderer))
			{
				std::cout << "Failed to load continue_button image " << std::endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					gContinueButton[i].x = 22 * i;
					gContinueButton[i].y = 0;
					gContinueButton[i].w = 22;
					gContinueButton[i].h = 34;
				}
			}

			for (int i = 0; i < BACKGROUND_LAYER; ++i)
			{
				if (!g_BackgroundTexture1[i].LoadFromFile(SCENCE1[i].c_str(), gRenderer))
				{
					std::cout << "Failed to load background image" << std::endl;
					success = false;
				}
			}
			for (int i = 0; i < BACKGROUND_LAYER; ++i)
			{
				if (!g_BackgroundTexture2[i].LoadFromFile(SCENCE2[i].c_str(), gRenderer))
				{
					std::cout << "Failed to load background image" << std::endl;
					success = false;
				}
			}

			for (int i = 0; i < BACKGROUND_LAYER; ++i)
			{
				if (!g_BackgroundTexture3[i].LoadFromFile(SCENCE3[i].c_str(), gRenderer))
				{
					std::cout << "Failed to load background image" << std::endl;
					success = false;
				}
			}

			if (!gGroundTexture.LoadFromFile("imgs/background/ground.png", gRenderer))
			{
				std::cout << "Failed to load ground image" << std::endl;
				success = false;
			}
			if (!gLoseTexture.LoadFromFile("imgs/background/lose.png", gRenderer))
			{
				std::cout << "Failed to load lose image." << std::endl;
				success = false;
			}
		}
	}
	return success;
}
void Game::Close() {
	gMenuTexture.Free();
	gInstructionTexture.Free();
	gGroundTexture.Free();
	gPlayButtonTexture.Free();
	gHelpButtonTexture.Free();
	gExitButtonTexture.Free();
	gBackButtonTexture.Free();
	gPauseButtonTexture.Free();
	gContinueButtonTexture.Free();
	gLoseTexture.Free();
	gText1Texture.Free();
	gScoreTexture.Free();
	gText2Texture.Free();
	gText3Texture.Free();
	gHighScoreTexture.Free();
	gDeathCountTexture.Free();
	for (int i = 0; i < BACKGROUND_LAYER; ++i)
	{
		g_BackgroundTexture1[i].Free();
	}

	for (int i = 0; i < BACKGROUND_LAYER; ++i)
	{
		g_BackgroundTexture2[i].Free();
	}

	for (int i = 0; i < BACKGROUND_LAYER; ++i)
	{
		g_BackgroundTexture3[i].Free();
	}

	Mix_FreeMusic(gMusic);
	Mix_FreeMusic(gMenuMusic);
	Mix_FreeChunk(gClick);
	Mix_FreeChunk(gLose);
	Mix_FreeChunk(gJump);
	gMusic = nullptr;
	gMenuMusic = nullptr;
	gClick = nullptr;
	gLose = nullptr;
	gJump = nullptr;

	SDL_DestroyRenderer(gRenderer);
	gRenderer = nullptr;

	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;

	IMG_Quit();
	Mix_Quit();
	SDL_Quit();
}