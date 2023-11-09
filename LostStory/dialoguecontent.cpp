#include "dialoguecontent.h"

//¹ï¸Ü®Ø³]¸m
DialogueContent::DialogueContent() {

}
DialogueContent::DialogueContent(TTF_Font* font,Graphics& graphics ,
	std::string spokesman , std::string content,int skips,
	std::vector<DialogueOption> Option):
	_spokesman(spokesman),
	_content(content),
	_skip(skips),
	_dialogueOption(Option){
	SDL_Color color = { 255, 255, 255 };
	printf(_content.c_str());
	printf("\n");

	this->_surface = TTF_RenderUTF8_Solid(font, content.c_str(), color);
	this->_tileset = SDL_CreateTextureFromSurface(graphics.getRenderer(), this->_surface);

}
DialogueContent::~DialogueContent() {
}
void DialogueContent::update() {

}
void DialogueContent::draw(Graphics& graphics) {
	Vector2D destXY = Vector2D(400, 600);
	if (this->_spokesman == "player") destXY._x = 100;
	SDL_Rect destRect = {destXY._x, destXY._y,
			this->_content.size() * 16 ,32 };
	for (int i = 0; i < this->_dialogueOption.size();++i) {
		this->_dialogueOption[i].draw(900, 600 + i * 50);
	}
	graphics.blitSurface(this->_tileset ,NULL, &destRect);
}

const std::string DialogueContent::getCurrentSpoke() const {
	return this->_spokesman;
}

const int DialogueContent::getCurrentSkip() const {
	return this->_skip;
}