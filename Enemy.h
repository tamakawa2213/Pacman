#pragma once
#include "Character.h"

class AStar2D;

//◆◆◆を管理するクラス
class Enemy : public Character
{
	int Count_;
	AStar2D* pAst_;
	bool Discover_;

	int PrevIntX_;
	int PrevIntZ_;

	int ChaseCount_;
	int Bored_;			//飽きにくさ

	std::list<std::pair<int, int>> route_;

	void Input() override;
	void InitChild() override;

	//プレイヤーが視界に入っているかの計算
	void CalcInSight();

	//プレイヤーを捜索する
	void Search();
	//プレイヤーを追跡する
	void Chase();

protected:

	float Visibility;			//視程
	float SightWidth;		//視界の広さ

public:
	Enemy(GameObject* parent);
	Enemy(GameObject* parent, std::string name, float vis, float wid, int bored);
	~Enemy();
};