#include"stdafx.h"
#include"StateHelp.h"

void StateHelp::init() {
	back = new Text("B A C K", 10, Globals::screenHeight - 32.5, "../Font/OceanSummer.ttf", 1, 1, Vector4(1.0, 1.0, 1.0, 1.0), 48);
	back->init();
	//FILE* file;
	//file = fopen("../ResourcesPacket/help.txt", "r");

	model = new Model("../ResourcesPacket/Models/Button.nfg");
	model->Init();
	
	texture = new Texture("../ResourcesPacket/Textures/statehelp.tga");
	texture->Init();

	scale.SetScale(2, 4, 3);
	pos.SetTranslation(-1, -3, 0);
	mvp = scale * pos;

}
void StateHelp::Update(float deltaTime) {

}
void StateHelp::Draw(Shaders* textShader, Shaders* shapeShader) {

	glUseProgram(shapeShader->program);

	glBindTexture(GL_TEXTURE_2D, texture->mTextureId);
	glBindBuffer(GL_ARRAY_BUFFER, model->mVBO);
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
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->mIBO);
	glDrawElements(GL_TRIANGLES, model->mNumberOfIndices, GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	back->RenderText(textShader);
}
void StateHelp::OnMouseOver(int x, int y) {
	if (back->checkChoose(x, y) == true) {
		back->color = Vector4(1.0, 0.5, 1.0, 1.0);
	}
	if (back->checkChoose(x, y) == false) {
		back->color = Vector4(1.0, 1.0, 1.0, 1.0);
	}
}
void StateHelp::OnMouseClick(int x, int y) {
	if (back->checkChoose(x, y) == true) {
		back->isChoose = true;
	}
	if (back->checkChoose(x, y) == false) {
		back->isChoose = false;
	}
}
void StateHelp::CleanUp() {
	delete model;
	delete[] texture->mTgaFilePath;
	delete texture;

	back->CleanUp();
	delete back;
}