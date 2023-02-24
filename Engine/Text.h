#pragma once
#include <d2d1.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include <dwrite.h>
#include <string>
#include <cstdio>
#include <vector>
#include <stdio.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

using namespace DirectX;

//フォントリスト
enum class Font
{
    Meiryo,
    Arial,
    MeiryoUI
};

//フォント名
namespace
{
    const WCHAR* FontList[]
    {
        L"メイリオ",
        L"Arial",
        L"Meiryo UI"
    };
}

//フォント設定
struct FontData
{
    Font font;                              //フォント名
    IDWriteFontCollection* fontCollection;  //フォントコレクション
    DWRITE_FONT_WEIGHT fontWeight;          //フォントの太さ
    DWRITE_FONT_STYLE fontStyle;            //フォントスタイル
    DWRITE_FONT_STRETCH fontStretch;        //フォントの幅
    FLOAT fontSize;                         //フォントサイズ
    WCHAR const* localeName;                //ロケール名
    DWRITE_TEXT_ALIGNMENT textAlignment;    //テキストの配置
    D2D1_COLOR_F Color;                     //テキストの色

    //デフォルト設定
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

    //フォントデータ
    FontData* Setting = new FontData();

    //string->wstring変換
    std::wstring StringToWString(std::string str);
public:
    //デフォルトコンストラクタを制限
    Text() = delete;

    //コンストラクタ
    Text(FontData* set) : Setting(set) {};

    /// <summary>コンストラクタ</summary>
    /// <param name="font">フォント名</param>
    /// <param name="fontcollection">フォントコレクション</param>
    /// <param name="fontweight">フォントの太さ</param>
    /// <param name="fontstyle">フォントスタイル</param>
    /// <param name="fontstretch">フォントの幅</param>
    /// <param name="fontsize">フォントサイズ</param>
    /// <param name="localename">ロケール名</param>
    /// <param name="textalignment">テキストの配置</param>
    /// <param name="color">フォントの色</param>
    Text(Font font,
        IDWriteFontCollection* fontcollection,
        DWRITE_FONT_WEIGHT fontweight,
        DWRITE_FONT_STYLE fontstyle,
        DWRITE_FONT_STRETCH fontstretch,
        FLOAT fontsize,
        WCHAR const* localename,
        DWRITE_TEXT_ALIGNMENT textalignment,
        D2D1_COLOR_F color);

    //フォント設定
    void SetFont(FontData* set);

    /// <summary>フォント設定</summary>
    /// <param name="font">フォント名</param>
    /// <param name="fontcollection">フォントコレクション</param>
    /// <param name="fontweight">フォントの太さ</param>
    /// <param name="fontstyle">フォントスタイル</param>
    /// <param name="fontstretch">フォントの幅</param>
    /// <param name="fontsize">フォントサイズ</param>
    /// <param name="localename">ロケール名</param>
    /// <param name="textalignment">テキストの配置</param>
    /// <param name="color">フォントの色</param>
    void SetFont(Font font,
        IDWriteFontCollection* fontcollection,
        DWRITE_FONT_WEIGHT fontweight,
        DWRITE_FONT_STYLE fontstyle,
        DWRITE_FONT_STRETCH fontstretch,
        FLOAT fontsize,
        WCHAR const* localename,
        DWRITE_TEXT_ALIGNMENT textalignment,
        D2D1_COLOR_F color);

    /// <summary>描画</summary>
    /// <param name="str">表示したい文字列</param>
    /// <param name="pos">描画位置</param>
    /// <param name="options">テキストの整形</param>
    template <typename ... Args>
    void Draw(XMFLOAT3 pos, const std::string& fmt, Args ... args)
    {
        size_t len = snprintf(nullptr, 0, fmt.c_str(), args ...);
        std::vector<char> buf(len + 1);
        snprintf(&buf[0], len + 1, fmt.c_str(), args ...);

        //文字列の変換
        std::wstring wstr = StringToWString(std::string(&buf[0], &buf[0] + len));

        //ターゲットサイズの取得
        D2D1_SIZE_F TargetSize = pRT->GetSize();

        //テキストレイアウトを作成
        pDWriteFactory->CreateTextLayout(wstr.c_str(), (UINT32)wstr.size(), pTextFormat, TargetSize.width, TargetSize.height, &pTextLayout);
        assert(pTextLayout != nullptr);

        //描画位置の確定
        D2D1_POINT_2F pounts;
        pounts.x = pos.x;
        pounts.y = pos.y;

        //描画開始
        pRT->BeginDraw();

        //描画処理
        pRT->DrawTextLayout(pounts, pTextLayout, pSolidBrush, D2D1_DRAW_TEXT_OPTIONS_NONE);

        //描画終了
        pRT->EndDraw();
    }

    void Initialize();

    void Release();
};