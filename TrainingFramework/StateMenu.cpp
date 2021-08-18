#include"stdafx.h"
#include"StateMenu.h"
#include<iostream>
#include"Vertex.h"
using namespace std;

void StateMenu::init() {
	FILE* file;
	file = fopen(fileState, "r");
	char modelfile[50], texturefile[50];
	fscanf(file, "Model: %s\n", &modelfile);
	modelLogo = new Model(modelfile);
	modelLogo->Init();
	fscanf(file, "Texture: %s\n", &texturefile);
	textureLogo = new Texture();
	textureLogo->mTgaFilePath = texturefile;
	textureLogo->Init();
	play = new Text("PLAY", 310, 450, "../Font/OceanSummer.ttf", 1, 1, Vector4(0.5, 0.5, 0.5, 0.5), 68);
	options = new Text("OPTIONS", 310, 400, "../Font/OceanSummer.ttf", 1, 1, Vector4(0.5, 0.5, 0.5, 0.5), 68);
	helps = new	Text("HELPS", 310, 350, "../Font/OceanSummer.ttf", 1, 1, Vector4(0.5, 0.5, 0.5, 0.5), 68);
	quit = new	Text("QUIT", 310, 300, "../Font/OceanSummer.ttf", 1, 1, Vector4(0.5, 0.5, 0.5, 0.5), 68);
	play->init();
	options->init();
	helps->init();
	quit->init();
	listText.push_back(play);
	listText.push_back(options);
	listText.push_back(helps);
	listText.push_back(quit);
	/*int NoT, ID, scaleX, scaleY, posX, posY;
	Vector4 color;
	char font[50];
	char text[10];
	Text* subText;
	int size;
	fscanf(file, "NumOfText: %d\n", &NoT);
	for (int i = 0; i < NoT; i++) {
		fscanf(file, "ID: %d\n", &ID);
		fscanf(file, "TEXT: %s\n", &text);
		fscanf(file, "POSX,Y: %d %d\n", &posX, &posY);
		fscanf(file, "FILEFONT: %s\n", &font);
		fscanf(file, "SCALE: %d %d\n", &scaleX, &scaleY);
		fscanf(file, "COLOR: %f %f %f %f\n", &color.x, &color.y, &color.z, &color.w);
		fscanf(file, "SIZE: %d\n", &size);
		subText = new Text(text, posX, posY, font, scaleX, scaleY, color,size);
		subText->init();
		listText.push_back(subText);
	}*/
}
void StateMenu::Update(float deltaTime) {

}

void StateMenu::Draw(Shaders textShader, Shaders shapeShader) {

	/*glUseProgram(shapeShader.program);

	glBindTexture(GL_TEXTURE_2D, textureLogo->mTextureId);
	glBindBuffer(GL_ARRAY_BUFFER, modelLogo->mVBO);
	if (shapeShader.positionAttribute != -1)
	{
		glEnableVertexAttribArray(shapeShader.positionAttribute);
		glVertexAttribPointer(shapeShader.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}
	if (shapeShader.uvAttribute != -1)
	{
		glEnableVertexAttribArray(shapeShader.uvAttribute);
		glVertexAttribPointer(shapeShader.uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(2 * sizeof(Vector3)));
	}
	Matrix pos, scale, mvp;
	scale.SetScale(0.5, 0.5, 0.5);
	pos.SetTranslation(0, 0, 0);
	mvp = scale * pos;
	glUniformMatrix4fv(shapeShader.u_MVP, 1, GL_FALSE, *mvp.m);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, modelLogo->mIBO);
	glDrawElements(GL_TRIANGLES, modelLogo->mNumberOfIndices, GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);*/
	
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
			listText.at(i)->color = Vector4(0.6, 1, 0.4, 1);
		}
		if (listText.at(i)->checkChoose(x, y) == false) {
			listText.at(i)->color = Vector4(0.5, 0.5, 0.5, 0.5);
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