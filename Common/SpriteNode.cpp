/*
* Name: Gastello, Andrii
* Date Created: 01.28.2023
* Last Modified: 04.10.2023
*/
#include "SpriteNode.h"
#include "Game.hpp"

SpriteNode::SpriteNode(Game* game, States::ID id) : Entity(game, id)
{
}

void SpriteNode::drawCurrent() const
{
	renderer->Mat = game->getMaterials()[mSprite].get();
	renderer->World = getTransform();
	renderer->NumFramesDirty++;
}

void SpriteNode::buildCurrent()
{
	auto render = std::make_unique<RenderItem>();
	renderer = render.get();
	renderer->World = getTransform();
	XMStoreFloat4x4(&renderer->TexTransform, XMMatrixScaling(mTiling.x, mTiling.y, mTiling.z));
	renderer->ObjCBIndex = game->getRenderItems().size();
	renderer->Mat = game->getMaterials()[mSprite].get();
	renderer->Geo = game->getGeometries()["boxGeo"].get();
	render->StateID = state;
	renderer->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	renderer->IndexCount = renderer->Geo->DrawArgs["box"].IndexCount;
	renderer->StartIndexLocation = renderer->Geo->DrawArgs["box"].StartIndexLocation;
	renderer->BaseVertexLocation = renderer->Geo->DrawArgs["box"].BaseVertexLocation;

	game->getRenderItems().push_back(std::move(render));
}
