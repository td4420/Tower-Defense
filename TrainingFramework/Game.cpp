#include"stdafx.h"
#include"Game.h"
#include"StateBase.h"
using namespace std;
void Game::Update(float deltaTime) {

	
	if (curState == StateBase::StateControl::StateMenu) {
		stateMenu->Update(deltaTime);
	}else if (curState == StateBase::StateControl::StateOption) {
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
	
	if (curState == StateBase::StateControl::StateMenu) {
		stateMenu->Draw(textShader, shapeShader);
		
		curThemeMusic.openFromFile("./Sound/menutheme2.wav");
		curThemeMusic.setLoop(true);
		curThemeMusic.setVolume(35);
		curThemeMusic.play(); 
	}
	else if (curState == StateBase::StateControl::StateOption) {
		stateOption->Draw(textShader, shapeShader);
				
	}else if (curState == StateBase::StateControl::StatePlay) {
		statePlay->Draw(textShader);
		
	}
	else if (curState == StateBase::StateControl::StateMap) {
		stateMap->Draw(textShader, shapeShader);
		
	}
	else if (curState == StateBase::StateControl::StateHelp) {
		stateHelp->Draw(textShader, shapeShader);
	}
}
void Game::init() {
	stateMap->init();
	stateMenu->init();
	//statePlay->init();
	stateOption->init();
	stateHelp->init();
	curState = StateBase::StateControl::StateMenu;
	
}

void Game::OnMouseOver(int x, int y) {
	if (curState == StateBase::StateControl::StatePlay) {
		statePlay->OnMouseOver(x, y);
	}
	else if (curState == StateBase::StateControl::StateMenu) {
		stateMenu->OnMouseOver(x,y);
	}
	else if (curState == StateBase::StateControl::StateOption) {
		stateOption->OnMouseOver(x, y);
	}
	
	else if (curState == StateBase::StateControl::StateHelp) {
		stateHelp->OnMouseOver(x, y);
	}
	else if (curState == StateBase::StateControl::StateMap) {
		stateMap->OnMouseOver(x, y);
	}
}
void Game::OnMouseClick(int x, int y) {
	if (curState == StateBase::StateControl::StatePlay) {
		statePlay->OnMouseClick(x, y);
	}
	else if (curState == StateBase::StateControl::StateMenu) {
		stateMenu->OnMouseClick(x, y);
	}
	else if (curState == StateBase::StateControl::StateOption) {
		stateOption->OnMouseClick(x, y);
	}
	
	else if (curState == StateBase::StateControl::StateHelp) {
		stateHelp->OnMouseClick(x, y);
	}
	else if (curState == StateBase::StateControl::StateMap) {
		stateMap->OnMouseClick(x, y);
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
	//play
	if (curState == StateBase::StateControl::StateMap && (stateMap->M1->isChoose == true || stateMap->M2->isChoose == true)) {
		if (initCount == 0)
		{
			initCount++;
			statePlay->init(stateMap->Map);
		}
		curState = StateBase::StateControl::StatePlay;
		return;
	}
	// option
	else if (curState == StateBase::StateControl::StateMenu && stateMenu->options->isChoose == true) {
		stateOption->back->isChoose = false;
		curState = StateBase::StateControl::StateOption;
		return;
	}else if (curState == StateBase::StateControl::StateOption && stateOption->back->isChoose == true) {
		stateMenu->options->isChoose = false;
		curState = StateBase::StateControl::StateMenu;
		return;
	}
	// Map
	else if (curState == StateBase::StateControl::StateMenu && stateMenu->play->isChoose == true) {
		stateMap->back->isChoose = false;
		 curState = StateBase::StateControl::StateMap;
		 return;
	 }
	else if (curState == StateBase::StateControl::StateMap && stateMap->back->isChoose == true) {
		stateMenu->play->isChoose = false;
		curState = StateBase::StateControl::StateMenu;
		return;
	}
	//help
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
	//quit
	else if (curState == StateBase::StateControl::StateMenu && stateMenu->quit->isChoose == true) {
		this->CleanUp();
		delete this;
		cout << "Good Bye!" << endl;
		exit(-1);
	}
}

void Game::CleanUp()
{
	stateMenu->CleanUp();
	stateHelp->CleanUp();
	stateOption->CleanUp();
	stateMap->CleanUp();

	if (initCount == 0) statePlay->CleanUpIfNotInit();
	else
	{
		statePlay->CleanUp();
	}


	delete stateMenu;
	delete stateHelp;
	delete stateOption;
	delete stateMap;
	delete statePlay;
}
