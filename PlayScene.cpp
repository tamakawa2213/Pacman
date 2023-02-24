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
	: GameObject(parent, "PlayScene"), pText(nullptr)
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

	FontData* data = new FontData();
	data->fontSize = 5;
	pText = new Text(data);
	pText->Initialize();

	//�t�H���g�f�[�^�����
	SAFE_DELETE(data);
}

//�X�V
void PlayScene::Update()
{
	
}

//�`��
void PlayScene::Draw()
{
	pText->Draw(XMFLOAT3(0, 0, 0), "%.3g", Time::GetTimef());
}

//�J��
void PlayScene::Release()
{
	SAFE_RELEASE(pText);
	SAFE_DELETE(pText);
}