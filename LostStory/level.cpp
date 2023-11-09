#include "level.h"
#include "tinyxml2.h"
#include <algorithm>
#include <sstream>
#include <cmath>

using namespace tinyxml2; 

void Level::LoadMap(std::string fileName , Graphics& graphics) { //讀取Map
	this->resetMap();	//刷新Leve地圖等繪製
	XMLDocument doc; //XML物件
	std::stringstream ss;

	ss << "assets/map/" << fileName << ".tmx"; 
	doc.LoadFile(ss.str().c_str()); //讀取XML檔

	XMLElement* mapNode = doc.FirstChildElement("map");
	int width, height;
	mapNode->QueryIntAttribute("width", &width);//設置地圖長寬
	mapNode->QueryIntAttribute("height", &height);
	_mapSize = Vector2D(0, 0, width, height);

	int tileWidth, tileHeight;
	mapNode->QueryIntAttribute("tilewidth", &tileWidth);//單個圖塊長寬
	mapNode->QueryIntAttribute("tileheight", &tileHeight);
	_mapPixelSize = Vector2D(0, 0, tileWidth, tileHeight);
	XMLElement* pTileset = mapNode->FirstChildElement("tileset");
	if (pTileset != NULL) { //讀取所有圖片
		while (pTileset) {
			const std::string source = pTileset->FirstChildElement("image")->Attribute("source");
			std::stringstream ss;
			ss << source;

			int firstgid;
			pTileset->QueryIntAttribute("firstgid", &firstgid);
			SDL_Texture* tex = SDL_CreateTextureFromSurface(graphics.getRenderer(),
				graphics.loadImage(ss.str()));
			int gidWidth, gidHeight;
			pTileset->FirstChildElement("image")->QueryIntAttribute("width", &gidWidth);
			pTileset->FirstChildElement("image")->QueryIntAttribute("height", &gidHeight);
			this->_tilesets.push_back(Tileset(tex, firstgid , Vector2D(0,0,gidWidth,gidHeight)));
			pTileset = pTileset->NextSiblingElement("tileset");
		}
	}

	XMLElement* pBackground = mapNode->FirstChildElement("layer");
	if (pBackground != NULL) { //讀取每個圖塊所要放上的圖片
		while (pBackground) {
			int bWidth, bHeight;
			pBackground->QueryIntAttribute("width", &bWidth);
			pBackground->QueryIntAttribute("height", &bHeight);
			XMLElement* pData = pBackground->FirstChildElement("data");
			XMLElement* pName = pBackground->FirstChildElement("name");
			if (pData != NULL) {
				while (pData) {
					XMLElement* pTile = pData->FirstChildElement("tile");
					if (pTile != NULL) {
						for (int i = 0; i < bHeight; ++i) {
							for (int j = 0; j < bWidth; ++j) {
								int gid = 0;
								pTile->QueryIntAttribute("gid", &gid);
								if (gid == 0) {
									pTile = pTile->NextSiblingElement("tile");
									continue;
								}
								int szW = (this->_tilesets.back()._size._width) / 32;
								int y = (gid-1) / szW;
								int x = (gid-1) % szW;
								//if (gid >= 83) {
								//	this->_ItemObject                       //mine
								//}
								this->_staticObject.push_back(Tile(this->_tilesets.back().Texture,
									Vector2D((x)*tileWidth, (y)*tileHeight),
									Vector2D(j * tileWidth, i * tileHeight)));
								
								pTile = pTile->NextSiblingElement("tile");
							}
							if (pTile == NULL) break;
						}
						
					}
					pData = pData->NextSiblingElement("data");
				}
			}
			pBackground = pBackground->NextSiblingElement("layer");
		}
	}
	//讀取碰撞物
	XMLElement* pObjectgroup = mapNode->FirstChildElement("objectgroup");
	if (pObjectgroup != NULL) {
		while (pObjectgroup) {
			std::string Name = pObjectgroup->Attribute("name");
			if (Name == "collision") {
				XMLElement* pObject = pObjectgroup->FirstChildElement("object");
				if (pObject != NULL) {
					while (pObject) {
						Vector2D position;
						pObject->QueryFloatAttribute("x", &(position._x));
						pObject->QueryFloatAttribute("y", &(position._y));
						pObject->QueryIntAttribute("width", &(position._width));
						pObject->QueryIntAttribute("height", &(position._height));
						this->_collisionObjects.push_back(position);
						//載入碰撞物
						pObject = pObject->NextSiblingElement("object");
					}
				}
			}//讀取傳送點
			else if (Name == "touch") {
				XMLElement* pObject = pObjectgroup->FirstChildElement("object");
				if (pObject != NULL) {
					while (pObject) {
						Vector2D position;
						Vector2D sendPosition;
						const std::string pMapName = pObject->Attribute("name");
						pObject->QueryFloatAttribute("x", &(position._x));
						pObject->QueryFloatAttribute("y", &(position._y));
						pObject->QueryIntAttribute("width", &(position._width));
						pObject->QueryIntAttribute("height", &(position._height));
						pObject->QueryFloatAttribute("sendx", &(sendPosition._x));
						pObject->QueryFloatAttribute("sendy", &(sendPosition._y));
						this->_touchObjects.push_back(TouchSend(position,pMapName,sendPosition));

						pObject = pObject->NextSiblingElement("object");
					}
				}
			}
			else if (Name == "dialogue") {
				XMLElement* pObject = pObjectgroup->FirstChildElement("object");
				if (pObject != NULL) {
					while (pObject) {
						Vector2D position;
						const std::string pNPCName = pObject->Attribute("name");
						pObject->QueryFloatAttribute("x", &(position._x));
						pObject->QueryFloatAttribute("y", &(position._y));
						pObject->QueryIntAttribute("width", &(position._width));
						pObject->QueryIntAttribute("height", &(position._height));
						this->_dialogueObjects[pNPCName].push_back(position);
						this->LoadDialogue(pNPCName, graphics, 1);
						pObject = pObject->NextSiblingElement("object");
					}
				}
			}
			else if (Name == "Item") {
				XMLElement* pObject = pObjectgroup->FirstChildElement("object");
				if (pObject != NULL) {
					while (pObject) {
						Vector2D position;
						const std::string pItemName = pObject->Attribute("name");
						pObject->QueryFloatAttribute("x", &(position._x));
						pObject->QueryFloatAttribute("y", &(position._y));
						pObject->QueryIntAttribute("width", &(position._width));
						pObject->QueryIntAttribute("height", &(position._height));
						this->_collisionItems[pItemName]=Item(position);
						this->LoadDialogue(pItemName, graphics, 1);
						pObject = pObject->NextSiblingElement("object");
					}
				}
			
			
			}
			pObjectgroup = pObjectgroup->NextSiblingElement("objectgroup");
		}
	}
	
}

