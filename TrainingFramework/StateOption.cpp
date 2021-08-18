#include"stdafx.h"
#include"StateOption.h"
#include<iostream>
void StateOption::init() {
	onSound = true;
	back->init();
	nhacNen->init();
	onNhacNen->init();
	offNhacNen->init();
	changeNhacNen->init();


	listText.push_back(back);
	listText.push_back(nhacNen);
	
	listText.push_back(changeNhacNen);
	//listText.push_back(onNhacNen);
	//listText.push_back(offNhacNen);
}
void StateOption::Update(float deltaTime) {

}
void StateOption::Draw(Shaders textShader, Shaders shapeShader) {
	for (int i = 0; i < listText.size(); i++) {
		listText.at(i)->RenderText(textShader);
	}
	if (onSound == true) {
		onNhacNen->RenderText(textShader);
	}
	if (onSound == false) {
		offNhacNen->RenderText(textShader);
	}
	std::cout << onSound;
}
void StateOption::OnMousOver(int x, int y) {
	if (back->checkChoose(x, y) == true) {
		back->color = Vector4(0.6, 0.4, 0.5, 1.0);
	}
	if (back->checkChoose(x, y) == false) {
		back->color = Vector4(0.5, 0.5, 0.5, 0.5);
	}
	if (onNhacNen->checkChoose(x, y) == true) {
		onNhacNen->color = Vector4(0.6, 0.4, 0.5, 1.0);
	}
	if (onNhacNen->checkChoose(x, y) == false) {
		onNhacNen->color = Vector4(0.5, 0.5, 0.5, 0.5);
	}
	if (offNhacNen->checkChoose(x, y) == true) {
		offNhacNen->color = Vector4(0.6, 0.4, 0.5, 1.0);
	}
	if (offNhacNen->checkChoose(x, y) == false) {
		offNhacNen->color = Vector4(0.5, 0.5, 0.5, 0.5);
	}
}
void StateOption::OnMouseClick(int x, int y) {
	if (back->checkChoose(x, y) == true) {
		back->isChoose = true;
	}
	if (back->checkChoose(x, y) == false) {
		back->isChoose = false;
	}
	if (onSound == true && onNhacNen->checkChoose(x, y) == true) {
		onSound = false;
	}
	else if (onSound == false && offNhacNen->checkChoose(x, y) == true) {
		onSound = true;
	}
}