#pragma once

//ゲーム内時間を管理する
namespace GameTime
{
	void Update();
	float GetRelativeTime();
	int RemainingTimes();
	void UpDated();
	bool IsStop();
};