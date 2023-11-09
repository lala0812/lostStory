#include "player.h"

Player::Player() {

}
//�غc(Graphics,�Ϥ���m,�ӷ�xy,�ؼ�xy)
Player::Player(Graphics& graphics, const std::string fileName,
	Vector2D source, Vector2D destination):
	AnimatedSprite(graphics, fileName,
		 source,  destination),
	_facing(Direction::RIGHT),//�w�]�V��
	_positionMoveL(Vector2D(0,0)),//��l�ưʤO
	_positionMoveR(Vector2D(0,0)) {
	this->setupAnimation();//��l�ʵe
	this->playAnimation("IdleRight"); //�w�]����V�k���m�ʵe
}

void Player::moveRight() {
	this->_positionMoveR._x = player_constants::WALK_SPEED; //����
	this->playAnimation("RunRight"); //����ʵe
	this->_facing = Direction::RIGHT; //�]�w��V
}
void Player::moveLeft() {
	this->_positionMoveL._x = -player_constants::WALK_SPEED;
	this->playAnimation("RunLeft");
	this->_facing = Direction::LEFT;
}

void Player::stopRight() {
	this->_positionMoveR._x = 0; //����V�k�ʤO
}
void Player::stopLeft() {
	this->_positionMoveL._x = 0; //����V���ʤO
}


const float Player::getX() const {
	return this->pos._x; //��^�䨤��x
}

const float Player::getY() const {
	return this->pos._y;
}

void Player::setupAnimation() { 
	//�w�]�ʵe(�ʵe�W��,�ʵe�b��Ϥ�������m(x,y),Animation(�ʵe�զ����Ϥ���,�C�i�Ϥ����d������))
	this->addAnimation("RunLeft", Vector2D(0, 0, this->_sourceRect.w,this->_sourceRect.h), Animation(2, 20));
	this->addAnimation("IdleLeft", Vector2D(0, 0 , this->_sourceRect.w, this->_sourceRect.h), Animation(1, 20));
	this->addAnimation("RunRight", Vector2D(0, 128 , this->_sourceRect.w, this->_sourceRect.h), Animation(2, 20));
	this->addAnimation("IdleRight", Vector2D(0, 128 , this->_sourceRect.w, this->_sourceRect.h), Animation(1, 20));
}

void Player::handleCollisions(std::vector <Collision>& others) { //other�����I��������
	//�B�z�I��
	for (int i = 0; i < others.size(); i++) {
		collisionSide::Sides collisionSide = Sprite::getCollisionSide(others.at(i)); //�P�w��I����V
		if (collisionSide != collisionSide::Sides::NONE) { //�Y���T�w��V(�i�R)
			switch (collisionSide) { //�B�z���k��V
			case collisionSide::Sides::LEFT:
				this->pos._x = others.at(i).GetCurrentRight() + 1;
				break;
			case collisionSide::Sides::RIGHT:
				this->pos._x = others.at(i).GetCurrentLeft() - this->pos._width - 1;
				break;
			}

		}
	}
}

void Player::handleTouchs(std::vector <TouchSend>& others) {//�]�m��ǰe��m
	for (int i = 0; i < others.size(); i++) {
		this->pos._x = others[i].getSendPosition()._x;
		this->pos._y = others[i].getSendPosition()._y;
		break;
	}
}

void Player::update() { //�����s
	//���Ⲿ�ʤ�V=���ʤO+�k�ʤO
	this->pos._x += this->_positionMoveR._x + this->_positionMoveL._x;
	//�P�w���V�M�w�ʵe�ΰʵe��V
	if (this->_positionMoveR._x + this->_positionMoveL._x > 0) {
		this->playAnimation("RunRight");
	}
	else if (this->_positionMoveR._x + this->_positionMoveL._x < 0) {
		this->playAnimation("RunLeft");
	}
	else {//�L���ʮ�
		switch (this->_facing) {
		case Direction::RIGHT:
			this->playAnimation("IdleRight");
			break;
		case Direction::LEFT:
			this->playAnimation("IdleLeft");
			break;
		}
	}

	AnimatedSprite::update(); //�N�u�O��s
}
void Player::draw(Graphics& graphics) { //�ѹ껡���ε��y�� ����A��
	AnimatedSprite::draw(graphics, Vector2D(globals::camera_x, globals::camera_y, this->pos._width, this->pos._height));
}