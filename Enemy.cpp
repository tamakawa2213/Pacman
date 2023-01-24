#include "Enemy.h"
#include "PlayerState.h"

void Enemy::Input()
{
    //‘ÎÛ‚ÆŽ©g‚ÌˆÊ’uŠÖŒW‚ðŒvŽZ
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
