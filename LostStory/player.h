#ifndef PLAYER_H
#define PLAYER_H

#include "animatedsprite.h"
#include "touchsend.h"

namespace player_constants {//角色移動速度
	const float WALK_SPEED = 2.0f;
}

enum Direction { //定義其動畫方向
	RIGHT,
	LEFT,
	TOP,
	DOWN
};

class Player : public AnimatedSprite { //繼承至AnimatedSprite
public:
	Player();
	Player(Graphics& graphics, const std::string fileName,
		Vector2D source, Vector2D destination);
	/*
	* 角色的控制函式
	*/
	void moveRight();
	void moveLeft();

	void stopRight();
	void stopLeft();

	//取得當前角色位置
	const float getX() const;
	const float getY() const;

	//設定動畫
	void setupAnimation();

	//角色碰撞機制及處理
	void handleCollisions(std::vector <Collision>& others);
	void handleTouchs(std::vector <TouchSend>& others);

	//更新及繪製
	void update();
	void draw(Graphics& graphics);
private:

	Vector2D _positionMoveR;//角色向右動力
	Vector2D _positionMoveL; //角色向左動力
	Direction _facing; //角色當前方向
};


#endif // !PLAYER_H

