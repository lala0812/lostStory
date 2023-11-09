#pragma once
#include "graphics.h"
#include "SDL.h"
#include "globals.h"
#include "collision.h"

class Sprite {
public:
	Sprite();
	Sprite(Graphics& graphics, const std::string fileName,Vector2D source,Vector2D destination);
	~Sprite();

	void update();
	void draw(Graphics& graphics , int x ,int y);

	const collisionSide::Sides getCollisionSide(Collision& other) const;
	const Collision getCollisionBox() const;

protected:
	SDL_Rect _sourceRect;
	SDL_Texture* _spriteSheet;
	
	Vector2D pos;
	Collision _collision;
	
};
