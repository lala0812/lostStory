#pragma once
#include "graphics.h"
#include "globals.h"
#include "SDL_ttf.h"
#include <vector>

struct SDL_Surface;
struct SDL_Texture;
class Graphics;
struct DialogueOption;

//對話框設置
class DialogueContent {
public:
	DialogueContent();
	DialogueContent(TTF_Font* font, Graphics& graphics ,
		std::string spokesman, std::string content , int skips,
		std::vector<DialogueOption> Option);
	~DialogueContent();
	void update();
	void draw(Graphics& graphics);
	const std::string getCurrentSpoke() const;
	const int getCurrentSkip() const;

	inline SDL_Texture* getTexture() { return this->_tileset; }
	inline SDL_Surface* getSurface() { return this->_surface; }
	inline std::vector<DialogueOption>& getDialogueOptions() { return this->_dialogueOption; }
	
protected:
	std::string _spokesman; //說話者
	std::string _content; //說話內容
	SDL_Surface* _surface; //表現的紋理
	SDL_Texture* _tileset;
	Vector2D _position;

	std::vector<DialogueOption> _dialogueOption;
	
	int _skip;
};

struct DialogueOption {
	DialogueOption(Graphics graphics):_graphics(graphics) {}
	DialogueOption(TTF_Font* font,Graphics& graphics,const std::string Content, const std::string Plot):
		content(Content),
		plot(Plot),
		_font(font),
		_graphics(graphics){
		SDL_Color color = { 255, 255, 255 };
		this->_surface = TTF_RenderUTF8_Solid(_font, content.c_str(), color);
		this->_tileset = SDL_CreateTextureFromSurface(_graphics.getRenderer(), this->_surface);

	}

	void setColorBlack() {
		SDL_Color color = { 255, 255, 255 };
		this->_surface = TTF_RenderUTF8_Solid(_font, content.c_str(), color);
		this->_tileset = SDL_CreateTextureFromSurface(_graphics.getRenderer(), this->_surface);
	}

	void setColorRed() {
		SDL_Color color = { 255, 0, 0 };
		this->_surface = TTF_RenderUTF8_Solid(_font, content.c_str(), color);
		this->_tileset = SDL_CreateTextureFromSurface(_graphics.getRenderer(), this->_surface);
	}

	void draw( int x ,int y ) {

		SDL_Rect optiondestRect = { x,y,this->content.size() * 16 ,32 };
		_graphics.blitSurface(this->_tileset, NULL, &optiondestRect);
	}
	TTF_Font* _font;
	Graphics& _graphics;
	std::string content;
	std::string plot;
	SDL_Surface* _surface; //表現的紋理
	SDL_Texture* _tileset;
	int skip;
};
