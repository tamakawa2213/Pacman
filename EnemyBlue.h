#pragma once
#include "Enemy.h"

class EnemyBlue : public Enemy
{
public:
	EnemyBlue(GameObject* parent);
	~EnemyBlue();

	void Draw() override;
};

