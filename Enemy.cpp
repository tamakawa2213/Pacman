#include "Enemy.h"
#include "Engine/Math.h"
#include "Engine/Model.h"
#include "Graphics/imgui.h"
#include "Player.h"
#include "PlayerState.h"
#include "Stage.h"

namespace
{
	const XMVECTOR sight = { 0,0,-1,0 };		//視線ベクトル
	const float Visibility = 10;				//視程
	const float SightWidth = 0.5f;				//視界の広さ
	const float MovingSpeed = 0.1f;				//移動速度
	float checkZ_ = 0.3f;
}

Enemy::Enemy(GameObject* parent)
	: GameObject(parent, "Enemy"), Discover_(false), pStage(nullptr)
{
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	MLoad(hModel_, "Assets\\Parrot.fbx");
	pStage = (Stage*)FindObject("Stage");
	transform_.rotate_.x = 90;
	transform_.position_ = { 10,0,10 };
	transform_.scale_ = { 0.25f,0.25f,0.25f };
}

void Enemy::Update()
{
	CalcInSight();
	if (Discover_)
	{
		StateDiscovered();
	}
	else
	{
		StateUndiscovered();
	}
	JudgeWall();
	ShowGraphical();
}

void Enemy::Draw()
{
	Model::Draw(hModel_, transform_);
}

void Enemy::Release()
{
}

void Enemy::CalcInSight()
{
	//視線ベクトルをtransformに合わせて回転
	XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
	XMVECTOR s = XMVector3Normalize(XMVector3TransformCoord(sight, mRotate));

	//playerとの距離と内積を測定
	XMFLOAT3 pl = PlayerState::GetPlayerPosition();
	XMVECTOR p = XMVector3Normalize(XMLoadFloat3(&pl) - XMLoadFloat3(&transform_.position_));
	float l = XMVectorGetX(XMVector3Dot(s, p));

	//視線ベクトルとplayerの内積と距離から発見状態かどうかを判定
	if (l > SightWidth && Math::GetDistance(transform_.position_, pl) < Visibility)
	{
		Discover_ = true;
	}
	else
	{
		Discover_ = false;
	}

}

void Enemy::ShowGraphical()
{
	ImGui::Begin("Enemy");
	if (Discover_)
	{
		ImGui::Text("Discovered");
	}
	else
	{
		ImGui::Text("lose");
	}
	ImGui::End();
}

void Enemy::StateDiscovered()
{
}

void Enemy::StateUndiscovered()
{
	//transform_.rotate_.y++;
	XMVECTOR m = { 0,0,-0.1f,0 };
	XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
	m = XMVector3TransformCoord(m, mRotate);
	m = XMVector3Normalize(m);
	m *= MovingSpeed;
	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
	vPos += m;
	XMStoreFloat3(&transform_.position_, vPos);
}

void Enemy::JudgeWall()
{
	float checkX, checkZ;

	//右部
	checkX = transform_.position_.x + 1.3f;
	checkZ = transform_.position_.z;

	if (pStage->IsWall(checkX, checkZ)) {
		transform_.position_.x = (float)((int)(transform_.position_.x + 0.5f)) - 0.3f;
	}
	else if (pStage->IsWall(checkX - 0.6f, checkZ)) {
		//左部
		transform_.position_.x = (float)((int)(transform_.position_.x + 0.5f)) + 0.3f;
	}
	//下部
	checkX = transform_.position_.x + 1.0f;
	checkZ -= checkZ_;

	if (pStage->IsWall(checkX, checkZ)) {
		transform_.position_.z = (float)((int)(transform_.position_.z + 0.5f)) + 0.3f;
	}
	else if (pStage->IsWall(checkX, checkZ + 0.6f)) {
		//上部
		transform_.position_.z = (float)((int)(transform_.position_.z + 0.5f)) - 0.3f;
	}
}
