#include "EnemyBlue.h"

EnemyBlue::EnemyBlue(GameObject* parent)
	:Enemy(parent, "EnemyBlue")
{
	Visibility = 12;
	SightWidth = 0.7f;
}

EnemyBlue::~EnemyBlue()
{
}
