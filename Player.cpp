#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Stage.h"

//コンストラクタ
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"), hModel_(-1), move_(0.1f), front_{ 0,0,1,0 }, checkZ_(0.3f), pStage(nullptr)
{
}

//デストラクタ
Player::~Player()
{
}

//初期化
void Player::Initialize()
{//モデルデータのロード
    hModel_ = Model::Load("Assets\\player.fbx");
    assert(hModel_ >= 0);

    transform_.position_.x = 0.5f;
    transform_.position_.z = 1.5f;
    pStage = (Stage*)FindObject("Stage");
    assert(pStage != nullptr);
}

//更新
void Player::Update()
{
    //移動前の位置ベクトル
    XMVECTOR prevPosition = XMLoadFloat3(&transform_.position_);
    XMVECTOR vMove = {};

    //操作awsdと上下左右キーのどちらでも可
    if (Input::IsKey(DIK_UP) || Input::IsKey(DIK_W))
    {
        vMove += {0, 0, move_, 0};
    }
    if (Input::IsKey(DIK_DOWN) || Input::IsKey(DIK_S))
    {
        vMove -= {0, 0, move_, 0};
    }
    if (Input::IsKey(DIK_RIGHT) || Input::IsKey(DIK_D))
    {
        vMove += {move_, 0, 0, 0};
    }
    if (Input::IsKey(DIK_LEFT) || Input::IsKey(DIK_A))
    {
        vMove -= {move_, 0, 0, 0};
    }
    vMove = XMVector3Normalize(vMove) * move_;
    XMStoreFloat3(&transform_.position_, prevPosition + vMove);
    ////////////////////////////////////////////////////////回転処理////////////////////////////////////////////////////

    //移動後の位置ベクトル
    XMVECTOR nowPosition = prevPosition + vMove;

    //移動ベクトル
    XMVECTOR move = nowPosition - prevPosition;

    //移動ベクトルの長さの測定
    XMVECTOR length = XMVector3Length(move);

    //0.1以上移動してたら回転処理
    if (XMVectorGetY(length) >= 0.1f) {

        //移動ベクトルの正規化
        move = XMVector3Normalize(move);

        //front_とmoveの内積を求める(戻り値はvector)
        XMVECTOR vecDot = XMVector3Dot(front_, move);
        float dot = XMVectorGetX(vecDot);

        //角度を求める(ラジアン)
        float angle = acosf(dot);

        //外積を求める
        XMVECTOR cross = XMVector3Cross(front_, move);

        //外積の結果のyがマイナス (= 左に進んでる)
        if (XMVectorGetY(cross) < 0) {
            angle *= -1;
        }

        //angleで回転させる
        transform_.rotate_.y = angle * 180 / 3.14f;
    }

    //////////////////////////////////////////////////////////壁との衝突判定//////////////////////////////////////////////////////

    float checkX, checkZ;

    //右部
    checkX = transform_.position_.x + 1.3f;
    checkZ = transform_.position_.z;

    if (pStage->IsWall(checkX, checkZ)) {
        transform_.position_.x = (float)((int)(transform_.position_.x + 0.5f)) - 0.3f;
    }
    else if(pStage->IsWall(checkX - 0.6f, checkZ)) {
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

//描画
void Player::Draw()
{
    Model::Draw(hModel_, transform_);
}

//開放
void Player::Release()
{
}