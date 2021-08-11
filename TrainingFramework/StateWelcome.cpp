#include"stdafx.h"
#include"StateWelcome.h"

void StateWelcome::init() {
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
	loading->init();
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
void StateWelcome::Draw(Shaders s) {
	loading->RenderText(s);
}
void StateWelcome::DrawLogo(Shaders ss) {
	glUseProgram(ss.program);

	glBindTexture(GL_TEXTURE_2D, textureLogo->mTextureId);
	glBindBuffer(GL_ARRAY_BUFFER, modelLogo->mVBO);
	if (ss.positionAttribute != -1)
	{
		glEnableVertexAttribArray(ss.positionAttribute);
		glVertexAttribPointer(ss.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}
	if (ss.uvAttribute != -1)
	{
		glEnableVertexAttribArray(ss.uvAttribute);
		glVertexAttribPointer(ss.uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(2 * sizeof(Vector3)));
	}
	Matrix pos, scale, mvp;
	scale.SetScale(0.5, 0.5, 0.5);
	pos.SetTranslation(0, 0, 0);
	mvp = scale * pos;
	glUniformMatrix4fv(ss.u_MVP, 1, GL_FALSE, *mvp.m);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, modelLogo->mIBO);
	glDrawElements(GL_TRIANGLES, modelLogo->mNumberOfIndices, GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
