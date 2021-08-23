#include"stdafx.h"
#include"StateLogo.h"

void StateLogo::init() {
	FILE* file;
	file = fopen("../ResourcesPacket/StateWelcome.txt", "r");
	char modelfile[50], texturefile[50];

	fscanf(file, "Model: %s\n", &modelfile);
	modelLogo = new Model(modelfile);
	modelLogo->Init();
	fscanf(file, "Texture: %s\n", &texturefile);
	textureLogo = new Texture(texturefile);
	textureLogo->mTgaFilePath = texturefile;
	textureLogo->Init();
	scale.SetScale(1, 1, 1);
	trans.SetTranslation(-0.5, -0.5, 0);
	mvp = scale * trans;
}
void StateLogo::Update(float deltaTime) {
	//if (time > 0) {
	//	Sleep(200);
	//	time--;
	//}
}
void StateLogo::Draw(Shaders* textShader, Shaders* shapeShader) {
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