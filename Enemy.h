#ifndef ENEMY_H_
#define ENEMY_H_

#include "LTexture.h"

#define ENEMY_MAX_HEIGHT 240
#define ENEMY_MIN_HEIGHT 270

#define ENEMY_POSITION_RANGE 250
#define ENEMY1_RANGE 100
#define ENEMY2_RANGE 350
#define ENEMY3_RANGE 500


class Enemy
{
public:
	int type;
	int posX, posY;
	std::string pathID;
	Enemy(int _type = 0);
	
	~Enemy();

	void LoadFromFile(std::string path, SDL_Renderer* gRenderer);
	void LoadFromProperties(SDL_Renderer* gRenderer);
	void GenerateBat(Enemy& enemy,
		SDL_Rect* gEnemyClips,
		SDL_Renderer* gRenderer);
	void GeneratePortal(Enemy& enemy,
		SDL_Rect* gPortalClips,
		SDL_Renderer* gRenderer);
	void GenerateGolem(Enemy& enemy,
		SDL_Rect(&gEnemyClips)[12],
		SDL_Renderer* gRenderer);
	void Move(int acceleration);
	void Render(SDL_Renderer* gRenderer, SDL_Rect* currentClip = nullptr);

	int GetType();

	int GetSpeed(const int& acceleration);

	int GetPosX();

	int GetPosY();

	int GetWidth();

	int GetHeight();
private:
	int eWidth, eHeight;
	SDL_Texture *EnemyTexture;
};

#endif // !ENEMY_H_