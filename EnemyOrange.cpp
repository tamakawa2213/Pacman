#include "EnemyOrange.h"
#include "Engine/Model.h"

EnemyOrange::EnemyOrange(GameObject* parent)
	:Enemy(parent, "EnemyOrange", 0, 1.0f, 0)
{
	Visibility = 0;
	SightWidth = 1.0f;
}

EnemyOrange::~EnemyOrange()
{
}

void EnemyOrange::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_, { 0.5f, 0.5f, 0 }, 1, 1);
}
