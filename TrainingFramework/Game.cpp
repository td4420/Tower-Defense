#include"stdafx.h"
#include"Game.h"
#include"StateBase.h"
using namespace std;
void Game::Update(float deltaTime) {
	getCurState();
	if (curState == StateBase::StateControl::StateWelcome) {
		stateWelcome->Update(deltaTime);
	}
	else if (curState == StateBase::StateControl::StateMenu) {
		stateMenu->Update(deltaTime);
	}
	else if (curState == StateBase::StateControl::StateOption) {
		stateOption->Update(deltaTime);
	}
}
void Game::Draw(Shaders textShader, Shaders shapeShader) {
	getCurState();
	if (curState == StateBase::StateControl::StateWelcome) {
		stateWelcome->Draw(textShader, shapeShader);
	}
	else if (curState == StateBase::StateControl::StateMenu) {
		stateMenu->Draw(textShader, shapeShader);
	}
	else if (curState == StateBase::StateControl::StateOption) {
		stateOption->Draw(textShader, shapeShader);
	}
}
void Game::init() {
	stateMenu->init();
	stateWelcome->init();
	stateOption->init();
	curState = StateBase::StateControl::StateWelcome;
	stackState.push(curState);
}
void Game::OnMouseOver(int x, int y) {
	if (curState == StateBase::StateControl::StateWelcome) {
		stateWelcome->OnMouseOver(x,y);
	}
	else if (curState == StateBase::StateControl::StateMenu) {
		stateMenu->OnMouseOver(x,y);
	}
	else if (curState == StateBase::StateControl::StateOption) {
		stateOption->OnMousOver(x, y);
	}
}
void Game::OnMouseClick(int x, int y) {
	if (curState == StateBase::StateControl::StateWelcome) {
		stateWelcome->OnMouseClick(x, y);
	}
	else if (curState == StateBase::StateControl::StateMenu) {
		stateMenu->OnMouseClick(x, y);
	}
	else if (curState == StateBase::StateControl::StateOption) {
		stateOption->OnMouseClick(x, y);
	}
}
bool Game::findStack(stack<StateBase::StateControl> stack, StateBase::StateControl state) {
	std::stack<StateBase::StateControl> stackCopy;
	stackCopy = stack;
	while (!stackCopy.empty()) {
		StateBase::StateControl tmp = stackCopy.top();
		if (tmp == state) return true;
		stackCopy.pop();
	}
	return false;
}
void Game::getCurState() {
	
	if (curState == StateBase::StateControl::StateWelcome && stateWelcome->percentLoad < 100) {
		curState = StateBase::StateControl::StateWelcome;
		return;
	}
	else if (curState == StateBase::StateControl::StateWelcome && stateWelcome->tapToStart->isChoose == true) {
		curState = StateBase::StateControl::StateMenu;
		
		stateWelcome->tapToStart->isChoose == false;
		return;
	}
	else if (curState == StateBase::StateControl::StateMenu && stateMenu->options->isChoose == true) {
		stateOption->back->isChoose = false;
		stateMenu->options->isChoose = false;
		curState = StateBase::StateControl::StateOption;
		
		return;
	}
	else if (curState == StateBase::StateControl::StateOption && stateOption->back->isChoose == true) {
		stateMenu->options->isChoose = false;
		stateOption->back->isChoose = false;
		curState = StateBase::StateControl::StateMenu;
		
		return;
	}
}