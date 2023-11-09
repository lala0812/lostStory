#pragma once
#include <string>
#include <map>
#include "SDL.h"
#include "SDL_image.h"
//繪圖
class Graphics {
public:
	Graphics(const char* wName,int x ,int y,int w,int h,Uint32 flags); //視窗繪製
	~Graphics();


	void flip();//填滿
	void clear(); //清除
	//繪製
	void blitSurface(SDL_Texture* texture, SDL_Rect* sourceRect, SDL_Rect* destinationRect);
	//讀取圖片
	SDL_Surface* loadImage(const std::string& filePath);
	//取得渲染
	SDL_Renderer* getRenderer() const;


private: 
	int a1 = 123;
	SDL_Window* _window;
	SDL_Renderer* _renderer;

	std::map<std::string, SDL_Surface*> _spriteSheets; //管理圖片
};
