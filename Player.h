#pragma once
#include "Character.h"

//ŸŸŸ‚ğŠÇ—‚·‚éƒNƒ‰ƒX
class Player : public Character
{
	void Input() override;
public:
	Player(GameObject* parent);
	~Player();
};