//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------

void Level::LoadDialogueIMG(std::string fileName, Graphics& graphics) {
	XMLDocument doc;
	std::stringstream ss;

	ss << "assets/map/" << fileName << ".tmx";
	doc.LoadFile(ss.str().c_str());

	XMLElement* mapNode = doc.FirstChildElement("map");
	int width, height;
	mapNode->QueryIntAttribute("width", &width);
	mapNode->QueryIntAttribute("height", &height);
	
	int tileWidth, tileHeight;
	mapNode->QueryIntAttribute("tilewidth", &tileWidth);
	mapNode->QueryIntAttribute("tileheight", &tileHeight);
	XMLElement* pTileset = mapNode->FirstChildElement("tileset");
	if (pTileset != NULL) {
		while (pTileset) {
			const std::string source = pTileset->FirstChildElement("image")->Attribute("source");
			std::stringstream ss;
			ss << source;

			int firstgid;
			pTileset->QueryIntAttribute("firstgid", &firstgid);
			SDL_Texture* tex = SDL_CreateTextureFromSurface(graphics.getRenderer(),
				graphics.loadImage(ss.str()));
			int gidWidth, gidHeight;
			pTileset->FirstChildElement("image")->QueryIntAttribute("width", &gidWidth);
			pTileset->FirstChildElement("image")->QueryIntAttribute("height", &gidHeight);
			this->_tilesets.push_back(Tileset(tex, firstgid, Vector2D(0, 0, gidWidth, gidHeight)));
			pTileset = pTileset->NextSiblingElement("tileset");
		}
	}
	XMLElement* pBackground = mapNode->FirstChildElement("layer");
	if (pBackground != NULL) {
		while (pBackground) {
			int bWidth, bHeight;
			pBackground->QueryIntAttribute("width", &bWidth);
			pBackground->QueryIntAttribute("height", &bHeight);
			XMLElement* pData = pBackground->FirstChildElement("data");
			if (pData != NULL) {
				while (pData) {
					XMLElement* pTile = pData->FirstChildElement("tile");
					if (pTile != NULL) {
						for (int i = 0; i < bHeight; ++i) {
							for (int j = 0; j < bWidth; ++j) {
								int gid = 0;
								pTile->QueryIntAttribute("gid", &gid);
								if (gid == 0) {
									pTile = pTile->NextSiblingElement("tile");
									continue;
								}
								int szW = (this->_tilesets.back()._size._width) / 32;
								int y = (gid - 1) / szW;
								int x = (gid - 1) % szW;
								this->_staticDialogueObject[fileName].push_back(Tile(this->_tilesets.back().Texture,
									Vector2D((x)*tileWidth, (y)*tileHeight),
									Vector2D(j * tileWidth, i * tileHeight)));
								pTile = pTile->NextSiblingElement("tile");
							}
							if (pTile == NULL) break;
						}

					}
					pData = pData->NextSiblingElement("data");
				}
			}
			pBackground = pBackground->NextSiblingElement("layer");
		}
	}
}

