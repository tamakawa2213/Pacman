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

	SAFE_DELETE(data);
}

void ResultScene::Update()
{
}

void ResultScene::Draw()
{
	pText->Draw(XMFLOAT2( 0,50 ), "Score : %.3g", Time::GetTimef());
}

void ResultScene::Release()
{
	SAFE_DELETE(pText);
	SAFE_RELEASE(pText);
}
