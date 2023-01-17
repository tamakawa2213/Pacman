#pragma once
#include "Engine/GameObject.h"
#include "Engine/CsvReader.h"

class Stage : public GameObject
{
	int hModel_[2];    //モデル番号
	int map_ [15][15];
	CsvReader csv;
public:
	//コンストラクタ
	Stage(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	//壁or床
	bool IsWall(float x, float z);
};

