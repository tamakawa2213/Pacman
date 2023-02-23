#pragma once
#include "Enemy.h"

class EnemyRed : public Enemy
{
public:
	EnemyRed(GameObject* parent);
	~EnemyRed();

	void Draw() override;
};