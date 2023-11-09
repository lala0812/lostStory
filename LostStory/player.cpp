#include "player.h"

Player::Player() {

}
//建構(Graphics,圖片位置,來源xy,目標xy)
Player::Player(Graphics& graphics, const std::string fileName,
	Vector2D source, Vector2D destination):
	AnimatedSprite(graphics, fileName,
		 source,  destination),
	_facing(Direction::RIGHT),//預設向左
	_positionMoveL(Vector2D(0,0)),//初始化動力
	_positionMoveR(Vector2D(0,0)) {
	this->setupAnimation();//初始動畫
	this->playAnimation("IdleRight"); //預設播放向右閒置動畫
}

void Player::moveRight() {
	this->_positionMoveR._x = player_constants::WALK_SPEED; //移動
	this->playAnimation("RunRight"); //播放動畫
	this->_facing = Direction::RIGHT; //設定方向
}
void Player::moveLeft() {
	this->_positionMoveL._x = -player_constants::WALK_SPEED;
	this->playAnimation("RunLeft");
	this->_facing = Direction::LEFT;
}

void Player::stopRight() {
	this->_positionMoveR._x = 0; //停止向右動力
}
void Player::stopLeft() {
	this->_positionMoveL._x = 0; //停止向左動力
}


const float Player::getX() const {
	return this->pos._x; //返回其角色x
}

const float Player::getY() const {
	return this->pos._y;
}

void Player::setupAnimation() { 
	//預設動畫(動畫名稱,動畫在原圖片中的位置(x,y),Animation(動畫組成的圖片數,每張圖片停留的偵數))
	this->addAnimation("RunLeft", Vector2D(0, 0, this->_sourceRect.w,this->_sourceRect.h), Animation(2, 20));
	this->addAnimation("IdleLeft", Vector2D(0, 0 , this->_sourceRect.w, this->_sourceRect.h), Animation(1, 20));
	this->addAnimation("RunRight", Vector2D(0, 128 , this->_sourceRect.w, this->_sourceRect.h), Animation(2, 20));
	this->addAnimation("IdleRight", Vector2D(0, 128 , this->_sourceRect.w, this->_sourceRect.h), Animation(1, 20));
}

void Player::handleCollisions(std::vector <Collision>& others) { //other為有碰撞的物件
	//處理碰撞
	for (int i = 0; i < others.size(); i++) {
		collisionSide::Sides collisionSide = Sprite::getCollisionSide(others.at(i)); //判定其碰撞方向
		if (collisionSide != collisionSide::Sides::NONE) { //若有確定方向(可刪)
			switch (collisionSide) { //處理左右方向
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

void Player::handleTouchs(std::vector <TouchSend>& others) {//設置其傳送位置
	for (int i = 0; i < others.size(); i++) {
		this->pos._x = others[i].getSendPosition()._x;
		this->pos._y = others[i].getSendPosition()._y;
		break;
	}
}

void Player::update() { //角色更新
	//角色移動方向=左動力+右動力
	this->pos._x += this->_positionMoveR._x + this->_positionMoveL._x;
	//判定其方向決定動畫及動畫方向
	if (this->_positionMoveR._x + this->_positionMoveL._x > 0) {
		this->playAnimation("RunRight");
	}
	else if (this->_positionMoveR._x + this->_positionMoveL._x < 0) {
		this->playAnimation("RunLeft");
	}
	else {//無移動時
		switch (this->_facing) {
		case Direction::RIGHT:
			this->playAnimation("IdleRight");
			break;
		case Direction::LEFT:
			this->playAnimation("IdleLeft");
			break;
		}
	}

	AnimatedSprite::update(); //就只是更新
}
void Player::draw(Graphics& graphics) { //老實說不用給座標 之後再改
	AnimatedSprite::draw(graphics, Vector2D(globals::camera_x, globals::camera_y, this->pos._width, this->pos._height));
}