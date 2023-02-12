#pragma once
#include "Engine/GameObject.h"

class Stage;

//◆◆◆を管理するクラス
class Character : public GameObject
{
    int hModel_;    //モデル番号
    XMVECTOR front_;//奥向きのベクトル
    float checkZ_;
    //XMVECTOR vMove;

protected:
    virtual void Input() = 0;
    void GoAbove();
    void GoUnder();
    void GoLeft();
    void GoRight();

    virtual void InitChild(){}

    Stage* pStage;
    float move_;    //移動速度
    float movingDist_;
    int intPosX;
    int intPosZ;

public:
    //コンストラクタ
    Character(GameObject* parent);
    Character(GameObject* parent, std::string name);

    //デストラクタ
    ~Character();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};