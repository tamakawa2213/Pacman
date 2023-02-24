#include "PlayScene.h"
#include "EnemyRed.h"
#include "EnemyBlue.h"
#include "EnemyOrange.h"
#include "Stage.h"
#include "Player.h"
#include "Engine/Camera.h"
#include "Engine/SceneManager.h"
#include "Engine/Time/Time.h"

//�R���X�g���N�^
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

//������
void PlayScene::Initialize()
{
	Instantiate<Stage>(this);
	Instantiate<Player>(this);
	Instantiate<EnemyRed>(this);
	Instantiate<EnemyOrange>(this);
	Instantiate<EnemyBlue>(this);

	Time::Reset();
	Time::UnLock();
}

//�X�V
void PlayScene::Update()
{
	
}

//�`��
void PlayScene::Draw()
{
}

//�J��
void PlayScene::Release()
{
}