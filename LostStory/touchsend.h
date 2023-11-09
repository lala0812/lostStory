#pragma once

#include "collision.h"
#include <string>

class TouchSend : public Collision {
public:
	//CollisionObjecct() {}
	TouchSend(Vector2D Side,const std::string MapN , Vector2D SendPosition) :Collision(Side),
	_mapName(MapN),
	_sendPosition(SendPosition){

	}

	const bool collidesWith(const Collision& other) const {
		return
			this->GetCurrentRight() >= other.GetCurrentLeft() &&
			this->GetCurrentLeft() <= other.GetCurrentRight() &&
			this->GetCurrentTop() <= other.GetCurrentBottom() &&
			this->GetCurrentBottom() >= other.GetCurrentTop();
	}

	void update() {

	}

	const bool isValidCollision() const {
		return (this->_side._x <= 1080 && this->_side._y <= 720 && this->_side._width >= 0 && this->_side._height >= 0);
	}

	const std::string getMapName() const {
		return this->_mapName;
	}

	const Vector2D getSendPosition() const {
		return this->_sendPosition;
	}

	
private:
	std::string _mapName;
	Vector2D _sendPosition;
};
#pragma once
