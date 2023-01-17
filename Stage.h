#pragma once
#include "Engine/GameObject.h"
#include "Engine/CsvReader.h"

class Stage : public GameObject
{
	int hModel_[2];    //���f���ԍ�
	int map_ [15][15];
	CsvReader csv;
public:
	//�R���X�g���N�^
	Stage(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	//��or��
	bool IsWall(float x, float z);
};

