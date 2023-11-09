#include "graphics.h"

Graphics::Graphics(const char* wName, int x, int y, int w, int h, Uint32 flags) {
	_window = SDL_CreateWindow(wName, x, y,
		w, h, flags);
	_renderer = SDL_CreateRenderer(_window, -1, 0);
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
}

Graphics::~Graphics() {
	SDL_DestroyWindow(this->_window);
	SDL_DestroyRenderer(this->_renderer);
	for (auto& c : this->_spriteSheets) {
		SDL_FreeSurface(c.second);
	}
}

void Graphics::flip() {//�e�{��V
	SDL_RenderPresent(this->_renderer);
}

void Graphics::clear() {//�M����V
	SDL_RenderClear(this->_renderer);
}
//ø�s
void Graphics::blitSurface(SDL_Texture* texture, SDL_Rect* sourceRect, SDL_Rect* destinationRect) {
	SDL_RenderCopy(this->_renderer, texture, sourceRect, destinationRect);
}

//Ū���Ӥ�
SDL_Surface* Graphics::loadImage(const std::string& filePath) {
	if (this->_spriteSheets.count(filePath) == 0) { //�P�w�O�_Ū�L
		this->_spriteSheets[filePath] = IMG_Load(filePath.c_str());
	}
	return this->_spriteSheets[filePath];
}


SDL_Renderer* Graphics::getRenderer() const {
	return this->_renderer;
}
