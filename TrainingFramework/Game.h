#pragma once
#include"StateBase.h"
#include"StateMenu.h"
#include"StateWelcome.h"
#include"StateOption.h"
#include"StateHelp.h"
#include"StateLogo.h"
#include"StatePlay.h"
#include"StateHelp.h"
#include<stack>
using namespace std;
class Game  {
public:
	StateBase::StateControl curState;

	StateLogo* stateLogo = new StateLogo();
	StateWelcome* stateWelcome = new StateWelcome();
	StateMenu* stateMenu = new StateMenu();
	StateOption* stateOption = new StateOption();
	StatePlay* statePlay = new StatePlay();
	StateHelp* stateHelp = new StateHelp();
	
	void Update(float deltaTime);
	void Draw(Shaders* textShader, Shaders* shapeShader);
	void init();
	void OnMouseOver(int x, int y);
	void OnMouseClick(int x, int y);
	bool findStack(stack<StateBase::StateControl> stack,  StateBase::StateControl state);
	void getCurState();

};