#pragma once
#include "globals.h"
#include "graphics.h"
#include <SDL.h>
#include "collision.h"

class Item :public Collision{
public:
	Item();

	Item(Vector2D side);

	~Item();

	void draw(Graphics& graphics);
	void update();

private:
	SDL_Texture* _ItemName;
	Vector2D _source;
	Vector2D _position;
};