#pragma once
#include "Character.h"

//���������Ǘ�����N���X
class Player : public Character
{
	void Input() override;
public:
	Player(GameObject* parent);
	~Player();
};