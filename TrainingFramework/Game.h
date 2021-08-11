#pragma once
#include"StateBase.h"
#include"StateMenu.h"
#include"StateWelcome.h"
#include<stack>
using namespace std;
class Game  {
public:

	StateBase::StateControl curState;
	stack<StateBase::StateControl> stackState;
	StateWelcome* stateWelcome = new StateWelcome();
	StateMenu* stateMenu = new StateMenu();
	bool isFinishLoading;
	void Update(float deltaTime);
	void Draw(Shaders s);
	void init();
};