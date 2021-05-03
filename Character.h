#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "LTexture.h"

#define JUMP 1
#define FALL 2
#define RUN	0
#define DOWN 3

class Character
{
public:
	int posX, posY;
	static const int JUMP_SPEED = 9;
	static const int FALL_SPEED = 9;

	Character();
	~Character() {}
	bool OnGround();

	void HandleEvent(SDL_Event& e, Mix_Chunk *gJump);
	void GenerateCharacter(Character& character,
		SDL_Rect* gCharacterclips,
		SDL_Renderer* gRenderer);
	void Move();
	void LoadFromFile(std::string path, SDL_Renderer* gRenderer);
	void Render(SDL_Renderer *gRenderer, SDL_Rect* currentClip = nullptr);

	int GetPosX();

	int GetPosY();

private:
	SDL_Texture* CharacterTexture = nullptr;
	
	int status;
};

#endif // !CHARACTER_H_