#pragma once
#include "Direct3D.h"
#include <DirectXMath.h>

using namespace DirectX;

//-----------------------------------------------------------
//カメラ
//-----------------------------------------------------------
namespace Camera
{
	//初期化（プロジェクション行列作成）
	void Initialize();

	//更新（ビュー行列作成）
	void Update();

	//視点（カメラの位置）を設定
	void SetPosition(XMVECTOR position);

	//焦点（見る位置）を設定
	void SetTarget(XMVECTOR target);

	//ビュー行列を取得
	XMMATRIX GetViewMatrix();

	//プロジェクション行列を取得
	XMMATRIX GetProjectionMatrix();

	//カメラの位置を取得
	XMVECTOR GetPosition();

	//カメラの焦点を取得
	XMVECTOR GetTarget();

	//カメラの視線ベクトルを取得
	XMVECTOR GetSight();

	XMVECTOR GetCameraVecPosition();

	XMVECTOR GetCameraVecTarget();
};