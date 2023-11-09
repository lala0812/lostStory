#pragma once
//地圖繪製
#include <string>
#include <vector>
#include <map>
#include "globals.h"
#include "player.h"
#include "graphics.h"
#include "tile.h"
#include "collisionobject.h"
#include "touchsend.h"
#include "dialoguecontent.h"
#include "Item.h"
#include "SDL_ttf.h"

struct Tileset;

class Level {
public:
	friend class Game;
	Level() {
		if (TTF_Init() < 0) //讀取文字包
			printf("ERROR:TTF_Init false!!!!!!!!!!");
		this->font = TTF_OpenFont("assets/fonts/DroidSansFallback.ttf", 24);
		if (!this->font) {
			printf("Failed to load font:%p\n ",TTF_GetError());
		}

	}
	~Level() {
		//TTF_CloseFont(this->font);
		//TTF_Quit();
	}
	void LoadMap(std::string mapName,Graphics& graphics); //讀取地圖

	void LoadDialogueIMG(std::string fileName, Graphics& graphics); //讀取對話框

	void LoadDialogue(std::string dialogue,Graphics& graphics,int dialogueId); //讀取對話內容
	void resetMap(); //清除地圖

	void update();
	void draw(Graphics& graphics);
	void drawDialogue(Graphics& graphics);

	std::vector<Collision> checkObjectCollision(const Collision& other); //檢查碰撞物件
	//檢查傳送點
	std::vector<TouchSend> checkObjectTouch(const Collision& other, Graphics& graphics);
	//檢查對話事件
	bool checkObjectDialogue(const Collision& other);
	//標示當前玩家所選之對話選項
	void handleDialogueOption(bool UpOrDown);

	void destoryFont();
private:
	TTF_Font* font; //文字

	static bool _isDialogue; //判定是否在對話
	static int flow; //判定對話流程
	static int CurrentOption;//當前對話選項

	std::vector<Tile> _staticObject; //地圖靜態物件
	std::map<std::string ,std::vector<Tile>> _ItemObject;

	std::map<std::string ,std::vector<Tile>> _staticDialogueObject; //對話框物件

	std::vector<Tileset> _tilesets; //讀取的圖片源

	std::map<std::string,Item> _collisionItems;//mine

	std::vector<CollisionObject> _collisionObjects; //地圖碰撞物件
	std::vector<TouchSend> _touchObjects; //傳點物件

	//(NPC名,對話內容)
	std::map <std::string, std::vector<DialogueContent>> _dialogueContents; 
	
	//對話框的觸發物件位置
	std::map<std::string,std::vector<CollisionObject>> _dialogueObjects;
	
	
	Vector2D _mapSize;
	Vector2D _mapPixelSize;
};

struct Tileset { //:)
	SDL_Texture* Texture;
	int FirstGid;
	Vector2D _size;
	Tileset() {
		this->FirstGid = -1;
	}
	Tileset(SDL_Texture* texture, int firstGid , Vector2D Size):
		Texture(texture),
		FirstGid(firstGid),
		_size(Size){

	}
	~Tileset() {
		//SDL_DestroyTexture(Texture);
	}
};
