#include "Image.h"
#include "CallDef.h"

namespace Image
{
    std::vector<PictureSet*> FileSet;      //Fbx�̍\���̂̓��I�z��

    int Load(std::string filename)
    {
        wchar_t file[CHAR_MAX];
        size_t ret;
        mbstowcs_s(&ret, file, filename.c_str(), filename.length());
        return Load(file);
    }

    int Image::Load(LPCWSTR filename)
    {
        HRESULT hr;
        PictureSet* File = new PictureSet;
        File->FileName = filename;
        for (auto itr = FileSet.begin(); itr != FileSet.end(); itr++)
        {
            //�������O�̃t�@�C�������łɃ��[�h���Ă����ꍇ
            if (File->FileName == (*itr)->FileName)
            {
                File->pSprite = (*itr)->pSprite;
                File->FindFbx = true;
                break;
            }
        }
        //������Ȃ������ꍇ�A�V�������[�h����
        if (!File->FindFbx)
        {
            File->pSprite = new Sprite;
            hr = File->pSprite->Initialize(filename);
            if (FAILED(hr)) //���[�h�Ɏ��s�����ꍇ
            {
                SAFE_DELETE(File->pSprite);
                SAFE_DELETE(File);
            }
        }

        FileSet.push_back(File);
        return (int)FileSet.size() - 1;
    }

    void Image::SetTransform(int hPicture, Transform transform)
    {
        FileSet[hPicture]->transform = transform;
    }

    void Image::Draw(int hModel)
    {
        FileSet[hModel]->pSprite->Draw(FileSet[hModel]->transform);
    }

    void Release()
    {
        for (int i = 0; i < FileSet.size(); i++)
        {
            if (!FileSet[i]->FindFbx)
            {
                SAFE_DELETE(FileSet[i]->pSprite);
            }
            SAFE_DELETE(FileSet[i]);
        }
        FileSet.clear();
    }
}