#pragma once
#include "Character.h"

//���������Ǘ�����N���X
class Enemy : public Character
{
	void Input() override;
public:
	Enemy(GameObject* parent);
	~Enemy();
};