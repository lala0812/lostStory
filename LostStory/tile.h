#pragma once
#include "graphics.h"
#include "globals.h"

struct SDL_Texture;
class Graphics;


class Tile {
public:
	Tile();
	Tile(SDL_Texture* tileset, Vector2D tilesetPosition, Vector2D position);
	~Tile();
	void update();
	void draw(Graphics& graphics);
	void drawDialogue(Graphics& graphics);
	const SDL_Texture* getTexture() const {
		return this->_tileset;
	}
protected:
	SDL_Texture* _tileset;
	Vector2D _tilesetPosition;
	Vector2D _position;
};
