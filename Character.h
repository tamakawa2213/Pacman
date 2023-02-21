#pragma once
#include "Engine/GameObject.h"

class Stage;

//���������Ǘ�����N���X
class Character : public GameObject
{
    XMVECTOR front_;//�������̃x�N�g��
    float checkZ_;

protected:
    int hModel_;    //���f���ԍ�
    virtual void Input() = 0;
    void GoAbove();
    void GoUnder();
    void GoLeft();
    void GoRight();

    virtual void InitChild(){}

    Stage* pStage;
    float move_;    //�ړ����x
    float movingDist_;
    int intPosX;
    int intPosZ;

public:
    //�R���X�g���N�^
    Character(GameObject* parent);
    Character(GameObject* parent, std::string name);

    //�f�X�g���N�^
    ~Character();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};