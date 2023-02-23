#include "EnemyRed.h"
#include "Engine/Model.h"

EnemyRed::EnemyRed(GameObject* parent)
	:Enemy(parent, "EnemyRed", 4.0f, 0.3f, 65)
{
}

EnemyRed::~EnemyRed()
{
}

void EnemyRed::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_, { 0.5f, 0, 0 }, 1, 1);
}
