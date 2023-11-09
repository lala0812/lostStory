#include "game.h"
#include "input.h"

//�C���۾���m
Vector2D CGlobals::camera = Vector2D(0, 0);
//�P�w�ثe�O�_Ĳ�o��ܨƥ�
bool Level::_isDialogue = false;
//��ܮت����ǧP�_�̧�
int Level::flow = 0;
//
int Level::CurrentOption = 0;
//�C�����غc
Game::Game() :_isRunning(true),coolDown(0)
	{
	//�C����l��
	SDL_Init(SDL_INIT_EVERYTHING);
	this->gameLoop();
}

Game::~Game() {

}

void Game::gameLoop() {
	//�ŧiø�Ϫ���(�����W��,������mx,������my,�����j�px,�����j�py,�������)
	Graphics graphics("LostStory",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
		1080,720,SDL_WINDOW_SHOWN);
	//�ŧi��J����
	Input input;
	//�ŧi�C���ƥ�
	SDL_Event _event;
	//�w�q���v
	int FPS = 60;
	int frameDelay = 1000 / FPS; 
	int frameStart = 0;
	//�w�qLevel �ᤩ���s�w�q
	this->_level = Level();
	//Ū���a��(�a�ϦW,Graphics)
	this->_level.LoadMap("new_map", graphics);
	//�w�q����(Graphics,�������,�������xy,��m��mx,y)
	this->_player = Player(graphics, "assets/_player.png", Vector2D(0, 0,64,128), Vector2D(508, 607,64,128));
	//Game start
	this->_bag = Bag(graphics, "assets/bag/bag.png");

	while (this->_isRunning) {
		frameStart = SDL_GetTicks(); //���o�ثe�ɶ�
		//Frame start
		//input.resetKey();
		if (SDL_PollEvent(&_event)) { //���o��e�C���ƥ�
			if (_event.type == SDL_KEYDOWN) { //���U����ƥ�
				if (_event.key.repeat == 0) { //�P�_�O�_����@�ƥ�
					input.keyDownEvent(_event); //�K�[��input����
				}
			}
			else if (_event.type == SDL_KEYUP) { //��}����ƥ�
				if (_event.key.repeat == 0) { //
					input.keyUpEvent(_event); //�K�[��input����
				}
			}
			else if (_event.type == SDL_QUIT) { //�P�w�O�_�����}�ƥ�
				return;
			}
		}
		if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE) == true) { //���Uescape���}�C��
			break;
		}
		if (input.isKeyHeld(SDL_SCANCODE_LEFT) == true) { //���U����V��
			this->_player.moveLeft();//����V�����ʨƥ�
		}
		else {
			this->_player.stopLeft(); //����L���U�ɡA�Ϩ���V���ʤO�k0
		}
		if (input.isKeyHeld(SDL_SCANCODE_RIGHT) == true) {
			this->_player.moveRight();
		}
		else {
			this->_player.stopRight();
		}
		//��ܱ���
		if (input.isKeyHeld(SDL_SCANCODE_UP) == true && !coolDown && Level::_isDialogue) {
			this->_level.handleDialogueOption(false);
			coolDown = 20;
		}
		if (input.isKeyHeld(SDL_SCANCODE_DOWN) == true && !coolDown && Level::_isDialogue) {
			this->_level.handleDialogueOption(true);
			coolDown = 20;
		}

		if (input.isKeyHeld(SDL_SCANCODE_Z) == true && !coolDown) { //�����ǰe�a�Ϩƥ�
			std::vector<TouchSend> others;
			if ((others = this->_level.checkObjectTouch(this->_player.getCollisionBox(),graphics)).size() > 0) {
				this->_player.handleTouchs(others);//�ǰe
				coolDown = 50;
			}
		}
		if (input.isKeyHeld(SDL_SCANCODE_X) == true && !coolDown) { //������ܮبƥ�
			if (this->_level.checkObjectDialogue(this->_player.getCollisionBox())) {
				coolDown = 50;
			}
		}
		if (input.isKeyHeld(SDL_SCANCODE_B) == true && !coolDown) {
			this->_bag.openBag();
			coolDown = 50;
		}
		if (input.isKeyHeld(SDL_SCANCODE_C) == true && !coolDown) {//�ȵL
			coolDown = 50;
		}



		//Frame end
		int frameTime = SDL_GetTicks() - frameStart;
		this->update(); //�C����s
		this->draw(graphics); //�C��ø��
		SDL_Delay(frameDelay > frameTime ? frameDelay - frameTime : 0);
	}

	this->_level.destoryFont();
}

void Game::update() {
	if (coolDown) --coolDown; //�ϧN�o�`��
	this->_player.update(); //�i�樤���s
	

	std::vector<Collision> others; //�P�w�O�_���I������
	if ((others = this->_level.checkObjectCollision(this->_player.getCollisionBox())).size() > 0) {
		this->_player.handleCollisions(others);
	}
	
	//printf("%f\n", this->_player.getY());
	CGlobals::camera._x = this->_player.getX() - 508; //��s�۾�������
	CGlobals::camera._y = this->_player.getY() - 328;

}

void Game::draw(Graphics& graphics) { //ø�s���ǨM�w�ϼh�e��
	graphics.clear(); //ø�ϲM��
	this->_level.draw(graphics); //���dø�s
	this->_player.draw(graphics);//����ø�s
	this->_level.drawDialogue(graphics);//��ܮ�ø�s
	this->_bag.drawBag(graphics);
	graphics.flip(); //���s��V

}

