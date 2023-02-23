#pragma once
#include "Enemy.h"

class EnemyOrange : public Enemy
{
public:
	EnemyOrange(GameObject* parent);
	~EnemyOrange();

	void Draw() override;
};

