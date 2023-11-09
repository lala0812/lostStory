#pragma once

#include "collision.h"

class CollisionObject : public Collision { //�i�����I����
public:
	//CollisionObjecct() {}
	CollisionObject(Vector2D Side) :Collision(Side) {

	}

	const bool collidesWith(const Collision& other) const { //�I���P�w
		return
			this->GetCurrentRight() >= other.GetCurrentLeft() &&
			this->GetCurrentLeft() <= other.GetCurrentRight() &&
			this->GetCurrentTop() <= other.GetCurrentBottom() &&
			this->GetCurrentBottom() >= other.GetCurrentTop();
	}

	void update() { 
		
	}

	const bool isValidCollision() const { //�P�w�O�_�����ĸI���� ����|�Ψ�
		return (this->_side._x <= 1080 && this->_side._y <= 720 && this->_side._width >= 0 && this->_side._height >= 0);
	}
private:

};
