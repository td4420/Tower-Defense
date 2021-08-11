#pragma once
#include"Shaders.h"
class StateBase {
public:
	enum class StateControl {StateWelcome, StateMenu, StatePlay, StateOption, StateHelp, StateQuit};
	virtual void init() = 0;
	virtual void Draw(Shaders s) = 0;
	virtual void Update(float deltaTime) = 0;
};