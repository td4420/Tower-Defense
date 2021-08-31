#include"stdafx.h"
#include"StateOption.h"
#include<iostream>
//void StateOption::init() {
//	onSound = true;
//	back->init();
//	nhacNen->init();
//	onNhacNen->init();
//	offNhacNen->init();
//	changeNhacNen->init();
//
//
//	listText.push_back(back);
//	listText.push_back(nhacNen);
//	
//	listText.push_back(changeNhacNen);
//	//listText.push_back(onNhacNen);
//	//listText.push_back(offNhacNen);
//}
//void StateOption::Update(float deltaTime) {
//
//}
//void StateOption::Draw(Shaders* textShader, Shaders* shapeShader) {
//	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//	for (int i = 0; i < listText.size(); i++) {
//		listText.at(i)->RenderText(textShader);
//	}
//	if (onSound == true) {
//		onNhacNen->RenderText(textShader);
//	}
//	if (onSound == false) {
//		offNhacNen->RenderText(textShader);
//	}
//	std::cout << onSound;
//}
//void StateOption::OnMouseOver(int x, int y) {
//	if (back->checkChoose(x, y) == true) {
//		back->color = Vector4(0.6, 0.4, 0.5, 1.0);
//	}
//	if (back->checkChoose(x, y) == false) {
//		back->color = Vector4(0.5, 0.5, 0.5, 0.5);
//	}
//	if (onNhacNen->checkChoose(x, y) == true) {
//		onNhacNen->color = Vector4(0.6, 0.4, 0.5, 1.0);
//	}
//	if (onNhacNen->checkChoose(x, y) == false) {
//		onNhacNen->color = Vector4(0.5, 0.5, 0.5, 0.5);
//	}
//	if (offNhacNen->checkChoose(x, y) == true) {
//		offNhacNen->color = Vector4(0.6, 0.4, 0.5, 1.0);
//	}
//	if (offNhacNen->checkChoose(x, y) == false) {
//		offNhacNen->color = Vector4(0.5, 0.5, 0.5, 0.5);
//	}
//}
//void StateOption::OnMouseClick(int x, int y) {
//	if (back->checkChoose(x, y) == true) {
//		back->isChoose = true;
//	}
//	if (back->checkChoose(x, y) == false) {
//		back->isChoose = false;
//	}
//	if (onSound == true && onNhacNen->checkChoose(x, y) == true) {
//		onSound = false;
//	}
//	else if (onSound == false && offNhacNen->checkChoose(x, y) == true) {
//		onSound = true;
//	}
//}

