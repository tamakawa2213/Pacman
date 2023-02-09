#include "Stage.h"
#include "PlayScene.h"
#include "Engine/Model.h"

//�R���X�g���N�^
Stage::Stage(GameObject* parent)
	: GameObject(parent, "Stage"), map_()
{
	hModel_[0] = -1;
	hModel_[1] = -1;
}

//������
void Stage::Initialize()
{
	//���f���f�[�^�̃��[�h
	hModel_[0] = Model::Load("Assets\\Floor.fbx");//0�Ȃ珰
	assert(hModel_[0] >= 0);

	hModel_[1] = Model::Load("Assets\\Wall.fbx");//1�Ȃ��
	assert(hModel_[1] >= 0);

	//transform_.scale_ = { 10,1,10 };
	csv.Load("Assets\\Map.csv");
}

//�X�V
void Stage::Update()
{
}

//�`��
void Stage::Draw()
{
	for (int x = 0; x < 15; x++) {
		for (int z = 0; z < 15; z++) {
			int type = csv.GetValue(x, z);
			map_[x][z] = csv.GetValue(x, z);
			transform_.position_.x = (float)x - 1;
			transform_.position_.z = (float)z;
			Model::Draw(hModel_[type], transform_);
		}
	}
}

//�J��
void Stage::Release()
{
}

//��or��
bool Stage::IsWall(float x, float z)
{
	return (map_ [(int)x][(int)z] == 1);
}
