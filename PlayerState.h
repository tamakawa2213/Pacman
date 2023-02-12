#pragma once
#include <DirectXMath.h>

using namespace DirectX;

namespace PlayerState
{
	void SetPlayerPosition(XMFLOAT3 pos);
	void SetPlayerPosition(int x, int z);
	XMFLOAT3 GetPlayerPosition();
	int GetPlayerPositionX();
	int GetPlayerPositionZ();
};