void StateOption::init()
{	
	modelLogo = new Model("../ResourcesPacket/Models/Button.nfg");
	modelLogo->Init();
	
	textureLogo = new Texture("../ResourcesPacket/Textures/bgOption.tga");
	textureLogo->Init();

	scale.SetScale(2, 4, 3);
	pos.SetTranslation(-1, -3, 0);
	mvp = scale * pos;

	onSoundNen = true;
	onSoundGame = true;

	back = new Text("B A C K", 10, Globals::screenHeight - 32.5, "../Font/OceanSummer.ttf", 1, 1, Vector4(1.0, 1.0, 1.0, 1.0), 48);

	//nhac nen
	nhacNen = new Text("NHAC NEN :", 280, 550, "../Font/OceanSummer.ttf", 1, 1, Vector4(1.0, 1.0, 1.0, 1.0), 78);
	onNhacNen = new Text("5", 550, 550, "../Font/wingdings2.ttf", 1, 1, Vector4(1.0, 1.0, 1.0, 1.0), 78);
	offNhacNen = new Text("6", 550, 550, "../Font/wingdings2.ttf", 1, 1, Vector4(1.0, 1.0, 1.0, 1.0), 78);
	changeNhacNen = new Text(vnen, 450, 550, "../Font/OceanSummer.ttf", 1, 1, Vector4(1.0, 1.0, 1.0, 1.0), 78);
	giamVolumeNen = new Text("-", 415, 550, "../Font/OceanSummer.ttf", 1, 1, Vector4(1.0, 1.0, 1.0, 1.0), 78);
	tangVolumeNen = new Text("+", 485, 550, "../Font/OceanSummer.ttf", 1, 1, Vector4(1.0, 1.0, 1.0, 1.0), 78);

	//nhac game
	nhacGame = new Text("NHAC GAME :", 270, 450, "../Font/OceanSummer.ttf", 1, 1, Vector4(1.0, 1.0, 1.0, 1.0), 78);
	onNhacGame = new Text("5", 550, 450, "../Font/wingdings2.ttf", 1, 1, Vector4(1.0, 1.0, 1.0, 1.0), 78);
	offNhacGame = new Text("6", 550, 450, "../Font/wingdings2.ttf", 1, 1, Vector4(1.0, 1.0, 1.0, 1.0), 78);
	changeNhacGame = new Text(vgame, 450, 450, "../Font/OceanSummer.ttf", 1, 1, Vector4(1.0, 1.0, 1.0, 1.0), 78);
	giamVolumeGame = new Text("-", 415, 450, "../Font/OceanSummer.ttf", 1, 1, Vector4(1.0, 1.0, 1.0, 1.0), 78);
	tangVolumeGame = new Text("+", 485, 450, "../Font/OceanSummer.ttf", 1, 1, Vector4(1.0, 1.0, 1.0, 1.0), 78);


	back->init();

	nhacNen->init();
	onNhacNen->init();
	offNhacNen->init();
	changeNhacNen->init();
	tangVolumeNen->init();
	giamVolumeNen->init();

	nhacGame->init();
	onNhacGame->init();
	offNhacGame->init();
	changeNhacGame->init();
	tangVolumeGame->init();
	giamVolumeGame->init();

	listText.push_back(back);

	listText.push_back(nhacNen);
	listText.push_back(changeNhacNen);
	listText.push_back(tangVolumeNen);
	listText.push_back(giamVolumeNen);


	listText.push_back(nhacGame);
	listText.push_back(changeNhacGame);
	listText.push_back(tangVolumeGame);
	listText.push_back(giamVolumeGame);

	//listText.push_back(changeNhacNen);
	//listText.push_back(onNhacNen);
	//listText.push_back(offNhacNen);
}
void StateOption::Update(float deltaTime) {

	tmpGame = std::to_string(volumeGame);
	vgame = tmpGame.c_str();
	changeNhacGame->text = vgame;

	tmpNen = std::to_string(volumeNen);
	vnen = tmpNen.c_str();
	changeNhacNen->text = vnen;

}
void StateOption::Draw(Shaders* textShader, Shaders* shapeShader) {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glUseProgram(shapeShader->program);

	glBindTexture(GL_TEXTURE_2D, textureLogo->mTextureId);
	glBindBuffer(GL_ARRAY_BUFFER, modelLogo->mVBO);
	if (shapeShader->positionAttribute != -1)
	{
		glEnableVertexAttribArray(shapeShader->positionAttribute);
		glVertexAttribPointer(shapeShader->positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}
	if (shapeShader->uvAttribute != -1)
	{
		glEnableVertexAttribArray(shapeShader->uvAttribute);
		glVertexAttribPointer(shapeShader->uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(2 * sizeof(Vector3)));
	}


	glUniformMatrix4fv(shapeShader->u_MVP, 1, GL_FALSE, *mvp.m);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, modelLogo->mIBO);
	glDrawElements(GL_TRIANGLES, modelLogo->mNumberOfIndices, GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	for (int i = 0; i < listText.size(); i++) {
		listText.at(i)->RenderText(textShader);
	}
	if (onSoundNen == true) {
		onNhacNen->RenderText(textShader);
	}
	else if (onSoundNen == false) {
		offNhacNen->RenderText(textShader);
	}
	if (onSoundGame == true) {
		onNhacGame->RenderText(textShader);
	}
	else if (onSoundGame == false) {
		offNhacGame->RenderText(textShader);
	}
}
void StateOption::OnMouseOver(int x, int y) {
	if (back->checkChoose(x, y) == true) {
		back->color = Vector4(1.0, 0.5, 1.0, 1.0);
	}
	else back->color = Vector4(1.0, 1.0, 1.0, 1.0);

	//nhac nen
	if (onNhacNen->checkChoose(x, y) == true) {
		onNhacNen->color = Vector4(1.0, 0.5, 1.0, 1.0);
	}
	if (onNhacNen->checkChoose(x, y) == false) {
		onNhacNen->color = Vector4(1.0, 1.0, 1.0, 1.0);
	}
	if (offNhacNen->checkChoose(x, y) == true) {
		offNhacNen->color = Vector4(1.0, 0.5, 1.0, 1.0);
	}
	if (offNhacNen->checkChoose(x, y) == false) {
		offNhacNen->color = Vector4(1.0, 1.0, 1.0, 1.0);
	}

	if (tangVolumeNen->checkChoose(x, y) == true) {
		tangVolumeNen->color = Vector4(1.0, 0.5, 1.0, 1.0);
	}
	else if (tangVolumeNen->checkChoose(x, y) == false) {
		tangVolumeNen->color = Vector4(1.0, 1.0, 1.0, 1.0);
	}
	if (giamVolumeNen->checkChoose(x, y) == true) {
		giamVolumeNen->color = Vector4(1.0, 0.5, 1.0, 1.0);
	}
	else if (giamVolumeNen->checkChoose(x, y) == false) {
		giamVolumeNen->color = Vector4(1.0, 1.0, 1.0, 1.0);
	}

	//nhac game
	if (onNhacGame->checkChoose(x, y) == true) {
		onNhacGame->color = Vector4(1.0, 0.5, 1.0, 1.0);
	}
	if (onNhacGame->checkChoose(x, y) == false) {
		onNhacGame->color = Vector4(1.0, 1.0, 1.0, 1.0);
	}
	if (onNhacGame->checkChoose(x, y) == true) {
		onNhacGame->color = Vector4(1.0, 0.5, 1.0, 1.0);
	}
	if (onNhacGame->checkChoose(x, y) == false) {
		onNhacGame->color = Vector4(1.0, 1.0, 1.0, 1.0);
	}

	if (tangVolumeGame->checkChoose(x, y) == true) {
		tangVolumeGame->color = Vector4(1.0, 0.5, 1.0, 1.0);
	}
	else if (tangVolumeGame->checkChoose(x, y) == false) {
		tangVolumeGame->color = Vector4(1.0, 1.0, 1.0, 1.0);
	}
	if (giamVolumeGame->checkChoose(x, y) == true) {
		giamVolumeGame->color = Vector4(1.0, 0.5, 1.0, 1.0);
	}
	else if (giamVolumeGame->checkChoose(x, y) == false) {
		giamVolumeGame->color = Vector4(1.0, 1.0, 1.0, 1.0);
	}
}
void StateOption::OnMouseClick(int x, int y) {
	if (back->checkChoose(x, y) == true) {
		back->isChoose = true;
	}
	if (back->checkChoose(x, y) == false) {
		back->isChoose = false;
	}
	// nhac nen
	if (onSoundNen == true && onNhacNen->checkChoose(x, y) == true) {
		onSoundNen = false;
	}
	else if (onSoundNen == false && offNhacNen->checkChoose(x, y) == true) {
		onSoundNen = true;
	}
	// nhac game
	if (onSoundGame == true && onNhacGame->checkChoose(x, y) == true) {
		onSoundGame = false;
	}
	else if (onSoundGame == false && offNhacGame->checkChoose(x, y) == true) {
		onSoundGame = true;
	}

	//change nen
	if (giamVolumeNen->checkChoose(x, y) == true) {
		volumeNen -= 5;
		if (volumeNen <= 0) volumeNen = 0;
	}
	if (tangVolumeNen->checkChoose(x, y) == true) {
		volumeNen += 5;
		if (volumeNen >= 100) volumeNen = 100;
	}
	//change game
	if (giamVolumeGame->checkChoose(x, y) == true) {
		volumeGame -= 5;
		if (volumeGame <= 0) volumeGame = 0;
	}
	if (tangVolumeGame->checkChoose(x, y) == true) {
		volumeGame += 5;
		if (volumeGame >= 100) volumeGame = 100;
	}
}
void StateOption::CleanUp() {
	delete modelLogo;
	delete textureLogo;
	for (int i = 0; i < listText.size(); i++) {
		delete listText.at(i);
	}
	delete onNhacGame;
	delete offNhacGame;
	delete onNhacNen;
	delete offNhacNen;
}