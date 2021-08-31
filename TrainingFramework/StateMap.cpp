#include"stdafx.h"
#include"StateMap.h"

void StateMap::init() {
	back = new Text("B A C K", 10, Globals::screenHeight - 32.5, "../Font/OceanSummer.ttf", 1, 1, Vector4(1.0, 1.0, 1.0, 1.0), 48);
	back->init();
	M1 = new Text("MAP 1", 216, 400, "../Font/OceanSummer.ttf", 1, 1, Vector4(1.0, 1.0, 1.0, 1.0), 68);
	M1->init();
	
	M2 = new Text("MAP 2", 600, 400, "../Font/OceanSummer.ttf", 1, 1, Vector4(1.0, 1.0, 1.0, 1.0), 68);
	M2->init();

	myShader->Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");

	bg = new Object();
	bg->o_Model = new Model("../Resources/modelBackground.nfg");
	bg->o_Texture.push_back(new Texture("../ResourcesPacket/Textures/bgPlay.tga"));
	bg->o_shaders = myShader;
	bg->Build(0, 0);
	bg->InitObject();

	map1 = new Object();
	map1->o_Model = new Model("../Resources/modelBackground.nfg");
	map1->o_Texture.push_back(new Texture("../ResourcesPacket/Textures/Map1.tga"));
	map1->o_shaders = myShader;
	map1->Build(0,0);
	map1->Scale.SetScale(0.2, 0.2, 0.2);
	map1->Translation.SetTranslation(-0.5, 0.5, 0.0);
	map1->MVP = map1->Scale * map1->Translation;
	map1->InitObject();
		
	map2 = new Object();
	map2->o_Model = new Model("../Resources/modelBackground.nfg");
	map2->o_Texture.push_back(new Texture("../ResourcesPacket/Textures/Map2.tga"));
	map2->o_shaders = myShader;
	map2->Build(0, 0);
	map2->Scale.SetScale(0.2, 0.2, 0.2);
	map2->Translation.SetTranslation(0.3, 0.5, 0.0);
	map2->MVP = map1->Scale * map1->Translation;
	map2->InitObject();
}
void StateMap::Update(float deltaTime) {

}
void StateMap::Draw(Shaders* textShader, Shaders* shapeShader) {

	bg->DrawObject();
	map1->DrawObject();
	map2->DrawObject();
	back->RenderText(textShader);
	M1->RenderText(textShader);
	M2->RenderText(textShader);
}
void StateMap::OnMouseOver(int x, int y) {
	if (back->checkChoose(x, y) == true) {
		back->color = Vector4(1.0, 0.5, 1.0, 1.0);
	}
	if (back->checkChoose(x, y) == false) {
		back->color = Vector4(1.0, 1.0, 1.0, 1.0);
	}
	if (M1->checkChoose(x, y) == true) {
		M1->color = Vector4(1.0, 0.5, 1.0, 1.0);
		map1->Scale.SetScale(0.25, 0.25, 0.25);
		map1->MVP = map1->Scale * map1->Translation;
	}
	if (M1->checkChoose(x, y) == false) {
		M1->color = Vector4(1.0, 1.0, 1.0, 1.0);
		map1->Scale.SetScale(0.2, 0.2, 0.2);
		map1->MVP = map1->Scale * map1->Translation;
	}
	if (M2->checkChoose(x, y) == true) {
		M2->color = Vector4(1.0, 0.5, 1.0, 1.0);
		map2->Scale.SetScale(0.25, 0.25, 0.25);
		map2->MVP = map2->Scale * map2->Translation;
	}
	if (M2->checkChoose(x, y) == false) {
		M2->color = Vector4(1.0, 1.0, 1.0, 1.0);
		map2->Scale.SetScale(0.2, 0.2, 0.2);
		map2->MVP = map2->Scale * map2->Translation;
	}
}
void StateMap::OnMouseClick(int x, int y) {
	if (back->checkChoose(x, y) == true) {
		back->isChoose = true;
	}
	if (back->checkChoose(x, y) == false) {
		back->isChoose = false;
	}
	if (M1->checkChoose(x, y) == true) {
		M1->isChoose = true;
		Map = 1;
	}
	if (M1->checkChoose(x, y) == false) {
		M1->isChoose = false;
	}
	if (M2->checkChoose(x, y) == true) {
		M2->isChoose = true;
		Map = 2;
	}
	if (M2->checkChoose(x, y) == false) {
		M2->isChoose = false;
	}
}
void StateMap::CleanUp() {
	delete back;
}