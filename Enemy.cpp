#include "Enemy.h"
#include "AStar2D.h"
#include "Engine/CsvReader.h"
#include "Engine/Math.h"
#include "PlayerState.h"
#include "Stage.h"

namespace
{
    const XMVECTOR sight = { 0,0,1,0 };		//視線ベクトル
    const float Visibility = 7;				//視程
    const float SightWidth = 0.5f;				//視界の広さ
}

void Enemy::Input()
{
    CalcInSight();

    if (Count_++ >= 16)
    {

        if (Discover_ || !route_.empty())
            Chase();
        else
            Search();


        Count_ = 0;
    }

   
}

void Enemy::Search()
{
    if (rand() % 128 <= 16)
    {
        if (rand() % 2 == 0)
            transform_.rotate_.y += 90;
        else
            transform_.rotate_.y -= 90;

        return;
    }

    if (movingDist_ <= 0)
    {
        if (rand() % 2 == 0)
            transform_.rotate_.y += 90;
        else
            transform_.rotate_.y -= 90;
    }
}

void Enemy::Chase()
{
    if (Math::GetDistance(PlayerState::GetPlayerPosition(), transform_.position_) > 10)
    {
        route_.clear();
    }

    if (Discover_)
    {
        route_.clear();
        pAst_->Reset();
        pAst_->SetStart({ intPosX, intPosZ });
        pAst_->SetGoal({ PlayerState::GetPlayerPositionX(), PlayerState::GetPlayerPositionZ() });
        pAst_->Adjacent(Move{ intPosX, intPosZ });
        pAst_->Route({ PlayerState::GetPlayerPositionX(), PlayerState::GetPlayerPositionZ() });
        route_ = pAst_->GetRoute();
        route_.pop_back();

    }

    if (!route_.empty())
    {
        {
            if (route_.back().first > intPosX)
            {
                GoRight();
            }
            else if (route_.back().first < intPosX)
            {
                GoLeft();
            }
        }
        {
            if (route_.back().second > intPosZ)
            {
                GoAbove();
            }
            else if (route_.back().second < intPosZ)
            {
                GoUnder();
            }
        }
        route_.pop_back();
    }
}

void Enemy::InitChild()
{
    CsvReader csv;
    csv.Load("Assets\\Map.csv");

    pAst_ = new AStar2D(csv.GetWidth());

    std::vector<std::vector<char>> data;
    data.clear();

    std::vector<char> line;
    line.clear();

    for (int i = 0; i < csv.GetWidth(); i++)
    {
        for (int j = 0; j < csv.GetHeight(); j++)
        {
            line.push_back(csv.GetValue(i, j));
        }
        data.push_back(line);
        line.clear();
    }

    pAst_->Initialize();
    pAst_->SetData(data);
}

Enemy::Enemy(GameObject* parent)
    :Character(parent, "Enemy"), pAst_(nullptr), Count_(0), Discover_(false), PrevIntX_(0), PrevIntZ_(0)
{
    route_.clear();
}

Enemy::~Enemy()
{
    SAFE_DELETE(pAst_);
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
        if (!Discover_ && route_.empty())
        {
            pAst_->Reset();
            pAst_->SetStart({ intPosX, intPosZ });
            pAst_->SetGoal({ PlayerState::GetPlayerPositionX(), PlayerState::GetPlayerPositionZ() });
            pAst_->Adjacent(Move{ intPosX, intPosZ });
            pAst_->Route({ PlayerState::GetPlayerPositionX(), PlayerState::GetPlayerPositionZ() });
            route_ = pAst_->GetRoute();
        }
        Discover_ = true;
    }
    else
    {
        Discover_ = false;
    }

}