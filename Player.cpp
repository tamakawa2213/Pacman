#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Stage.h"

//�R���X�g���N�^
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"), hModel_(-1), move_(0.1f), front_{ 0,0,1,0 }, checkZ_(0.3f), pStage(nullptr)
{
}

//�f�X�g���N�^
Player::~Player()
{
}

//������
void Player::Initialize()
{//���f���f�[�^�̃��[�h
    hModel_ = Model::Load("Assets\\player.fbx");
    assert(hModel_ >= 0);

    transform_.position_.x = 0.5f;
    transform_.position_.z = 1.5f;
    pStage = (Stage*)FindObject("Stage");
    assert(pStage != nullptr);
}

//�X�V
void Player::Update()
{
    //�ړ��O�̈ʒu�x�N�g��
    XMVECTOR prevPosition = XMLoadFloat3(&transform_.position_);
    XMVECTOR vMove = {};

    //����awsd�Ə㉺���E�L�[�̂ǂ���ł���
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
    ////////////////////////////////////////////////////////��]����////////////////////////////////////////////////////

    //�ړ���̈ʒu�x�N�g��
    XMVECTOR nowPosition = prevPosition + vMove;

    //�ړ��x�N�g��
    XMVECTOR move = nowPosition - prevPosition;

    //�ړ��x�N�g���̒����̑���
    XMVECTOR length = XMVector3Length(move);

    //0.1�ȏ�ړ����Ă����]����
    if (XMVectorGetY(length) >= 0.1f) {

        //�ړ��x�N�g���̐��K��
        move = XMVector3Normalize(move);

        //front_��move�̓��ς����߂�(�߂�l��vector)
        XMVECTOR vecDot = XMVector3Dot(front_, move);
        float dot = XMVectorGetX(vecDot);

        //�p�x�����߂�(���W�A��)
        float angle = acosf(dot);

        //�O�ς����߂�
        XMVECTOR cross = XMVector3Cross(front_, move);

        //�O�ς̌��ʂ�y���}�C�i�X (= ���ɐi��ł�)
        if (XMVectorGetY(cross) < 0) {
            angle *= -1;
        }

        //angle�ŉ�]������
        transform_.rotate_.y = angle * 180 / 3.14f;
    }

    //////////////////////////////////////////////////////////�ǂƂ̏Փ˔���//////////////////////////////////////////////////////

    float checkX, checkZ;

    //�E��
    checkX = transform_.position_.x + 1.3f;
    checkZ = transform_.position_.z;

    if (pStage->IsWall(checkX, checkZ)) {
        transform_.position_.x = (float)((int)(transform_.position_.x + 0.5f)) - 0.3f;
    }
    else if(pStage->IsWall(checkX - 0.6f, checkZ)) {
        //����
            transform_.position_.x = (float)((int)(transform_.position_.x + 0.5f)) + 0.3f;
    }
        //����
    checkX = transform_.position_.x + 1.0f;
    checkZ -= checkZ_;

    if (pStage->IsWall(checkX, checkZ)) {
        transform_.position_.z = (float)((int)(transform_.position_.z + 0.5f)) + 0.3f;
    }
    else if (pStage->IsWall(checkX, checkZ + 0.6f)) {
        //�㕔
        transform_.position_.z = (float)((int)(transform_.position_.z + 0.5f)) - 0.3f;
    }

}

//�`��
void Player::Draw()
{
    Model::Draw(hModel_, transform_);
}

//�J��
void Player::Release()
{
}