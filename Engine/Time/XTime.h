#pragma once

class Transform;

/// <summary>
/// DirectX�����K�v������ʕ\�����\��Time
/// </summary>
namespace XTime
{
	//������(Main�ŏ�����)
	void Initialize(int FPS);

	//�X�V(Main�ŌĂяo��)
	void Update();

	void Reset();

	void Lock();

	void UnLock();

	//�b�̂ݕ\���ɂ��邩�ǂ���
	//true = �b�̂�
	//false = �l�ɉ����Ď�/���̕\��
	void SetDisplayMode(bool Mode);

	//������ : �\������Transform ������ : �����_�ȉ�������\�����邩
	void Draw(Transform tr, int digit);

	//�Ăяo�����_�̎��Ԃ��擾
	int GetTimei();
	float GetTimef();
	double GetTimew();
};