void Level::LoadDialogue(std::string dialogueName, Graphics& graphics , int dialogueId) {
	XMLDocument doc;
	std::stringstream ss;

	ss << "assets/dialogue/" << dialogueName << ".tmx";
	doc.LoadFile(ss.str().c_str());

	XMLElement* dialogueNode = doc.FirstChildElement("dialogue");
	if (dialogueNode != NULL) {
		XMLElement* pdata = dialogueNode->FirstChildElement("data");
		if (pdata != NULL) {
			int gid;
			while (pdata) {
				pdata->QueryIntAttribute("id", &gid);
				if (gid == dialogueId) {
					XMLElement* pDialogue = pdata->FirstChildElement("dialogue");
					if (pDialogue != NULL) {
						while (pDialogue) {
							const std::string spokesman = pDialogue->Attribute("name");
							const std::string content = pDialogue->Attribute("content");
							int skips = 1,options = 0;
							pDialogue->QueryIntAttribute("skip", &skips);
							pDialogue->QueryIntAttribute("option", &options);
							if (font != NULL) {
								if (options != 0) {
									std::vector<DialogueOption> dialogueOptions;
									XMLElement* pOption = pDialogue->FirstChildElement("option");
									while(pOption){
										std::string Ocontent = pOption->Attribute("content");
										std::string Oplot = pOption->Attribute("plot");
										dialogueOptions.push_back(DialogueOption(this->font,graphics,Ocontent, Oplot));
										pOption = pOption->NextSiblingElement("option");
									}
									dialogueOptions[0].setColorRed();
									this->_dialogueContents[dialogueName].push_back(
										DialogueContent(this->font, graphics, spokesman, content, skips, dialogueOptions));
								}
								else {
									this->_dialogueContents[dialogueName].push_back(
										DialogueContent(this->font, graphics, spokesman, content, skips,std::vector<DialogueOption>()));
								}
							}
							if (this->_staticDialogueObject[spokesman].empty()) {
								this->LoadDialogueIMG(spokesman, graphics);
							}
							pDialogue = pDialogue->NextSiblingElement("dialogue");
						}
					}
				}
				pdata = pdata->NextSiblingElement("data");
			}
		}
	}
	
}

void Level::resetMap() {
	/*
	std::vector<Tile> _staticObject; //地圖靜態物件
	std::map<std::string ,std::vector<Tile>> _staticDialogueObject; //對話框物件

	std::vector<Tileset> _tilesets; //讀取的圖片源

	std::vector<CollisionObject> _collisionObjects; //地圖碰撞物件
	std::vector<TouchSend> _touchObjects; //傳點物件

	//(NPC名,對話內容)
	std::map <std::string, std::vector<DialogueContent>> _dialogueContents; 

	//對話框的觸發物件位置
	std::map<std::string,std::vector<CollisionObject>> _dialogueObjects;
	*/
	for (auto& c : _tilesets) {
		SDL_DestroyTexture(c.Texture);
	}
	
	this->_tilesets.clear();

	for (auto& c : this->_dialogueContents) {
		for (auto &c2 : c.second) {
			for (auto &c3 : c2.getDialogueOptions()) {
				SDL_DestroyTexture(c3._tileset);
				SDL_FreeSurface(c3._surface);
			}
			SDL_DestroyTexture(c2.getTexture());
			SDL_FreeSurface(c2.getSurface());
		}
	}
	this->_dialogueContents.clear();

	this->_staticObject.clear();
	this->_staticDialogueObject.clear();


	this->_collisionObjects.clear();
	this->_touchObjects.clear();
	this->_dialogueObjects.clear();

}

