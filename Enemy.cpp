#include "Enemy.h"
#include "AStar2D.h"
#include "Engine/CsvReader.h"
//#include "Engine/Math.h"
#include "PlayerState.h"

void Enemy::Input()
{
    if (++Count_ > (rand() % 60))
    {
        //if (rand() % 100 > 50)
        //{
        //    pAst_->Reset();
        //    pAst_->SetStart({ intPosX / 10, intPosZ / 10 });
        //    pAst_->SetGoal({ (int)PlayerState::GetPlayerPosition().x, (int)PlayerState::GetPlayerPosition().z });
        //    pAst_->Adjacent(Move{ intPosX / 10, intPosZ / 10 });
        //    std::pair<int, int> route;
        //    pAst_->Route({ intPosX / 10, intPosZ / 10 });
        //    route = pAst_->GetRoute().front();

        //    //ëŒè€Ç∆é©êgÇÃà íuä÷åWÇåvéZ
        //    XMFLOAT3 p = PlayerState::GetPlayerPosition();
        //    XMVECTOR pPos = XMLoadFloat3(&p);
        //    XMVECTOR mPos = XMLoadFloat3(&transform_.position_);
        //    XMVECTOR rPos = pPos - mPos;

        //    if ((fabsf(XMVectorGetX(rPos)) < fabsf(XMVectorGetZ(rPos))) ^ (rand() % 100 > 50))
        //    {
        //        if (route.first > intPosX / 10)
        //        {
        //            GoRight();
        //        }
        //        else if (route.first < intPosX / 10)
        //        {
        //            GoLeft();
        //        }
        //    }
        //    else if((fabsf(XMVectorGetX(rPos)) > fabsf(XMVectorGetZ(rPos))) ^ (rand() % 100 < 50))
        //    {
        //        if (route.second > intPosZ / 10)
        //        {
        //            GoAbove();
        //        }
        //        else if (route.second < intPosZ / 10)
        //        {
        //            GoUnder();
        //        }
        //    }
        //}
        //else
        {
            //ëŒè€Ç∆é©êgÇÃà íuä÷åWÇåvéZ
            XMFLOAT3 p = PlayerState::GetPlayerPosition();
            XMVECTOR pPos = XMLoadFloat3(&p);
            XMVECTOR mPos = XMLoadFloat3(&transform_.position_);
            XMVECTOR rPos = pPos - mPos;

            int proportion = (int)((fabsf(XMVectorGetX(rPos)) / (fabsf(XMVectorGetX(rPos)) + fabsf(XMVectorGetZ(rPos)))) * 100);

            if ((fabsf(XMVectorGetX(rPos)) < fabsf(XMVectorGetZ(rPos))) ^ (rand() % 100 < proportion))
            {
                if (XMVectorGetX(rPos) > 0)
                {
                    GoRight();
                }
                else
                {
                    GoLeft();
                }
            }
            else
            {
                if (XMVectorGetZ(rPos) > 0)
                {
                    GoAbove();
                }
                else
                {
                    GoUnder();
                }
            }

        }

        Count_ = 0;
    }
}

void Enemy::Search()
{
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
    :Character(parent, "Enemy"), pAst_(nullptr), Count_(0)
{
}

Enemy::~Enemy()
{
    SAFE_DELETE(pAst_);
}
