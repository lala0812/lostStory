#include "animatedsprite.h"

AnimatedSprite::AnimatedSprite(Graphics& graphics, const std::string fileName,
	Vector2D source, Vector2D destination) :
	Sprite(graphics, fileName, source, destination),
	_frameIndex(0), //��l��0
	_currentAnimated(""), //�w�]��e�L�ʵe
	_timeElapsed(0){ 

}

void AnimatedSprite::playAnimation(std::string animationName) { //�����e�ʵe
	if (this->_currentAnimated != animationName) { //�P�w���񪺰ʵe�O�_�P��e�ۦP
		this->_currentAnimated = animationName; //���P�h��s
		resetAnimations(); //���]�ʵe����
	}
}

void AnimatedSprite::update() {
	Sprite::update(); //��sSprite

	++this->_timeElapsed; //�C�����ƼW�[
	//�p�G��e�C�����Ƥw�F�ʵe�����t��
	if (this->_timeElapsed >= this->_animationTime[this->_currentAnimated].speed) {
		this->_timeElapsed = 0;
		++this->_frameIndex;//�W�[�ʵe����
		if (this->_frameIndex >= this->_animationTime[this->_currentAnimated].index) {
			resetAnimations();
		}
	}
}

void AnimatedSprite::draw(Graphics& graphics, Vector2D position) { 
	//�Nø�� �`�N�PSprite::Draw���P 
	SDL_Rect destinationRectangle;
	destinationRectangle.x = position._x;
	destinationRectangle.y = position._y ;
	destinationRectangle.w = position._width;
	destinationRectangle.h = position._height;

	SDL_Rect sourceRect = this->_animations[this->_currentAnimated][this->_frameIndex];
	//��s��V
	//this->_spriteSheet��Sprite���Ϥ�SDL_Texture
	graphics.blitSurface(this->_spriteSheet, &sourceRect, &destinationRectangle);
}
//�s�W�ʵe
void AnimatedSprite::addAnimation(const std::string animationName,Vector2D source, Animation animation) {
	std::vector<SDL_Rect> rectangle;
	for (int i = 0; i < animation.index; ++i) {
		SDL_Rect newRect = { source._x + i * source._width,source._y,source._width,source._height };
		rectangle.push_back(newRect);
	}
	this->_animations[animationName] = rectangle; //�x�s�ʵe
	this->_animationTime[animationName] = animation;
}

void AnimatedSprite::resetAnimations() { //�N�k0
	this->_frameIndex = 0;
}