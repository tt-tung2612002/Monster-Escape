#include "Character.h"
#include "Enemy.h"
int minHeight = 360;
Character::Character(int type_)
{
	type = type_;
	posX = SCREEN_WIDTH - 700;
	posY = GROUND;
	pathID = "imgs/character/minotour1.png";
	status = 0;
}

bool Character::OnGround()
{
	return posY == GROUND;
}

void Character::HandleEvent(SDL_Event& e, Mix_Chunk *gJump)
{
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_UP:
			{
				if (OnGround())
				{
					Mix_PlayChannel(MIX_CHANNEL, gJump, NOT_REPEATITIVE);
					status = JUMP;
				}
			}
			case SDLK_RIGHT:
			{
			
			}
			case SDLK_DOWN:
			{
				//status = DOWN;
			}
		
		}
	}
	if (e.type == SDL_KEYUP )
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_UP:
			{
				if (posY <= minHeight)
					status = FALL;
			}
		}
	}
} 

void Character::Move()
{
	if (status == JUMP && posY >= MAX_HEIGHT)
	{
		posY += -JUMP_SPEED;
	}
	if (posY <= MAX_HEIGHT)
	{
		status = FALL;
	}
	if (status == FALL && posY < GROUND)
	{
		posY += FALL_SPEED ;
	}
}
void Character::GenerateCharacter(Character& character,SDL_Rect* gCharacterClips, SDL_Renderer* gRenderer) {
	character.LoadFromProperties(gRenderer);
	for (int i = 0; i < 18; i++) {
		gCharacterClips[i].x = 57 * i;
		gCharacterClips[i].y = 0;
		gCharacterClips[i].w = 57;
		gCharacterClips[i].h = 57;
	}
}
void Character::LoadFromFile(std::string path, SDL_Renderer* gRenderer) {
	SDL_Texture* tmpTexture = nullptr;
	SDL_Surface* tmpSurface = IMG_Load(path.c_str());
	SDL_SetColorKey(tmpSurface, SDL_TRUE, SDL_MapRGB(tmpSurface->format, 0, 255, 255));
	tmpTexture = SDL_CreateTextureFromSurface(gRenderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	CharacterTexture = tmpTexture;
}
void Character::LoadFromProperties(SDL_Renderer* gRenderer) {
	SDL_Texture* tmpTexture = nullptr;
	SDL_Surface* tmpSurface = IMG_Load(pathID.c_str());
	if (tmpSurface == nullptr)
	{
		LogError("Can not load image.", IMG_ERROR);
	}
	else
	{
		SDL_SetColorKey(tmpSurface, SDL_TRUE, SDL_MapRGB(tmpSurface->format, 0, 255, 255));

		tmpTexture = SDL_CreateTextureFromSurface(gRenderer, tmpSurface);
		if (tmpTexture == nullptr)
		{
			LogError("Can not create texture from surface.", SDL_ERROR);
		}
		SDL_FreeSurface(tmpSurface);
	}
	CharacterTexture = tmpTexture;
}
void Character::Render(SDL_Renderer *gRenderer,SDL_Rect* currentClip)
{
	SDL_Rect renderSpace = {posX, posY, 57, 57 };
	renderSpace.w = currentClip->w + 20;
	renderSpace.h = currentClip->h + 20;
	SDL_RenderCopy(gRenderer, CharacterTexture, currentClip, &renderSpace);
}

int Character::GetPosX()
{
	return posX;
}

int Character::GetPosY()
{
	return posY;
}