#include "Camera.h"
#include "CallDef.h"

//�ϐ�
namespace Camera {
	XMVECTOR position_;	//�J�����̈ʒu�i���_�j
	XMVECTOR target_;	//����ʒu�i�œ_�j
	XMMATRIX viewMatrix_;	//�r���[�s��
	XMMATRIX projMatrix_;	//�v���W�F�N�V�����s��
}

//������
void Camera::Initialize()
{
	position_ = XMVectorSet(6.5f, 20, 5, 0);	//�J�����̈ʒu
	target_ = XMVectorSet(6.5f, 0, 7, 0);		//�J�����̏œ_
	projMatrix_ = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)800 / (FLOAT)600, 0.1f, 100.0f);	//�v���W�F�N�V�����s��
}

//�X�V
void Camera::Update()
{
	//�r���[�s��̍쐬(�J�����Œ�̃Q�[���Ȃ�Initialize�ɏ���)
	viewMatrix_ = XMMatrixLookAtLH(position_, target_, XMVectorSet(0, 1, 0, 0));
}

//�ʒu��ݒ�
void Camera::SetPosition(XMVECTOR position)
{
	position_ = position;
}

//�œ_��ݒ�
void Camera::SetTarget(XMVECTOR target)
{
	target_ = target;
}

//�r���[�s����擾
XMMATRIX Camera::GetViewMatrix()
{
	return viewMatrix_;
}

//�v���W�F�N�V�����s����擾
XMMATRIX Camera::GetProjectionMatrix()
{
	return projMatrix_;
}

XMVECTOR Camera::GetPosition()
{
	return position_;
}

XMVECTOR Camera::GetTarget()
{
	return target_;
}

XMVECTOR Camera::GetSight()
{
	return target_ - position_;
}

XMVECTOR Camera::GetCameraVecPosition()
{
	return position_;
}
XMVECTOR Camera::GetCameraVecTarget()
{
	return target_;
}