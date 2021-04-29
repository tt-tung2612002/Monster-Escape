#include "Character.h"
#include "Enemy.h"
int minHeight = 410;
Character::Character()
{
	posX = SCREEN_WIDTH - 700;
	posY = GROUND;
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

void Character::Render(SDL_Rect* currentClip, SDL_Renderer *gRenderer, LTexture gCharacterTexture)
{
	gCharacterTexture.Render(posX, posY, gRenderer, currentClip);
}

int Character::GetPosX()
{
	return posX;
}

int Character::GetPosY()
{
	return posY;
}