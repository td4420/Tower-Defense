#include "stdafx.h"
#include "Frame.h"

Frame::Frame()
{
	o_Model = new Model("../Resources/model.nfg");
	o_Texture.push_back(new Texture("../ResourcesPacket/Textures/frame2.tga"));
}