#pragma once

#include "collision.h"

class CollisionObject : public Collision { //進階版碰撞器
public:
	//CollisionObjecct() {}
	CollisionObject(Vector2D Side) :Collision(Side) {

	}

	const bool collidesWith(const Collision& other) const { //碰撞判定
		return
			this->GetCurrentRight() >= other.GetCurrentLeft() &&
			this->GetCurrentLeft() <= other.GetCurrentRight() &&
			this->GetCurrentTop() <= other.GetCurrentBottom() &&
			this->GetCurrentBottom() >= other.GetCurrentTop();
	}

	void update() { 
		
	}

	const bool isValidCollision() const { //判定是否為有效碰撞物 之後會用到
		return (this->_side._x <= 1080 && this->_side._y <= 720 && this->_side._width >= 0 && this->_side._height >= 0);
	}
private:

};
