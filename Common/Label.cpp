#include "Label.h"
#include "Game.hpp"

Label::Label(Game* game, std::string labelName, States::ID id) : SceneNode(game, id)
                                                                 , mScrollSpeed(1.0f)
{
	mSprite = labelName;
}

void Label::updateCurrent(const GameTimer& gt)
{
}

void Label::buildCurrent()
{
	auto render = std::make_unique<RenderItem>();
	renderer = render.get();
	renderer->World = getTransform();
	renderer->ObjCBIndex = game->getRenderItems().size();
	renderer->Mat = game->getMaterials()[mSprite].get();
	renderer->Geo = game->getGeometries()["boxGeo"].get();
	renderer->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	renderer->StateID = state;
	renderer->IndexCount = renderer->Geo->DrawArgs["box"].IndexCount;
	renderer->StartIndexLocation = renderer->Geo->DrawArgs["box"].StartIndexLocation;
	renderer->BaseVertexLocation = renderer->Geo->DrawArgs["box"].BaseVertexLocation;

	game->getRenderItems().push_back(std::move(render));
}

void Label::drawCurrent() const
{
}
