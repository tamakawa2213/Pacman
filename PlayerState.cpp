#include "PlayerState.h"

namespace
{
	XMFLOAT3 PlayerPos = {0,0,0};
	int IntPosX = 0;
	int IntPosZ = 0;
}

namespace PlayerState
{
	void SetPlayerPosition(XMFLOAT3 pos)
	{
		PlayerPos = pos;
	}

	void SetPlayerPosition(int x, int z)
	{
		IntPosX = x;
		IntPosZ = z;
	}

	XMFLOAT3 GetPlayerPosition()
	{
		return PlayerPos;
	}
	int GetPlayerPositionX()
	{
		return IntPosX;
	}
	int GetPlayerPositionZ()
	{
		return IntPosZ;
	}
}
