#pragma once

//DELETE処理を呼び出すマクロを作成
#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;}
//配列をDELETEするマクロ
#define SAFE_DELETE_ARRAY(p) if(p != nullptr){ delete[] p; p = nullptr;}
//RELEASEも同様にマクロ作成
#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;}

//HRESULTが失敗したときにReleaseなしで呼び出すマクロ
#define HR_FAILED(hr, text) if(FAILED(hr)){MessageBox(NULL, text, L"Error", MB_OKCANCEL);return hr; }
//HRESULTが失敗したときにReleaseありで呼び出すマクロ
#define HR_FAILED_RELEASE(hr, text, p) if(FAILED(hr)){MessageBox(NULL, text, L"Error", MB_OKCANCEL); SAFE_RELEASE(p);return hr; }

//シーン切り替えを行うマクロ
#define SCENE_CHANGE(SCENE_ID) SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager"); pSceneManager->ChangeScene(SCENE_ID);

//一定の範囲に収めるもの
#define CLAMP(i, Min, Max) i = min(max( i, Min), Max);

//モデルをロードするもの
//引数 : 格納したいモデル番号 ファイル名
#define MLoad(hModel, filename) hModel = Model::Load(filename); assert(hModel >= 0);

//XMFLOAT3の要素をまとめて反転させる
//引数 : 逆転後のXMFLOAT3 元となるXMFLOAT3
#define RE_XMFLOAT3(Rev, Orig) Rev = {-Orig.x, -Orig.y, -Orig.z};