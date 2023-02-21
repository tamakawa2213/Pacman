#include "EnemyRed.h"

EnemyRed::EnemyRed(GameObject* parent)
	:Enemy(parent, "EnemyRed")
{
	Visibility = 7;
	SightWidth = 0.3f;
}

EnemyRed::~EnemyRed()
{
}
