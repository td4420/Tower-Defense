#include"stdafx.h"
#include"Game.h"
#include"StateBase.h"
void Game::Update(float deltaTime) {
	if (curState == StateBase::StateControl::StateWelcome && stateWelcome->percentLoad < 100) {
		stateWelcome->Update(deltaTime);
	}
	if (stateWelcome->percentLoad >= 100) {
		curState = StateBase::StateControl::StateMenu;
		//stackState.push(curState);
		stateMenu->Update(deltaTime);
	}
}
void Game::Draw(Shaders s) {
	if (curState == StateBase::StateControl::StateWelcome) {
		stateWelcome->Draw(s);
	}
	if (curState == StateBase::StateControl::StateMenu) {
		stateMenu->Draw(s);
	}
}
void Game::init() {
	stateMenu->init();
	stateWelcome->init();
	curState = StateBase::StateControl::StateWelcome;
	stackState.push(curState);
}