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

	std::list<std::pair<int, int>> route_;

	void Input() override;
	void InitChild() override;

	//�v���C���[�����E�ɓ����Ă��邩�̌v�Z
	void CalcInSight();

	//�v���C���[��{������
	void Search();
	//�v���C���[��ǐՂ���
	void Chase();
public:
	Enemy(GameObject* parent);
	~Enemy();
};