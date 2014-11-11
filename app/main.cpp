#include <windows.h>
#include "../tinygfxlib/tinygfxlib.h"
#include "../tinygfxlib/win.h"

class SimpleApp : public WindowsApp
{
private:
	void                        Initialize();
	void                        Terminate ();

public:
	SimpleApp(HINSTANCE hInstance, int nCmdShow)
		: WindowsApp(hInstance, nCmdShow)
	{
		Initialize();
	}

	virtual ~SimpleApp()
	{
		Terminate ();
	}

	virtual void                Update();
	virtual void                Draw  ();
};

void SimpleApp::Initialize()
{
}

void SimpleApp::Terminate ()
{
}

void SimpleApp::Update    ()
{
}

void SimpleApp::Draw      ()
{
}

int WINAPI WinMain(
	HINSTANCE hInstance,      // ���݂̃C���X�^���X�̃n���h��
	HINSTANCE hPrevInstance,  // �ȑO�̃C���X�^���X�̃n���h��
	LPSTR lpCmdLine,          // �R�}���h���C��
	int nCmdShow              // �\�����
	)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	SimpleApp app(hInstance, nCmdShow);

	return app.MainLoop();
}
