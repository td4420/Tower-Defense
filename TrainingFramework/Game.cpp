#include"stdafx.h"
#include"Game.h"
#include"StateBase.h"
using namespace std;
void Game::Update(float deltaTime) {
	getCurState();
	/*else if (curState == StateBase::StateControl::StateWelcome) {
		stateWelcome->Update(deltaTime);
	}*/
	if (curState == StateBase::StateControl::StateMenu) {
		stateMenu->Update(deltaTime);
	}
	
	else if (curState == StateBase::StateControl::StateOption) {
		stateOption->Update(deltaTime);
	}else if (curState == StateBase::StateControl::StatePlay) {
		statePlay->Update(deltaTime);
	}
	else if (curState == StateBase::StateControl::StateHelp) {
		stateHelp->Update(deltaTime);
	}
}
void Game::Draw(Shaders* textShader, Shaders* shapeShader) {
	getCurState();
	
	if (curState == StateBase::StateControl::StateWelcome) {
		stateWelcome->Draw(textShader, shapeShader);
		//cout << "welcome\n";
	}
	else if (curState == StateBase::StateControl::StateMenu) {
		stateMenu->Draw(textShader, shapeShader);
		//cout << "menu\n";
	}
	
	else if (curState == StateBase::StateControl::StateOption) {
		stateOption->Draw(textShader, shapeShader);
		//cout << "option\n";
	}else if (curState == StateBase::StateControl::StatePlay) {
		statePlay->Draw(textShader);
		//cout << "play\n";
	}
	else if (curState == StateBase::StateControl::StateHelp) {
		stateHelp->Draw(textShader, shapeShader);
		//cout << "help\n";
	}
}
void Game::init() {
	
	stateMenu->init();
	statePlay->init();
	stateOption->init();
	stateHelp->init();
	curState = StateBase::StateControl::StateMenu;
	
}
void Game::OnMouseOver(int x, int y) {
	if (curState == StateBase::StateControl::StateWelcome) {
		stateWelcome->OnMouseOver(x,y);
	}
	else if (curState == StateBase::StateControl::StateMenu) {
		stateMenu->OnMouseOver(x,y);
	}
	else if (curState == StateBase::StateControl::StateOption) {
		stateOption->OnMouseOver(x, y);
	}
	else if (curState == StateBase::StateControl::StatePlay) {
		statePlay->OnMouseOver(x, y);
	}
	else if (curState == StateBase::StateControl::StateHelp) {
		stateHelp->OnMouseOver(x, y);
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
	else if (curState == StateBase::StateControl::StatePlay) {
		statePlay->OnMouseClick(x, y);
	}
	else if (curState == StateBase::StateControl::StateHelp) {
		stateHelp->OnMouseClick(x, y);
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
		curState = StateBase::StateControl::StateOption;
		return;
	}
	else if (curState == StateBase::StateControl::StateMenu && stateMenu->play->isChoose == true) {
		 curState = StateBase::StateControl::StatePlay;
		 return;
	 }
	else if (curState == StateBase::StateControl::StateOption && stateOption->back->isChoose == true) {
		stateMenu->options->isChoose = false;
		curState = StateBase::StateControl::StateMenu;
		return;
	}

	else if (curState == StateBase::StateControl::StateMenu && stateMenu->helps->isChoose == true) {
		curState = StateBase::StateControl::StateHelp;
		stateHelp->back->isChoose = false;
		return;
	}
	else if (curState == StateBase::StateControl::StateHelp && stateHelp->back->isChoose == true) {//quit help
		stateMenu->helps->isChoose = false;
		curState = StateBase::StateControl::StateMenu;
		return;
	}

	else if (curState == StateBase::StateControl::StateMenu && stateMenu->quit->isChoose == true) {
		cout << "Good Bye!" << endl;
		exit(-1);
	}
}

