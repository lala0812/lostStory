#include "tile.h"
#include "game.h"
#include "SDL.h"

Tile::Tile() {}

Tile::Tile(SDL_Texture* tileset, Vector2D tilesetPosition, Vector2D position) :
	_tileset(tileset),
	_tilesetPosition(tilesetPosition),
	_position(position) {

}

Tile::~Tile() {
	//
}

void Tile::update() {
	
}

void Tile::draw(Graphics& graphics) {

	SDL_Rect destRect = { this->_position._x - CGlobals::camera._x, this->_position._y - CGlobals::camera._y,
			this->_position._width,this->_position._height };
	SDL_Rect sourceRect = { this->_tilesetPosition._x, this->_tilesetPosition._y, this->_tilesetPosition._width, this->_tilesetPosition._height };

	graphics.blitSurface(this->_tileset, &sourceRect, &destRect);

}
void Tile::drawDialogue(Graphics& graphics) {

	SDL_Rect destRect = { this->_position._x , this->_position._y,
			this->_position._width,this->_position._height };
	SDL_Rect sourceRect = { this->_tilesetPosition._x, this->_tilesetPosition._y, this->_tilesetPosition._width, this->_tilesetPosition._height };

	graphics.blitSurface(this->_tileset, &sourceRect, &destRect);

}