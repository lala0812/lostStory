#include "bag.h"


struct SDL_Texture;
class Graphics;

Bag::Bag() {}

Bag::Bag(Graphics& graphics, const std::string fileName):
	_bagSize(8),
	checkOpenBag(false)
{
	this->_surface = graphics.loadImage(fileName);
	this->_bagTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), this->_surface);
}

Bag::~Bag() {}

void Bag::drawBag(Graphics& graphics) {
	if (this->checkOpenBag) {
		for (int i = 0; i < _bagSize.size(); ++i) {
			SDL_Rect _source = { 0,0,16,16 };
			SDL_Rect _position = { 0 + i * 135,0,135,135 };
			graphics.blitSurface(this->_bagTexture, &_source, &_position);
		}
	}
	else {}
		
}

void Bag::drawItem(Graphics& graphics) {
	
}
void Bag::update() {

}

bool Bag::openBag() {
	if(checkOpenBag == false)
		return this->checkOpenBag = true;
	return this->checkOpenBag = false;
}