#pragma once
#include "Character.h"

//ŸŸŸ‚ğŠÇ—‚·‚éƒNƒ‰ƒX
class Enemy : public Character
{
	void Input() override;
public:
	Enemy(GameObject* parent);
	~Enemy();
};