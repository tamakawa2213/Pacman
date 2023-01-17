#pragma once
#include <DirectXMath.h>

using namespace DirectX;

namespace PlayerState
{
	void SetPlayerPosition(XMFLOAT3 pos);
	XMFLOAT3 GetPlayerPosition();
};