#include "Enemy.h"
#include "PlayerState.h"

void Enemy::Input()
{
    //対象と自身の位置関係を計算
    XMFLOAT3 p = PlayerState::GetPlayerPosition();
    XMVECTOR pPos = XMLoadFloat3(&p);
    XMVECTOR mPos = XMLoadFloat3(&transform_.position_);
    XMVECTOR rPos = pPos - mPos;

    if (fabsf(XMVectorGetX(rPos)) > fabsf(XMVectorGetZ(rPos)))
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

Enemy::Enemy(GameObject* parent)
    :Character(parent, "Enemy")
{
}

Enemy::~Enemy()
{
}
