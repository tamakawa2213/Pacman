#pragma once
#include "Engine/GameObject.h"

class Stage;

//���������Ǘ�����N���X
class Player : public GameObject
{
    int hModel_;    //���f���ԍ�
    float move_;    //�ړ����x
    XMVECTOR front_;//�������̃x�N�g��
    Stage* pStage;
    float checkZ_;

public:
    //�R���X�g���N�^
    Player(GameObject* parent);

    //�f�X�g���N�^
    ~Player();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};