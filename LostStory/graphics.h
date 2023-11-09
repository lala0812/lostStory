#pragma once
#include <string>
#include <map>
#include "SDL.h"
#include "SDL_image.h"
//ø��
class Graphics {
public:
	Graphics(const char* wName,int x ,int y,int w,int h,Uint32 flags); //����ø�s
	~Graphics();


	void flip();//��
	void clear(); //�M��
	//ø�s
	void blitSurface(SDL_Texture* texture, SDL_Rect* sourceRect, SDL_Rect* destinationRect);
	//Ū���Ϥ�
	SDL_Surface* loadImage(const std::string& filePath);
	//���o��V
	SDL_Renderer* getRenderer() const;


private: 
	int a1 = 123;
	SDL_Window* _window;
	SDL_Renderer* _renderer;

	std::map<std::string, SDL_Surface*> _spriteSheets; //�޲z�Ϥ�
};
