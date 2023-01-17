#pragma once
#include "Engine/GameObject.h"

class Stage;

class Enemy : public GameObject
{
	Stage* pStage;
	bool Discover_;		//������Ԃ��ǂ���

	//�v���C���[�����E�ɓ����Ă��邩�̌v�Z
	void CalcInSight();

	void ShowGraphical();

	//������Ԃ̏���
	void StateDiscovered();

	//��������Ԃ̏���
	void StateUndiscovered();

	void JudgeWall();
public:
	Enemy(GameObject* parent);

	~Enemy();

	//������
	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;
};