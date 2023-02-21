#include "EnemyOrange.h"

EnemyOrange::EnemyOrange(GameObject* parent)
	:Enemy(parent, "EnemyOrange")
{
	Visibility = 0;
	SightWidth = 1.0f;
}

EnemyOrange::~EnemyOrange()
{
}
