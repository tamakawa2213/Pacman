#include "PlayScene.h"
#include "EnemyRed.h"
#include "EnemyBlue.h"
#include "EnemyOrange.h"
#include "Stage.h"
#include "Player.h"
#include "Engine/Camera.h"
#include "Engine/SceneManager.h"

//コンストラクタ
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
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
}

//更新
void PlayScene::Update()
{
	
}

//描画
void PlayScene::Draw()
{
}

//開放
void PlayScene::Release()
{
}