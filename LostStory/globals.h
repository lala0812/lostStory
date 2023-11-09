#pragma once

#include <map>
#include <string>


namespace globals {
	const int playerSize = 2;
	const float camera_x = 508;
	const float camera_y = 328;
}


namespace collisionSide {
	enum Sides {
		TOP,
		BOTTOM,
		LEFT,
		RIGHT,
		NONE
	};
}


class Vector2D {
public:

	Vector2D() :_x(0.0f), _y(0.0f), _width(32), _height(32) {}

	Vector2D(float x,float y,int width = 32,int height = 32):
		_x(x),_y(y),_width(width),_height(height){ }


	float _x, _y;
	int _width, _height;
private:
};

class CGlobals {
public:
	static Vector2D camera;
	static std::map<std::string, bool> GameProcess;
	static std::map<std::string,bool> mapItemSurvival;
private:
};





