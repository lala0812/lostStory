#pragma once
#include "graphics.h"
#include "Item.h"

#include "SDL.h"
#include <vector>
class Bag {
public:
	Bag();
	Bag(Graphics& graphics, const std::string fileName);
	~Bag();
	void drawItem(Graphics& graphics);
	void drawBag(Graphics& graphics);
	void update();
	bool openBag();
	
	bool checkOpenBag;
	std::vector<Item>_bagSize;
private:
	SDL_Surface* _surface;
	SDL_Texture* _bagTexture;

};