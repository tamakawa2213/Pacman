#include "Stage.h"
#include "PlayScene.h"
#include "Engine/Model.h"

//コンストラクタ
Stage::Stage(GameObject* parent)
	: GameObject(parent, "Stage"), map_()
{
	hModel_[0] = -1;
	hModel_[1] = -1;
}

//初期化
void Stage::Initialize()
{
	//モデルデータのロード
	hModel_[0] = Model::Load("Assets\\Floor.fbx");//0なら床
	assert(hModel_[0] >= 0);

	hModel_[1] = Model::Load("Assets\\Wall.fbx");//1なら壁
	assert(hModel_[1] >= 0);

	//transform_.scale_ = { 10,1,10 };
	csv.Load("Assets\\Map.csv");
}

//更新
void Stage::Update()
{
}

//描画
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

//開放
void Stage::Release()
{
}

//壁or床
bool Stage::IsWall(float x, float z)
{
	return (map_ [(int)x][(int)z] == 1);
}
