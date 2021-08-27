#include"stdafx.h"
#include"StateMenu.h"
#include<iostream>modelMenu
#include"Vertex.h"
using namespace std;

void StateMenu::init() {
	FILE* file;
	file = fopen("../ResourcesPacket/bgMenu.txt", "r");
	char modelfile[50], texturefile[50];
	fscanf(file, "Model: %s\n", &modelfile);
	modelMenu = new Model(modelfile);
	modelMenu->Init();
	fscanf(file, "Texture: %s\n", &texturefile);
	textureMenu = new Texture();
	textureMenu->mTgaFilePath = texturefile;
	textureMenu->Init();

	scaleM.SetScale(2, 4, 3);
	posM.SetTranslation(-1, -3, 0);
	mvpM = scaleM * posM;

	play = new Text("PLAY", 450, 250, "../Font/OceanSummer.ttf", 1, 1, Vector4(1.0, 1.0, 1.0, 1.0), 68);
	options = new Text("OPTIONS", 450, 200, "../Font/OceanSummer.ttf", 1, 1, Vector4(1.0, 1.0, 1.0, 1.0), 68);
	helps = new	Text("HELPS", 450, 150, "../Font/OceanSummer.ttf", 1, 1, Vector4(1.0, 1.0, 1.0, 1.0), 68);
	quit = new	Text("QUIT", 450, 100, "../Font/OceanSummer.ttf", 1, 1, Vector4(1.0, 1.0, 1.0, 1.0), 68);
	play->init();
	options->init();
	helps->init();
	quit->init();
	listText.push_back(play);
	listText.push_back(options);
	listText.push_back(helps);
	listText.push_back(quit);
	
}
void StateMenu::Update(float deltaTime) {

}

void StateMenu::Draw(Shaders* textShader, Shaders* shapeShader) {
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	

	
	glUseProgram(shapeShader->program);

	glBindTexture(GL_TEXTURE_2D, textureMenu->mTextureId);
	glBindBuffer(GL_ARRAY_BUFFER, modelMenu->mVBO);
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


	glUniformMatrix4fv(shapeShader->u_MVP, 1, GL_FALSE, *mvpM.m);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, modelMenu->mIBO);
	glDrawElements(GL_TRIANGLES, modelMenu->mNumberOfIndices, GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	for (int i = 0; i < listText.size(); i++)
	{
		listText.at(i)->RenderText(textShader);
	}
}
void StateMenu::handleEvent() {

}
void StateMenu::OnMouseOver(int x, int y) {
	for (int i = 0; i < listText.size(); i++)
	{
		if (listText.at(i)->checkChoose(x, y) == true) {
			listText.at(i)->color = Vector4(1.0, 0.5, 1.0, 1.0); // (0.6, 1, 0.4, 1)
		}
		if (listText.at(i)->checkChoose(x, y) == false) {
			listText.at(i)->color = Vector4(1.0, 1.0, 1.0, 1.0);
		}
	}
}
void StateMenu::OnMouseClick(int x, int y) {
	for (int i = 0; i < listText.size(); i++) {
		if (listText.at(i)->checkChoose(x, y) == true) {
			listText.at(i)->isChoose = true;
		}
		if (listText.at(i)->checkChoose(x, y) == false) {
			listText.at(i)->isChoose = false;
		}
	}
}

StateMenu::StateMenu() {

}
StateMenu::~StateMenu() {
}
void StateMenu::CleanUp() {
	delete modelMenu;
	delete textureMenu;
	for (int i = 0; i < listText.size(); i++) {
		delete listText.at(i);
	}
}