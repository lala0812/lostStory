#include"sprite.h"
#include <algorithm>

Sprite::Sprite() {

}

Sprite::Sprite(Graphics& graphics,const std::string fileName, Vector2D source,Vector2D destination){
	this->pos._x = destination._x;
	this->pos._y = destination._y;
	this->pos._width = destination._width;
	this->pos._height = destination._height;
	this->_sourceRect.x = source._x;
	this->_sourceRect.y = source._y;
	this->_sourceRect.w = source._width;
	this->_sourceRect.h = source._height;
	this->_collision = Collision(destination); //�w�q�I��
	//Ū���Ϥ��ܯ��z
	this->_spriteSheet = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(fileName));
	if (this->_spriteSheet == NULL) { //�SŪ��Ϥ����z�פW�nGG��
		printf("\nError: Unable to load image\n");
	}

}

Sprite::~Sprite() {

}

void Sprite::update() { //��s��I������xy
	this->_collision._side._x = this->pos._x;
	this->_collision._side._y = this->pos._y;
}

void Sprite::draw(Graphics& graphics,int x ,int y) { //�N�e�� ��AnimatedSprite���P
	SDL_Rect destRect = { x , y , this->_sourceRect.w,this->_sourceRect.h };
	graphics.blitSurface(this->_spriteSheet, &this->_sourceRect, &destRect);
}

const collisionSide::Sides Sprite::getCollisionSide(Collision& other) const {
	//�P�w��I����V
	int amtRight, amtLeft, amtTop, amtBottom;
	amtRight = this->_collision.GetCurrentRight() - other.GetCurrentLeft();
	amtLeft = other.GetCurrentRight() - this->_collision.GetCurrentLeft();
	amtTop = other.GetCurrentBottom() - this->_collision.GetCurrentTop();
	amtBottom = this->_collision.GetCurrentBottom() - other.GetCurrentTop();

	int lowest;
	lowest = std::min({ amtRight, amtLeft, amtTop, amtBottom });


	return
		lowest == abs(amtRight) ? collisionSide::Sides::RIGHT :
		lowest == abs(amtLeft) ? collisionSide::Sides::LEFT :
		lowest == abs(amtTop) ? collisionSide::Sides::TOP :
		lowest == abs(amtBottom) ? collisionSide::Sides::BOTTOM :
		collisionSide::Sides::NONE;
}

const Collision Sprite::getCollisionBox() const { //���o�I����
	//printf("%f\n", this->_collision.GetCurrentLeft());
	return this->_collision;
}