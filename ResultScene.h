#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"

//�����V�[�����Ǘ�����N���X
class ResultScene : public GameObject
{
	Text* pText;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	ResultScene(GameObject* parent);

	~ResultScene();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};