#ifndef GAME_BASE_
#define GAME_BASE_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>

#define SDL_ERROR 1
#define IMG_ERROR 2
#define MIX_ERROR 3
#define TTF_ERROR 4

#define MIX_CHANNEL -1

#define TIME_MAX 1000
#define GROUND 400
#define MAX_HEIGHT 260

#define BASE_OFFSET_SPEED 0

#define SPEED_INCREASEMENT 1
#define SCORE_INCREASEMENT 1
#define TIME_INCREASEMENT 1
#define FRAME_INCREASEMENT 1

#define GROUND_SPEED 5
#define ENEMY_SPEED 5
#define MAX_ENEMY_WIDTH 100

#define IN_AIR_ENEMY 1
#define PORTAL 0
#define GOLEM 2
#define DINO 0
#define MINOTOUR1 1
#define MINOTOUR2 2
#define MINOTOUR3 3


#define SLOW_FRAME_CHAR 2
#define SLOW_FRAME_ENEMY 4

#define IS_REPEATITIVE -1
#define NOT_REPEATITIVE 0

#define SMALL_BUTTON 1
#define COMMON_BUTTON 2
const int WINTER = 0;
const int NIGHT = 1;
const int DESERT = 2;
const std::string WINDOW_TITLE = "Dino in jungle";

const int SCREEN_WIDTH = 928;
const int SCREEN_HEIGHT = 522;

const int COMMON_BUTTON_WIDTH = 130;
const int COMMON_BUTTON_HEIGHT = 45;
const int SMALL_BUTTON_WIDTH = 22;
const int SMALL_BUTTON_HEIGHT = 34;

const int PLAY_BUTON_POSX = 399;
const int PLAY_BUTTON_POSY= 392;
const int HELP_BUTTON_POSX = 389;
const int HELP_BUTTON_POSY = 293;
const int EXIT_BUTTON_POSX = 399;
const int EXIT_BUTTON_POSY = 440;
const int BACK_BUTTON_POSX = 31;
const int BACK_BUTTON_POSY = 29;
const int PAUSE_BUTTON_POSX = 31;
const int PAUSE_BUTTON_POSY = 29;
const int CONTINUE_BUTTON_POSX = 31;
const int CONTINUE_BUTTON_POSY = 29;

const int TEXT_1_POSX = 670;
const int TEXT_1_POSY = 20;
const int TEXT_2_POSX = 670;
const int TEXT_2_POSY = 80;
const int TEXT_3_POSX = 670;
const int TEXT_3_POSY = 140;
const int SCORE_POSX = 845;
const int SCORE_POSY = 20;
const int HIGH_SCORE_POSX = 845;
const int HIGH_SCORE_POSY = 80;
const int DEADTH_COUNT_POSX = 770;
const int DEADTH_COUNT_POSY = 140;

const double LAYER_1_SPEED = 0.0;
const double LAYER_2_SPEED = 0.25; 
const double LAYER_3_SPEED = 0.5;
const double LAYER_4_SPEED = 0.75;
const double LAYER_5_SPEED = 1.0;
const double LAYER_6_SPEED = 1.25;
const double LAYER_7_SPEED = 1.5;
const double LAYER_8_SPEED = 1.75;
const double LAYER_9_SPEED = 2.0;

const int RUNNING_FRAMES = 18;
const int FLYING_FRAMES = 5;
const int BACKGROUND_LAYER = 9;

enum ButtonSprite
{
	BUTTON_MOUSE_OUT = 0,
	BUTTON_MOUSE_OVER = 1,
	BUTTON_TOTAL = 2
};

void LogError(std::string msg, int error_code = SDL_ERROR);

#endif // !GAME_LIB_