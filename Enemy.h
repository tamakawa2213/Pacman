#pragma once
#include "Character.h"

class AStar2D;

//���������Ǘ�����N���X
class Enemy : public Character
{
	int Count_;
	AStar2D* pAst_;
	bool Discover_;

	int PrevIntX_;
	int PrevIntZ_;

	int ChaseCount_;
	int Bored_;			//�O���ɂ���

	std::list<std::pair<int, int>> route_;

	void Input() override;
	void InitChild() override;

	//�v���C���[�����E�ɓ����Ă��邩�̌v�Z
	void CalcInSight();

	//�v���C���[��{������
	void Search();
	//�v���C���[��ǐՂ���
	void Chase();

protected:

	float Visibility;			//����
	float SightWidth;		//���E�̍L��

public:
	Enemy(GameObject* parent);
	Enemy(GameObject* parent, std::string name, float vis, float wid, int bored);
	~Enemy();
};