void Level::update() { //目前無工作
	for (int i = 0; i < this->_staticObject.size(); ++i) {
		this->_staticObject.at(i).update();
	}
	for (int i = 0; i < this->_collisionObjects.size(); ++i) {
		this->_collisionObjects.at(i).update();
	}
	for (int i = 0; i < this->_touchObjects.size(); ++i) {
		this->_touchObjects.at(i).update();
	}
	/*for (int i = 0; i < this->_dialogueObjects.size(); ++i) {
		this->_dialogueObjects.at(i).update();
	}*/
}

void Level::draw(Graphics& graphics) {
	for (int i = 0; i < this->_staticObject.size(); ++i) {
		this->_staticObject.at(i).draw(graphics);
	}

}

void Level::drawDialogue(Graphics& graphics) {
	if (Level::_isDialogue) {
		if (Level::flow >= this->_dialogueContents["computer"].size()) {
			Level::flow = 0;
			Level::_isDialogue = false;
			return;
		}
		
		std::string nowname = this->_dialogueContents["computer"][Level::flow].getCurrentSpoke();
		for (int i = 0; i < this->_staticDialogueObject[nowname].size(); ++i) {
			this->_staticDialogueObject[nowname][i].drawDialogue(graphics);
		}
		this->_dialogueContents["computer"][Level::flow].draw(graphics);
		
	}
}

std::vector<Collision> Level::checkObjectCollision(const Collision& other) {
	std::vector<Collision> others;
	for (auto &c : this->_collisionObjects) {
		if (c.collidesWith(other)) {
			printf("hit object\n");
			others.push_back(c);
		}
	}
	return others;
}

std::vector<TouchSend> Level::checkObjectTouch(const Collision& other , Graphics& graphics) {
	std::vector<TouchSend> others;
	for (int i = 0; i < this->_touchObjects.size(); ++i) {
		if (this->_touchObjects[i].collidesWith(other)) {
			printf("hit Touch\n");
			others.push_back(this->_touchObjects[i]);
			//刷新Leve地圖等繪製
			//讀取地圖(地圖名,Graphics)
			this->LoadMap(this->_touchObjects[i].getMapName(), graphics);
			break;
		}
	}
	return others;
}

bool Level::checkObjectDialogue(const Collision& other) { //按下X鍵
	std::vector<Collision> others;
	/*for (int i = 0; i < this->_dialogueObjects.size(); ++i) {
		if (this->_dialogueObjects[i].collidesWith(other)) {
			_isDialogue = true;
		}
	}*/
	for (auto&c : this->_dialogueObjects) {
		for (auto& c2 : c.second) {
			if (c2.collidesWith(other)) {
				//printf("1\n");
				if (!Level::_isDialogue) Level::flow = 0;
				else {
					if (!this->_dialogueContents["computer"][Level::flow].getDialogueOptions().empty()) {
						if (this->_dialogueContents["computer"][Level::flow].getDialogueOptions()[Level::CurrentOption].plot != "") {
							CGlobals::GameProcess[this->_dialogueContents["computer"][Level::flow].getDialogueOptions()[Level::CurrentOption].plot] = true;
							printf(this->_dialogueContents["computer"][Level::flow].getDialogueOptions()[Level::CurrentOption].plot.c_str());
						}
						//Level::flow += this->_dialogueContents["computer"][Level::flow].getCurrentSkip();
						this->_dialogueContents["computer"][Level::flow].getDialogueOptions()[Level::CurrentOption].setColorBlack();
						Level::CurrentOption = 0;
						this->_dialogueContents["computer"][Level::flow].getDialogueOptions()[Level::CurrentOption].setColorRed();
					}
					Level::flow += this->_dialogueContents["computer"][Level::flow].getCurrentSkip();
				}
				Level::_isDialogue = true;
				return true;
			}
		}
	}
	return false;
}

void Level::handleDialogueOption(bool UpOrDown) {
	if (!this->_dialogueContents["computer"][Level::flow].getDialogueOptions().empty()) {
		this->_dialogueContents["computer"][Level::flow].getDialogueOptions()[Level::CurrentOption].setColorBlack();
		if (UpOrDown) {
			++Level::CurrentOption;
			if (Level::CurrentOption >= this->_dialogueContents["computer"][Level::flow].getDialogueOptions().size()) {
				Level::CurrentOption = 0;
			}
		}
		else {
			--Level::CurrentOption;
			if (Level::CurrentOption < 0) {
				Level::CurrentOption = this->_dialogueContents["computer"][Level::flow].getDialogueOptions().size()-1;
			}
		}
		this->_dialogueContents["computer"][Level::flow].getDialogueOptions()[Level::CurrentOption].setColorRed();

	}
}

void Level::destoryFont() {
	TTF_CloseFont(this->font);
	TTF_Quit();
}