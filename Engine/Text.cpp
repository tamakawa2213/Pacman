#include "Text.h"
#include "CallDef.h"
#include "Direct3D.h"

std::wstring Text::StringToWString(std::string str)
{
	int iBufferSize = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, (wchar_t*)NULL, 0);

	wchar_t* cpUCS2 = new wchar_t[iBufferSize];

	MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, cpUCS2, iBufferSize);

	std::wstring Ret(cpUCS2, cpUCS2 + iBufferSize - 1);

	SAFE_DELETE_ARRAY(cpUCS2);

	return Ret;
}

Text::Text(Font font, IDWriteFontCollection* fontcollection, DWRITE_FONT_WEIGHT fontweight, DWRITE_FONT_STYLE fontstyle, DWRITE_FONT_STRETCH fontstretch, FLOAT fontsize, WCHAR const* localename, DWRITE_TEXT_ALIGNMENT textalignment, D2D1_COLOR_F color)
{
	Setting->font = font;
	Setting->fontCollection = fontcollection;
	Setting->fontWeight = fontweight;
	Setting->fontStyle = fontstyle;
	Setting->fontStretch = fontstretch;
	Setting->fontSize = fontsize;
	Setting->localeName = localename;
	Setting->textAlignment = textalignment;
	Setting->Color = color;
}

void Text::SetFont(FontData* set)
{
	pDWriteFactory->CreateTextFormat(FontList[(int)set->font], set->fontCollection, set->fontWeight, set->fontStyle, set->fontStretch, set->fontSize, set->localeName, &pTextFormat);
	pTextFormat->SetTextAlignment(set->textAlignment);
	pRT->CreateSolidColorBrush(set->Color, &pSolidBrush);
}

void Text::SetFont(Font font, IDWriteFontCollection* fontcollection, DWRITE_FONT_WEIGHT fontweight, DWRITE_FONT_STYLE fontstyle, DWRITE_FONT_STRETCH fontstretch, FLOAT fontsize, WCHAR const* localename, DWRITE_TEXT_ALIGNMENT textalignment, D2D1_COLOR_F color)
{
	pDWriteFactory->CreateTextFormat(FontList[(int)font], fontcollection, fontweight, fontstyle, fontstretch, fontsize, localename, &pTextFormat);
	pTextFormat->SetTextAlignment(textalignment);
	pRT->CreateSolidColorBrush(color, &pSolidBrush);
}

//template <typename ... Args>
//void Text::Draw(XMFLOAT3 pos, const std::string& fmt, Args ... args)
//{
//	size_t len = std::snprintf(nullptr, 0, fmt.c_str(), args ...);
//	std::vector<char> buf(len + 1);
//	std::snprintf(&buf[0], len + 1, fmt.c_str(), args ...);
//	
//	//������̕ϊ�
//	std::wstring wstr = StringToWString(std::string(&buf[0], &buf[0] + len));
//
//	//�^�[�Q�b�g�T�C�Y�̎擾
//	D2D1_SIZE_F TargetSize = pRT->GetSize();
//
//	//�e�L�X�g���C�A�E�g���쐬
//	pDWriteFactory->CreateTextLayout(wstr.c_str(), (UINT32)wstr.size(), pTextFormat, TargetSize.width, TargetSize.height, &pTextLayout);
//	assert(pTextLayout != nullptr);
//
//	//�`��ʒu�̊m��
//	D2D1_POINT_2F pounts;
//	pounts.x = pos.x;
//	pounts.y = pos.y;
//
//	//�`��J�n
//	pRT->BeginDraw();
//
//	//�`�揈��
//	pRT->DrawTextLayout(pounts, pTextLayout, pSolidBrush, D2D1_DRAW_TEXT_OPTIONS_NONE);
//
//	//�`��I��
//	pRT->EndDraw();
//}

void Text::Initialize()
{
	//Direct2D, DirectWrite�̏�����
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);

	Direct3D::pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));

	//�����_�[�^�[�Q�b�g�̍쐬
	D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED), (FLOAT)Direct3D::scrWidth, (FLOAT)Direct3D::scrHeight);

	//�T�[�t�F�X�ɕ`�悷�郌���_�[�^�[�Q�b�g���쐬
	pD2DFactory->CreateDxgiSurfaceRenderTarget(pBackBuffer, &props, &pRT);

	//�A���`�G�C���A�V���O���[�h
	pRT->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_CLEARTYPE);

	//IDWriteFactory�̍쐬
	DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&pDWriteFactory));

	pDWriteFactory->CreateTextFormat(FontList[(int)Setting->font],
		Setting->fontCollection,
		Setting->fontWeight,
		Setting->fontStyle,
		Setting->fontStretch,
		Setting->fontSize,
		Setting->localeName,
		&pTextFormat);

	pTextFormat->SetTextAlignment(Setting->textAlignment);

	pRT->CreateSolidColorBrush(Setting->Color, &pSolidBrush);
}

void Text::Release()
{
	SAFE_RELEASE(pBackBuffer);
	SAFE_RELEASE(pSolidBrush);
	SAFE_RELEASE(pRT);
	SAFE_RELEASE(pTextFormat);
	SAFE_RELEASE(pDWriteFactory);
	SAFE_RELEASE(pD2DFactory);
	SAFE_RELEASE(pTextLayout);
}
