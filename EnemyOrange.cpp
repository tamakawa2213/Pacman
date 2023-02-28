#include "EnemyOrange.h"
#include "Engine/Model.h"

EnemyOrange::EnemyOrange(GameObject* parent)
	:Enemy(parent, "EnemyOrange", 0, 1.0f, 0)
{
}

EnemyOrange::~EnemyOrange()
{
}

void EnemyOrange::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_, { 0.5f, 0.5f, 0 }, 1, 1);
}
