#include "Character.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Stage.h"

void Character::GoAbove()
{
    transform_.rotate_.y = 0;
}

void Character::GoUnder()
{
    transform_.rotate_.y = 180.0f;
}

void Character::GoLeft()
{
    transform_.rotate_.y = -90.0f;
}

void Character::GoRight()
{
    transform_.rotate_.y = 90.0f;
}

//コンストラクタ
Character::Character(GameObject* parent)
    :Character(parent, "Character")
{
}

Character::Character(GameObject* parent, std::string name)
    : GameObject(parent, name), hModel_(-1), move_(0.0625f), front_{ 0,0,1,0 }, checkZ_(0.3f), pStage(nullptr), intPosX(0), intPosZ(0),
    movingDist_(0)
{
}

//デストラクタ
Character::~Character()
{
}

//初期化
void Character::Initialize()
{

    if (GetObjectName() == "Player")
    {
        transform_.position_.x = 0.5f;
        transform_.position_.z = 1.5f;
    }
    else
    {
        transform_.position_.x = 8.5f;
        transform_.position_.z = 1.5f;
    }
    intPosX = (int)((transform_.position_.x + 0.5f) * 10);
    intPosZ = (int)((transform_.position_.z - 0.5f) * 10);

    pStage = (Stage*)FindObject("Stage");
    assert(pStage != nullptr);

    InitChild();
}

//更新
void Character::Update()
{
    //移動前の位置ベクトル
    XMVECTOR prevPosition = XMLoadFloat3(&transform_.position_);

    Input();

    XMVECTOR vMove = { 0, 0, 1, 0 };
    XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    vMove = XMVector3Normalize(XMVector3TransformCoord(vMove, mRotate)) * move_;
    XMStoreFloat3(&transform_.position_, prevPosition + vMove);

    //////////////////////////////////////////////////////////壁との衝突判定//////////////////////////////////////////////////////

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

    //移動後の位置ベクトル
    XMVECTOR nowPosition = XMLoadFloat3(&transform_.position_);

    //移動ベクトル
    XMVECTOR move = nowPosition - prevPosition;

    //移動ベクトルの長さの測定
    XMVECTOR length = XMVector3Length(move);

    movingDist_ = XMVectorGetY(length);

    intPosX = (int)(transform_.position_.x + 1);
    intPosZ = (int)transform_.position_.z;

}

//描画
void Character::Draw()
{
    Model::Draw(hModel_, transform_);
}

//開放
void Character::Release()
{
}