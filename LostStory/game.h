#pragma once
#include "graphics.h"
#include "player.h"
#include "SDL.h"

#include "bag.h"
#include "globals.h"
#include "level.h"
#include "collisionobject.h"

class Game {
public:
	Game();
	~Game();

	//遊戲的整個進行
	void gameLoop(); 

	//遊戲進行時每一偵所更新的內容
	void update();

	//遊戲角色的事件控制
	void handleEvents();

	//遊戲內物件的繪製
	void draw(Graphics& graphics);

private:

	//遊戲觸發任何事件的冷卻
	int coolDown;

	//判斷遊戲是否運行
	bool _isRunning;

	//角色物件
	Player _player;

	//地圖及NPC等物件
	Level _level;

	Bag _bag;
};
