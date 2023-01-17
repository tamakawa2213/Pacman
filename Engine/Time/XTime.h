#pragma once

class Transform;

/// <summary>
/// DirectX環境が必要だが画面表示が可能なTime
/// </summary>
namespace XTime
{
	//初期化(Mainで初期化)
	void Initialize(int FPS);

	//更新(Mainで呼び出し)
	void Update();

	void Reset();

	void Lock();

	void UnLock();

	//秒のみ表示にするかどうか
	//true = 秒のみ
	//false = 値に応じて時/分の表示
	void SetDisplayMode(bool Mode);

	//第一引数 : 表示するTransform 第二引数 : 小数点以下何桁を表示するか
	void Draw(Transform tr, int digit);

	//呼び出し時点の時間を取得
	int GetTimei();
	float GetTimef();
	double GetTimew();
};