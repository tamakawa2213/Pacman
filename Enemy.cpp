#include "Enemy.h"
#include "AStar2D.h"
#include "Engine/CsvReader.h"
#include "Engine/Math.h"
#include "Engine/Model.h"
#include "Engine/SceneManager.h"
#include "Engine/Time/Time.h"
#include "PlayerState.h"
#include "Stage.h"

namespace
{
    const XMVECTOR sight = { 0,0,1,0 };		//視線ベクトル
}

void Enemy::Input()
{
    if (Math::GetDistance(PlayerState::GetPlayerPosition(), transform_.position_) < 0.5f)
    {
        SCENE_CHANGE(SCENE_ID_RESULT);
        Time::Lock();
    }

    if (++Count_ > 8)
    {
        Count_ = 0;

        CalcInSight();

        if (Discover_ || !route_.empty())
            Chase();
        else
            Search();
    }

}

void Enemy::Search()
{
    if (rand() % 32 <= 1)
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
    if (!Discover_ && movingDist_ <= 0)
    {
        if (rand() % 2 == 0)
            transform_.rotate_.y += 90;
        else
            transform_.rotate_.y -= 90;

        return;
    }

    if (intPosX != PrevIntX_ && intPosZ != PrevIntZ_)
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
            pAst_->Route({ intPosX, intPosZ });
            route_ = pAst_->GetRoute();

        }

        if (!route_.empty())
        {
            if(route_.front().first == intPosX && route_.front().second == intPosZ)
                route_.pop_front();
            else
            {
                if (route_.front().first != intPosX)
                {
                    int distX = route_.front().first - intPosX;
                    
                    if (distX > 0)
                        GoRight();
                    else
                        GoLeft();
                }
                else
                {
                    int distZ = route_.front().second - intPosZ;

                    if (distZ > 0)
                        GoAbove();
                    else
                        GoUnder();
                }
            }
        }

    }
}

void Enemy::InitChild()
{
    CsvReader csv;
    csv.Load("Assets\\Map.csv");

    pAst_ = new AStar2D((short)csv.GetWidth());

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
    :Enemy(parent, "Enemy", 7, 0.5f, 50)
{
}

Enemy::Enemy(GameObject* parent, std::string name, float vis, float wid, int bored)
    :Character(parent, "Enemy"), pAst_(nullptr), Count_(0), Discover_(false), PrevIntX_(0), PrevIntZ_(0),Visibility(vis), SightWidth(wid),
    ChaseCount_(50), Bored_(bored)
{
    route_.clear();
    MLoad(hModel_, "Assets\\Parrot.fbx");
    transform_.rotate_.x = 90;
    transform_.scale_ = { 0.3f, 0.3f, 0.3f };
    srand((unsigned int)time(NULL));
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

    if (Discover_ && --ChaseCount_ < 0)
    {
        Discover_ = false;
        ChaseCount_ = Bored_;
        transform_.rotate_.y += 180;
    }

}