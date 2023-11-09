#ifndef PLAYER_H
#define PLAYER_H

#include "animatedsprite.h"
#include "touchsend.h"

namespace player_constants {//���Ⲿ�ʳt��
	const float WALK_SPEED = 2.0f;
}

enum Direction { //�w�q��ʵe��V
	RIGHT,
	LEFT,
	TOP,
	DOWN
};

class Player : public AnimatedSprite { //�~�Ӧ�AnimatedSprite
public:
	Player();
	Player(Graphics& graphics, const std::string fileName,
		Vector2D source, Vector2D destination);
	/*
	* ���⪺����禡
	*/
	void moveRight();
	void moveLeft();

	void stopRight();
	void stopLeft();

	//���o��e�����m
	const float getX() const;
	const float getY() const;

	//�]�w�ʵe
	void setupAnimation();

	//����I������γB�z
	void handleCollisions(std::vector <Collision>& others);
	void handleTouchs(std::vector <TouchSend>& others);

	//��s��ø�s
	void update();
	void draw(Graphics& graphics);
private:

	Vector2D _positionMoveR;//����V�k�ʤO
	Vector2D _positionMoveL; //����V���ʤO
	Direction _facing; //�����e��V
};


#endif // !PLAYER_H

