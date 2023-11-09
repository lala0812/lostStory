#pragma once
#include "sprite.h"
#include "animation.h"
#include <vector>

class AnimatedSprite : public Sprite{ //�ʵe�B�z �~�Ӧ�Sprite
public:
	AnimatedSprite() {}
	AnimatedSprite(Graphics& graphics, const std::string fileName,
		Vector2D source, Vector2D destination  );

	void playAnimation(std::string animationName);//����ʵe

	void update();//��s
	void draw(Graphics& graphics , Vector2D position); //ø��

protected:
	void addAnimation(const std::string animationName,Vector2D source,Animation animation); //�[�J�ʵe
	void resetAnimations(); //���]�ʵe����i��

	std::string _currentAnimated; //��e����ʵe�W��
private:
	std::map<std::string, std::vector<SDL_Rect>> _animations; //�s��ʵe(�W��,����Ϥ��ӷ���m)
	std::map<std::string, Animation> _animationTime; //�x�s�ʵe����,�t��(�аѦ�animation.h)

	int _frameIndex; //�ثe���񪺰ʵe����

	int _timeElapsed; //�C������
};



