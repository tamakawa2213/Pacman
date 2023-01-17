#pragma once
#include "Engine/GameObject.h"

class Stage;

class Enemy : public GameObject
{
	Stage* pStage;
	bool Discover_;		//発見状態かどうか

	//プレイヤーが視界に入っているかの計算
	void CalcInSight();

	void ShowGraphical();

	//発見状態の処理
	void StateDiscovered();

	//未発見状態の処理
	void StateUndiscovered();

	void JudgeWall();
public:
	Enemy(GameObject* parent);

	~Enemy();

	//初期化
	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;
};