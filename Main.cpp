//�C���N���[�h
#include <Windows.h>
#include <stdlib.h>
#include "Engine/CallDef.h"
#include "Engine/Camera.h"
#include "Engine/Direct3D.h"
#include "Engine/GameTime.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/RootJob.h"
#include "Engine/Time/Time.h"
#include "Graphics/imgui_impl_dx11.h"
#include "Graphics/imgui_impl_win32.h"

#pragma comment(lib, "winmm.lib")

//�萔�錾
namespace
{
	LPCWSTR WIN_CLASS_NAME = L"SampleGame";	//�E�B���h�E�N���X��
	const unsigned int WINDOW_WIDTH = 800;	//�E�B���h�E�̕�
	const unsigned int WINDOW_HEIGHT = 600;	//�E�B���h�E�̍���
	static const char MAX_FPS = 60;			//�ő�t���[�����[�g
}

RootJob* pRootJob;

//�v���g�^�C�v�錾
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//�G���g���[�|�C���g(�v���O�����̃X�^�[�g�n�_)
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	//�E�B���h�E�N���X(�݌v�})���쐬
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);				//���̍\���̂̃T�C�Y
	wc.hInstance = hInstance;					//�C���X�^���X�n���h��
	wc.lpszClassName = WIN_CLASS_NAME;			//�E�B���h�E�N���X��
	wc.lpfnWndProc = WndProc;					//�E�B���h�E�v���V�[�W��
	wc.style = CS_VREDRAW | CS_HREDRAW;			//�X�^�C���i�f�t�H���g�j
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);	//�A�C�R��
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);	//�������A�C�R��
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);	//�}�E�X�J�[�\��
	wc.lpszMenuName = NULL;//���j���[
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //�w�i�i���j

	RegisterClassEx(&wc);  //�N���X��o�^

	//�E�B���h�E�T�C�Y�̌v�Z
	RECT winRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, TRUE);
	int winW = winRect.right - winRect.left;	//�E�B���h�E��
	int winH = winRect.bottom - winRect.top;	//�E�B���h�E����

	//�E�B���h�E���쐬
	HWND hWnd = CreateWindow(
		WIN_CLASS_NAME,			//�E�B���h�E�N���X��
		L"�l����3",			//�^�C�g���o�[�ɕ\��������e
		WS_OVERLAPPEDWINDOW,	//�X�^�C���i���ʂ̃E�B���h�E�j
		CW_USEDEFAULT,			//�\���ʒu���i���܂����j
		CW_USEDEFAULT,			//�\���ʒu��i���܂����j
		winW,					//�E�B���h�E��
		winH,					//�E�B���h�E����
		NULL,					//�e�E�C���h�E�i�Ȃ��j
		NULL,					//���j���[�i�Ȃ��j
		hInstance,				//�C���X�^���X
		NULL					//�p�����[�^�i�Ȃ��j
	);

	//�E�B���h�E��\��
	ShowWindow(hWnd, nCmdShow);

	HRESULT hr;

	//COM(Component Object Model)�̏�����
	hr = CoInitialize(nullptr);
	if (FAILED(hr)) {
		CoUninitialize();
		PostQuitMessage(0);
	}

	//Direct3D������
	hr = Direct3D::Initialize(WINDOW_WIDTH, WINDOW_HEIGHT, hWnd);
	if (FAILED(hr)) {
		Direct3D::Release();
		PostQuitMessage(0);
	}

	{//GUI������
#if _DEBUG
		//IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		ImFontConfig config;
		config.MergeMode = true;
		io.Fonts->AddFontDefault();
		//io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\meiryo.ttc", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
		ImGui::StyleColorsDark();
		ImGui_ImplWin32_Init(hWnd);
		ImGui_ImplDX11_Init(Direct3D::pDevice, Direct3D::pContext);
		ImGui::SetNextWindowSize(ImVec2(320, 100));
#endif
	}

	//�J�����̏�����
	Camera::Initialize();

	//RootJob������
	pRootJob = nullptr;
	pRootJob = new RootJob(nullptr);
	pRootJob->Initialize();

	//DirectInput�̏�����
	Input::Initialize(hWnd);

	//Time������
	Time::Initialize(MAX_FPS);

	//���b�Z�[�W���[�v(�����N����̂�҂�)
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		//���b�Z�[�W����
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//���b�Z�[�W�Ȃ�
		else
		{
			timeBeginPeriod(1);	//timeEndPeriod�ƃZ�b�g�Ŏg�p����֐�
			DWORD nowTime = timeGetTime();
			static DWORD lastUpdateTime = nowTime;

			if ((nowTime - lastUpdateTime) * MAX_FPS <= 1000.0f)
			{
				continue;
			}

#if _DEBUG
			ImGui_ImplDX11_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();

			//{
			//	static float f = 0.0f;
			//	static int counter = 0;

			//	ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

			//	ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
			//	ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state

			//	ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f

			//	if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			//		counter++;
			//	ImGui::SameLine();
			//	ImGui::Text("counter = %d", counter);

			//	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			//	ImGui::End();
			//}
			//if (show_another_window)
			//{
			//	ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
			//	ImGui::Text("Hello from another window!");
			//	if (ImGui::Button("Close Me"))
			//		show_another_window = false;
			//	ImGui::End();
			//}
#endif

			//FPS�̍X�V
			Time::Update();
			lastUpdateTime = nowTime;

			GameTime::Update();


			//�Q�[���̏���
			if (GameTime::IsStop())
			{
				Input::Update();
			}
			else
			{
				while (GameTime::RemainingTimes() >= 0)
				{
					//���͏��̍X�V
					Input::Update();

					pRootJob->Update();
					pRootJob->UpdateSub();
					GameTime::UpDated();
				}
			}
			Camera::Update();
			Direct3D::BeginDraw();


#if _DEBUG
			ImGui::Render();
			ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
#endif

			//�`�揈��
			pRootJob->DrawSub();

			Direct3D::EndDraw();

			timeEndPeriod(1);
		}
	}

#if _DEBUG
	ImGui_ImplDX11_Shutdown();
	ImGui::DestroyContext();
#endif

	pRootJob->ReleaseSub();
	SAFE_DELETE(pRootJob);
	Input::Release();
	Model::Release();
	Direct3D::Release();
	CoUninitialize();	//COM��Release
	return 0;
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//�E�B���h�E�v���V�[�W��(�������������ɌĂяo�����֐�)
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);  //�v���O�����I��
		return 0;
	case WM_MOUSEMOVE:
		Input::SetMousePosition(LOWORD(lParam), HIWORD(lParam));
		return 0;
	case WM_MOUSEWHEEL:
		Input::SetMouseWheel(GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA);
		return 0;
	}

#if _DEBUG
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;
#endif

	return DefWindowProc(hWnd, msg, wParam, lParam);
}