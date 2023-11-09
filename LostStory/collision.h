#pragma once
/*�I����*/
#include "globals.h"


class Collision {
public:
	Collision() {}
	Collision(Vector2D pos) : _side(pos) {}//�I��x,y,width,height
	

	~Collision(){
		//delete this->_side;
	}
	//inline void setSide(Vector2D other) { this->_side = other; }


	//���o�I�������W�U���k
	inline const float GetCurrentRight() const { return this->_side._x + this->_side._width; }
	inline const float GetCurrentLeft() const { return this->_side._x; }

	inline const float GetCurrentTop() const { return this->_side._y; }
	inline const float GetCurrentBottom() const { return this->_side._y + this->_side._height; }

	Vector2D _side; //�I��x,y,width,height

protected:
	//Vector2D _side; //����b�o�O�]���n��� ����|�b�B�z
};
