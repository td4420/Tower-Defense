#pragma once
#include"Shaders.h"
class StateBase {
public:
	enum class StateControl {StateLogo, StateWelcome, StateMenu, StatePlay, StateOption, StateHelp, StateQuit, StateMap};
	virtual void init() = 0;
	virtual void Draw(Shaders* textShader, Shaders* shapeShader) = 0;
	virtual void Update(float deltaTime) = 0;
};