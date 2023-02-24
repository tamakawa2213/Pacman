#include "PlayScene.h"
#include "EnemyRed.h"
#include "EnemyBlue.h"
#include "EnemyOrange.h"
#include "Stage.h"
#include "Player.h"
#include "Engine/Camera.h"
#include "Engine/SceneManager.h"
#include "Engine/Time/Time.h"

//コンストラクタ
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene"), pText(nullptr)
{
}

//初期化
void PlayScene::Initialize()
{
	Instantiate<Stage>(this);
	Instantiate<Player>(this);
	Instantiate<EnemyRed>(this);
	Instantiate<EnemyOrange>(this);
	Instantiate<EnemyBlue>(this);

	Time::Reset();
	Time::UnLock();

	FontData* data = new FontData();
	data->fontSize = 5;
	pText = new Text(data);
	pText->Initialize();

	//フォントデータを解放
	SAFE_DELETE(data);
}

//更新
void PlayScene::Update()
{
	
}

//描画
void PlayScene::Draw()
{
	pText->Draw(XMFLOAT3(0, 0, 0), "%.3g", Time::GetTimef());
}

//開放
void PlayScene::Release()
{
	SAFE_RELEASE(pText);
	SAFE_DELETE(pText);
}