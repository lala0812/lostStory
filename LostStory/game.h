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

	//�C������Ӷi��
	void gameLoop(); 

	//�C���i��ɨC�@���ҧ�s�����e
	void update();

	//�C�����⪺�ƥ󱱨�
	void handleEvents();

	//�C��������ø�s
	void draw(Graphics& graphics);

private:

	//�C��Ĳ�o����ƥ󪺧N�o
	int coolDown;

	//�P�_�C���O�_�B��
	bool _isRunning;

	//���⪫��
	Player _player;

	//�a�Ϥ�NPC������
	Level _level;

	Bag _bag;
};
