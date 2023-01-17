#include "XTime.h"
#include "../Math.h"
#include "../Transform.h"
#include "../Image.h"
#include <string>
#include <vector>

//定数宣言
namespace
{
	//60進法
	const char HEX = 60;

	//表示桁数
	const char Dig = 2;

	//文字間の大きさ
	const float Interval = 0.1f;

	//小数の大きさ
	const float Dec = 0.8f;
}

//変数
namespace
{
	int hPict_[10];
	char Hours_;
	char Minuts_;
	double Seconds_;
	bool OnlySec_;	//秒のみの表記にするか
	bool Lock_ = true;		//現在の状態で固定するか
	std::vector<int> CountFps_;	//現在のフレームレートを格納しておくもの
	int FPS_;		//初期化時に最大フレームレートを格納しておく
	int LookAt_;	//配列のどこを見るか
	Transform DrawTransform_;	//表示用のTransform
}

//外部から呼び出さない関数
namespace XTime
{
	void DrawH();			//時間の表示
	void DrawM(int dig);	//分の表示
	void DrawS(int dig);	//秒の表示
	void DrawF(int dig);	//小数点以下の表示
}

namespace XTime
{
	void Initialize(int FPS)
	{
		std::string texS = "Assets\\Numbers\\Num";
		std::string texF = ".png";
		//画像データのロード
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

		CountFps_.clear();		//念のための初期化
		CountFps_.reserve(FPS);	//要素数を確保しておく

		while (CountFps_.size() != CountFps_.capacity())
		{
			CountFps_.push_back(FPS);
		}
	}

	void Update()
	{
		for (int i = 0; i < CountFps_.size(); i++)
		{
			//最大フレームレートを超えることはないので
			if (CountFps_.at(i) < FPS_)
				CountFps_.at(i)++;
		}

		LookAt_++;
		if (LookAt_ >= FPS_)
			LookAt_ -= FPS_;

		//Lockされていたら更新しない
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

		if (OnlySec_)	//秒のみ表示の場合
		{
			int Digit = (int)log10(Seconds_);

			//整数部分の表示
			for (int i = 0; i <= Digit; i++)
			{
				DrawS(Digit - i);
			}
		}
		else
		{
			//時/分の更新
			Minuts_ = (char)(Seconds_ / HEX);
			Hours_ = (char)(Minuts_ / HEX);
			Minuts_ %= HEX;

			if (Hours_ > 0)	//Hoursを含めた表示
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
			else if (Minuts_ > 0)	//Minutsを含めた表示
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

				//整数部分の表示
				for (int i = 0; i <= Digit; i++)
				{
					DrawS(Digit - i);
				}
			}
		}

		//小数部分の表示
		DrawTransform_.scale_ = { Dec, Dec, Dec };
		DrawTransform_.position_.y -= 0.02f;		//縮小した分下に下げる
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


	//////////////////////////////外部から呼び出さない関数の定義/////////////////////////////////

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