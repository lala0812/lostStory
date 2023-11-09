#pragma once
/*碰撞器*/
#include "globals.h"


class Collision {
public:
	Collision() {}
	Collision(Vector2D pos) : _side(pos) {}//碰撞x,y,width,height
	

	~Collision(){
		//delete this->_side;
	}
	//inline void setSide(Vector2D other) { this->_side = other; }


	//取得碰撞器的上下左右
	inline const float GetCurrentRight() const { return this->_side._x + this->_side._width; }
	inline const float GetCurrentLeft() const { return this->_side._x; }

	inline const float GetCurrentTop() const { return this->_side._y; }
	inline const float GetCurrentBottom() const { return this->_side._y + this->_side._height; }

	Vector2D _side; //碰撞x,y,width,height

protected:
	//Vector2D _side; //不放在這是因為要更改 之後會在處理
};
