#include "animatedsprite.h"

AnimatedSprite::AnimatedSprite(Graphics& graphics, const std::string fileName,
	Vector2D source, Vector2D destination) :
	Sprite(graphics, fileName, source, destination),
	_frameIndex(0), //初始為0
	_currentAnimated(""), //預設當前無動畫
	_timeElapsed(0){ 

}

void AnimatedSprite::playAnimation(std::string animationName) { //播放當前動畫
	if (this->_currentAnimated != animationName) { //判定播放的動畫是否與當前相同
		this->_currentAnimated = animationName; //不同則更新
		resetAnimations(); //重設動畫播放
	}
}

void AnimatedSprite::update() {
	Sprite::update(); //更新Sprite

	++this->_timeElapsed; //遊戲偵數增加
	//如果當前遊戲偵數已達動畫片的速度
	if (this->_timeElapsed >= this->_animationTime[this->_currentAnimated].speed) {
		this->_timeElapsed = 0;
		++this->_frameIndex;//增加動畫偵數
		if (this->_frameIndex >= this->_animationTime[this->_currentAnimated].index) {
			resetAnimations();
		}
	}
}

void AnimatedSprite::draw(Graphics& graphics, Vector2D position) { 
	//就繪圖 注意與Sprite::Draw不同 
	SDL_Rect destinationRectangle;
	destinationRectangle.x = position._x;
	destinationRectangle.y = position._y ;
	destinationRectangle.w = position._width;
	destinationRectangle.h = position._height;

	SDL_Rect sourceRect = this->_animations[this->_currentAnimated][this->_frameIndex];
	//更新渲染
	//this->_spriteSheet為Sprite的圖片SDL_Texture
	graphics.blitSurface(this->_spriteSheet, &sourceRect, &destinationRectangle);
}
//新增動畫
void AnimatedSprite::addAnimation(const std::string animationName,Vector2D source, Animation animation) {
	std::vector<SDL_Rect> rectangle;
	for (int i = 0; i < animation.index; ++i) {
		SDL_Rect newRect = { source._x + i * source._width,source._y,source._width,source._height };
		rectangle.push_back(newRect);
	}
	this->_animations[animationName] = rectangle; //儲存動畫
	this->_animationTime[animationName] = animation;
}

void AnimatedSprite::resetAnimations() { //就歸0
	this->_frameIndex = 0;
}