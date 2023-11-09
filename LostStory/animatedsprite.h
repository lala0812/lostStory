#pragma once
#include "sprite.h"
#include "animation.h"
#include <vector>

class AnimatedSprite : public Sprite{ //動畫處理 繼承至Sprite
public:
	AnimatedSprite() {}
	AnimatedSprite(Graphics& graphics, const std::string fileName,
		Vector2D source, Vector2D destination  );

	void playAnimation(std::string animationName);//播放動畫

	void update();//更新
	void draw(Graphics& graphics , Vector2D position); //繪圖

protected:
	void addAnimation(const std::string animationName,Vector2D source,Animation animation); //加入動畫
	void resetAnimations(); //重設動畫播放進度

	std::string _currentAnimated; //當前播放動畫名稱
private:
	std::map<std::string, std::vector<SDL_Rect>> _animations; //存放動畫(名稱,播放圖片來源位置)
	std::map<std::string, Animation> _animationTime; //儲存動畫偵數,速度(請參考animation.h)

	int _frameIndex; //目前播放的動畫偵數

	int _timeElapsed; //遊戲偵數
};



