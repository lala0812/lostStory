#pragma once
//�a��ø�s
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
		if (TTF_Init() < 0) //Ū����r�]
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
	void LoadMap(std::string mapName,Graphics& graphics); //Ū���a��

	void LoadDialogueIMG(std::string fileName, Graphics& graphics); //Ū����ܮ�

	void LoadDialogue(std::string dialogue,Graphics& graphics,int dialogueId); //Ū����ܤ��e
	void resetMap(); //�M���a��

	void update();
	void draw(Graphics& graphics);
	void drawDialogue(Graphics& graphics);

	std::vector<Collision> checkObjectCollision(const Collision& other); //�ˬd�I������
	//�ˬd�ǰe�I
	std::vector<TouchSend> checkObjectTouch(const Collision& other, Graphics& graphics);
	//�ˬd��ܨƥ�
	bool checkObjectDialogue(const Collision& other);
	//�Хܷ�e���a�ҿ蠟��ܿﶵ
	void handleDialogueOption(bool UpOrDown);

	void destoryFont();
private:
	TTF_Font* font; //��r

	static bool _isDialogue; //�P�w�O�_�b���
	static int flow; //�P�w��ܬy�{
	static int CurrentOption;//��e��ܿﶵ

	std::vector<Tile> _staticObject; //�a���R�A����
	std::map<std::string ,std::vector<Tile>> _ItemObject;

	std::map<std::string ,std::vector<Tile>> _staticDialogueObject; //��ܮت���

	std::vector<Tileset> _tilesets; //Ū�����Ϥ���

	std::map<std::string,Item> _collisionItems;//mine

	std::vector<CollisionObject> _collisionObjects; //�a�ϸI������
	std::vector<TouchSend> _touchObjects; //���I����

	//(NPC�W,��ܤ��e)
	std::map <std::string, std::vector<DialogueContent>> _dialogueContents; 
	
	//��ܮت�Ĳ�o�����m
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
