#include "Item.h"


Item::Item() {}


Item::Item(Vector2D side) :
	Collision(side)
{}

Item::~Item() {}

void Item::draw(Graphics& graphics) {
	SDL_Rect sourceRect = { this->_source._x,this->_source._y,this->_source._height,_source._width };
	SDL_Rect positionRect = { this->_position._x,this->_position._y,this->_position._height,_position._width };

	graphics.blitSurface(this->_ItemName, &sourceRect, &positionRect);
}

void Item::update() {

}