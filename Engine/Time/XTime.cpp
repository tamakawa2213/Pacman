#include "XTime.h"
#include "../Math.h"
#include "../Transform.h"
#include "../Image.h"
#include <string>
#include <vector>

//�萔�錾
namespace
{
	//60�i�@
	const char HEX = 60;

	//�\������
	const char Dig = 2;

	//�����Ԃ̑傫��
	const float Interval = 0.1f;

	//�����̑傫��
	const float Dec = 0.8f;
}

//�ϐ�
namespace
{
	int hPict_[10];
	char Hours_;
	char Minuts_;
	double Seconds_;
	bool OnlySec_;	//�b�݂̂̕\�L�ɂ��邩
	bool Lock_ = true;		//���݂̏�ԂŌŒ肷�邩
	std::vector<int> CountFps_;	//���݂̃t���[�����[�g���i�[���Ă�������
	int FPS_;		//���������ɍő�t���[�����[�g���i�[���Ă���
	int LookAt_;	//�z��̂ǂ������邩
	Transform DrawTransform_;	//�\���p��Transform
}

//�O������Ăяo���Ȃ��֐�
namespace XTime
{
	void DrawH();			//���Ԃ̕\��
	void DrawM(int dig);	//���̕\��
	void DrawS(int dig);	//�b�̕\��
	void DrawF(int dig);	//�����_�ȉ��̕\��
}

namespace XTime
{
	void Initialize(int FPS)
	{
		std::string texS = "Assets\\Numbers\\Num";
		std::string texF = ".png";
		//�摜�f�[�^�̃��[�h
		for (int i = 0; i < 10; i++)
		{
			std::string data = texS + std::to_string(i) + texF;
			hPict_[i] = Image::Load(data);
			assert(hPict_[i] > 0);
		}
		Hours_ = 0;
		Minuts_ = 0;
		Seconds_ = 0;
		OnlySec_ = false;
		FPS_ = FPS;
		LookAt_ = 0;

		CountFps_.clear();		//�O�̂��߂̏�����
		CountFps_.reserve(FPS);	//�v�f�����m�ۂ��Ă���

		while (CountFps_.size() != CountFps_.capacity())
		{
			CountFps_.push_back(FPS);
		}
	}

	void Update()
	{
		for (int i = 0; i < CountFps_.size(); i++)
		{
			//�ő�t���[�����[�g�𒴂��邱�Ƃ͂Ȃ��̂�
			if (CountFps_.at(i) < FPS_)
				CountFps_.at(i)++;
		}

		LookAt_++;
		if (LookAt_ >= FPS_)
			LookAt_ -= FPS_;

		//Lock����Ă�����X�V���Ȃ�
		if (!Lock_)
		{
			float fps = CountFps_.at(LookAt_) * 0.98f;
			Seconds_ += 1.0 / fps;
		}

		CountFps_.at(LookAt_) = 0;
	}

	void Reset()
	{
		Hours_ = 0;
		Minuts_ = 0;
		Seconds_ = 0;
	}

	void Lock()
	{
		Lock_ = true;
	}

	void UnLock()
	{
		Lock_ = false;
	}

	void SetDisplayMode(bool Mode)
	{
		OnlySec_ = Mode;
	}

	void Draw(Transform tr, int digit)
	{
		DrawTransform_ = tr;

		if (OnlySec_)	//�b�̂ݕ\���̏ꍇ
		{
			int Digit = (int)log10(Seconds_);

			//���������̕\��
			for (int i = 0; i <= Digit; i++)
			{
				DrawS(Digit - i);
			}
		}
		else
		{
			//��/���̍X�V
			Minuts_ = (char)(Seconds_ / HEX);
			Hours_ = (char)(Minuts_ / HEX);
			Minuts_ %= HEX;

			if (Hours_ > 0)	//Hours���܂߂��\��
			{
				DrawH();

				DrawTransform_.position_.x += Interval / 2;
				for (int i = 1; i <= Dig; i++)
				{
					DrawM(Dig - i);
				}

				DrawTransform_.position_.x += Interval / 2;
				for (int i = 1; i <= Dig; i++)
				{
					DrawS(Dig - i);
				}
			}
			else if (Minuts_ > 0)	//Minuts���܂߂��\��
			{
				int Digit = (int)log10(Minuts_);
				for (int i = 0; i <= Digit; i++)
				{
					DrawM(Digit - i);
				}

				DrawTransform_.position_.x += Interval / 2;
				for (int i = 1; i <= Dig; i++)
				{
					DrawS(Dig - i);
				}
			}
			else
			{
				int Digit = (int)log10(Seconds_);

				//���������̕\��
				for (int i = 0; i <= Digit; i++)
				{
					DrawS(Digit - i);
				}
			}
		}

		//���������̕\��
		DrawTransform_.scale_ = { Dec, Dec, Dec };
		DrawTransform_.position_.y -= 0.02f;		//�k�����������ɉ�����
		for (int i = 1; i <= digit; i++)
		{
			DrawF(i);
		}
	}

	int GetTimei()
	{
		return (int)Seconds_;
	}
	float GetTimef()
	{
		return (float)Seconds_;
	}
	double GetTimew()
	{
		return Seconds_;
	}


	//////////////////////////////�O������Ăяo���Ȃ��֐��̒�`/////////////////////////////////

	void DrawH()
	{
		int Pic = Math::GetDigits(Hours_, 0, 0);
		DrawTransform_.position_.x += Interval;
		Image::SetTransform(hPict_[Pic], DrawTransform_);
		Image::Draw(hPict_[Pic]);
	}

	void DrawM(int dig)
	{
		int Pic = Math::GetDigits(Minuts_, dig, dig);
		DrawTransform_.position_.x += Interval;
		Image::SetTransform(hPict_[Pic], DrawTransform_);
		Image::Draw(hPict_[Pic]);
	}

	void DrawS(int dig)
	{
		int Pic;
		if (OnlySec_)
		{
			Pic = Math::GetDigits((int)Seconds_, dig, dig);
		}
		else
		{
			Pic = Math::GetDigits((int)Seconds_ % HEX, dig, dig);
		}
		DrawTransform_.position_.x += Interval;
		Image::SetTransform(hPict_[Pic], DrawTransform_);
		Image::Draw(hPict_[Pic]);
	}

	void DrawF(int dig)
	{
		int Pic = Math::GetFraction((float)Seconds_, dig);
		DrawTransform_.position_.x += Interval;
		Image::SetTransform(hPict_[Pic], DrawTransform_);
		Image::Draw(hPict_[Pic]);
	}
}