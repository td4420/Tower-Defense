#include"stdafx.h"
#include"StateWelcome.h"

void StateWelcome::init() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	FILE* file;
	file = fopen(fileState, "r");
	char modelfile[50], texturefile[50];
	
	fscanf(file, "Model: %s\n", &modelfile);
	modelLogo = new Model(modelfile);
	modelLogo->Init();
	fscanf(file, "Texture: %s\n", &texturefile);
	textureLogo = new Texture(texturefile);
	textureLogo->mTgaFilePath = texturefile;
	textureLogo->Init();
	loading->init();
	pt->init();
	tapToStart->init();
	scale.SetScale(1, 1, 1);
	trans.SetTranslation(-0.5, -0.1, 1);
	mvp = scale * trans;
}
void StateWelcome::Update(float deltaTime) {
	if (percentLoad < 100) {
		if (percentLoad > 20 && percentLoad < 40 || percentLoad > 60 && percentLoad < 90) {
			Sleep(100);
			percentLoad += 1;
		}
		else percentLoad += 1;
	}
	tmp = std::to_string(percentLoad);
	num_char = tmp.c_str();
	loading->text = num_char;
}
void StateWelcome::Draw(Shaders* textShader, Shaders* shapeShader) {

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	//draw text
	if (percentLoad < 100) {
		loading->RenderText(textShader);
		pt->RenderText(textShader);
		cout << "1\n";
	}
	else tapToStart->RenderText(textShader);
	//draw logo
	
	DrawLogo(shapeShader);
	
}
void StateWelcome::DrawLogo(Shaders* shapeShader) {
	glUseProgram(shapeShader->program);
	glBindBuffer(GL_ARRAY_BUFFER, modelLogo->mVBO);
	glBindTexture(GL_TEXTURE_2D, textureLogo->mTextureId);

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
}
void StateWelcome::OnMouseOver(int x, int y) {
	if (tapToStart->checkChoose(x, y) == true) {
		tapToStart->color = Vector4(0.6, 1, 0.4, 1);
	}
	if (tapToStart->checkChoose(x, y) == false) {
		tapToStart->color = Vector4(0.5, 0.5, 0.5, 0.5);
	}
}
void StateWelcome::OnMouseClick(int x, int y) {
	if (tapToStart->checkChoose(x, y) == true) {
		tapToStart->isChoose = true;
	}
	if (tapToStart->checkChoose(x, y) == false) {
		tapToStart->isChoose = false;
	}
}