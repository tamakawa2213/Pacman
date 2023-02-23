#include "EnemyBlue.h"
#include "Engine/Model.h"

EnemyBlue::EnemyBlue(GameObject* parent)
	:Enemy(parent, "EnemyBlue", 7.0f, 0.7f, 40)
{
}

EnemyBlue::~EnemyBlue()
{
}

void EnemyBlue::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_, { 0, 0, 0.5f }, 1, 1);
}
