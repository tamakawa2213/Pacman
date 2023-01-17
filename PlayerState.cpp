#include "PlayerState.h"

namespace
{
	XMFLOAT3 PlayerPos = {0,0,0};
}

namespace PlayerState
{
	void SetPlayerPosition(XMFLOAT3 pos)
	{
		PlayerPos = pos;
	}

	XMFLOAT3 GetPlayerPosition()
	{
		return PlayerPos;
	}
}
