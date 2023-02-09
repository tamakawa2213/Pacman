#pragma once
#include "Character.h"

class AStar2D;

//ŸŸŸ‚ğŠÇ—‚·‚éƒNƒ‰ƒX
class Enemy : public Character
{
	int Count_;
	AStar2D* pAst_;
	void Input() override;
	void Search();
	void InitChild() override;
public:
	Enemy(GameObject* parent);
	~Enemy();
};