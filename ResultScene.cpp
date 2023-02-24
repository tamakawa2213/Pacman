#include "ResultScene.h"
#include "Engine/Time/Time.h"

ResultScene::ResultScene(GameObject* parent)
	:GameObject(parent, "ResultScene"), pText(nullptr)
{
}

ResultScene::~ResultScene()
{
}

void ResultScene::Initialize()
{
	FontData* data = new FontData();
	data->fontSize = 10;
	pText = new Text(data);
	pText->Initialize();
}

void ResultScene::Update()
{
}

void ResultScene::Draw()
{
	pText->Draw(XMFLOAT3( 0,0,0 ), "Score : %g", Time::GetTimef());
}

void ResultScene::Release()
{
}
