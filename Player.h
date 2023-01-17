#pragma once
#include "Engine/GameObject.h"

class Stage;

//◆◆◆を管理するクラス
class Player : public GameObject
{
    int hModel_;    //モデル番号
    float move_;    //移動速度
    XMVECTOR front_;//奥向きのベクトル
    Stage* pStage;
    float checkZ_;

public:
    //コンストラクタ
    Player(GameObject* parent);

    //デストラクタ
    ~Player();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};