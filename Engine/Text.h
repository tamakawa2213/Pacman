#pragma once
#include <d2d1.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include <dwrite.h>
#include <string>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

using namespace DirectX;

//�t�H���g���X�g
enum class Font
{
    Meiryo,
    Arial,
    MeiryoUI
};

//�t�H���g��
namespace
{
    const WCHAR* FontList[]
    {
        L"���C���I",
        L"Arial",
        L"Meiryo UI"
    };
}

//�t�H���g�ݒ�
struct FontData
{
    Font font;                              //�t�H���g��
    IDWriteFontCollection* fontCollection;  //�t�H���g�R���N�V����
    DWRITE_FONT_WEIGHT fontWeight;          //�t�H���g�̑���
    DWRITE_FONT_STYLE fontStyle;            //�t�H���g�X�^�C��
    DWRITE_FONT_STRETCH fontStretch;        //�t�H���g�̕�
    FLOAT fontSize;                         //�t�H���g�T�C�Y
    WCHAR const* localeName;                //���P�[����
    DWRITE_TEXT_ALIGNMENT textAlignment;    //�e�L�X�g�̔z�u
    D2D1_COLOR_F Color;                     //�e�L�X�g�̐F

    //�f�t�H���g�ݒ�
    FontData()
    {
        font = Font::Meiryo;
        fontCollection = nullptr;
        fontWeight = DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_NORMAL;
        fontStyle = DWRITE_FONT_STYLE::DWRITE_FONT_STYLE_NORMAL;
        fontStretch = DWRITE_FONT_STRETCH::DWRITE_FONT_STRETCH_NORMAL;
        fontSize = 20;
        localeName = L"ja-jp";
        textAlignment = DWRITE_TEXT_ALIGNMENT::DWRITE_TEXT_ALIGNMENT_LEADING;
        Color = D2D1::ColorF(D2D1::ColorF::White);
    }
};

class Text
{
    ID2D1Factory* pD2DFactory = nullptr;
    IDWriteFactory* pDWriteFactory = nullptr;
    IDWriteTextFormat* pTextFormat = nullptr;
    IDWriteTextLayout* pTextLayout = nullptr;
    ID2D1RenderTarget* pRT = nullptr;
    ID2D1SolidColorBrush* pSolidBrush = nullptr;
    IDXGISurface* pBackBuffer = nullptr;

    //�t�H���g�f�[�^
    FontData* Setting = nullptr;

    //string->wstring�ϊ�
    std::wstring StringToWString(std::string str);
public:
    //�f�t�H���g�R���X�g���N�^�𐧌�
    Text() = delete;

    //�R���X�g���N�^
    Text(FontData* set) : Setting(set) {};

    //�f�X�g���N�^
    ~Text();

    //�t�H���g�ݒ�
    void SetFont(FontData* set);

    /// <summary>�`��</summary>
    /// <param name="pos">�`��ʒu</param>
    /// <param name="fmt">�\��������������</param>
    template <typename ... Args>
    void Draw(XMFLOAT2 pos, const std::string& fmt, Args ... args)
    {
        size_t len = snprintf(nullptr, 0, fmt.c_str(), args ...);
        std::string buf;
        snprintf(&buf[0], len + 1, fmt.c_str(), args ...);

        //������̕ϊ�
        std::wstring wstr = StringToWString(buf);

        //�^�[�Q�b�g�T�C�Y�̎擾
        D2D1_SIZE_F TargetSize = pRT->GetSize();

        //�e�L�X�g���C�A�E�g���쐬
        pDWriteFactory->CreateTextLayout(wstr.c_str(), (UINT32)wstr.size(), pTextFormat, TargetSize.width, TargetSize.height, &pTextLayout);
        assert(pTextLayout != nullptr);

        //�`��ʒu�̊m��
        D2D1_POINT_2F pounts;
        pounts.x = pos.x;
        pounts.y = pos.y;

        //�`��J�n
        pRT->BeginDraw();

        //�`�揈��
        pRT->DrawTextLayout(pounts, pTextLayout, pSolidBrush, D2D1_DRAW_TEXT_OPTIONS_NONE);

        //�`��I��
        pRT->EndDraw();
    }

    void Initialize();

    void Release();
};