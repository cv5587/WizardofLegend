// DefaultWindow.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "DefaultWindow.h"
#include "MainGame.h"

#define MAX_LOADSTRING 100

// ���� ����:
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.
HWND	g_hWnd;

// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
ATOM                MyRegisterClass(HINSTANCE hInstance);	// â ��Ÿ���� �����ϴ� �Լ�
BOOL                InitInstance(HINSTANCE, int);			// â�� �����ϴ� ��ɾ ȣ���ϴ� �Լ�
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);	// �����쿡�� �߻��� �޼����� ó���ϴ� �Լ�
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);		// â�� ������ ����ִ� �޼��� �ڽ� �Լ�

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,				// �޸𸮿� �Ҵ�Ǵ� ��ü, ���� ���α׷��� ���� �ĺ� ��ȣ�� ����
                     _In_opt_ HINSTANCE hPrevInstance,		// ���� ����Ǿ��� �ν��Ͻ��� �ڵ��� �Ѿ��, ���� ��� �⺻�� null�� ä����(ȣȯ���� ���� ����)
                     _In_ LPWSTR    lpCmdLine,				// �����Ǵ� ���� ü��(L"")
                     _In_ int       nCmdShow)				// ������ â�� ��Ÿ��(���/ �ּ�ȭ, �ִ�ȭ ��� ���� ��)�� �ɼ� ���� ���޵�
{
	GdiplusStartupInput  gdiplusStartupInput;
	ULONG_PTR		gdiplusToken;
	if (::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL) != Ok)

	{

		MessageBox(g_hWnd, L"����", L"����", MB_OK);
		return FALSE;
	}
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    UNREFERENCED_PARAMETER(hPrevInstance);		
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: ���⿡ �ڵ带 �Է��մϴ�.

    // ���� ���ڿ��� �ʱ�ȭ�մϴ�.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DEFAULTWINDOW, szWindowClass, MAX_LOADSTRING);
   
	MyRegisterClass(hInstance);

    // ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DEFAULTWINDOW));
	
    MSG msg;
	msg.message = WM_NULL;

	CMainGame		MainGame;

	MainGame.Initialize();

	DWORD	dwTime = GetTickCount();			// 990

	while (true)
	{
		// PM_REMOVE	: �޽����� �о�Ȱ� ���ÿ� �޽��� ť���� ����
		// PM_NOREMOVE : �޽��� ť�� �޽����� �ִ��� ���θ� �ľ�, �޽����� �������� GetMessage�� �ٽ� ȣ���ؾ� �Ѵ�.

		// PeekMessage�� ������ �޼����� ť�� ���� ��� �ڵ� 0�� �����Ѵ�.
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (WM_QUIT == msg.message)
				break;

			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		else
		{	//	1000			1001
			if (dwTime + 10 < GetTickCount())
			{
				MainGame.Update();
				MainGame.Late_Update();
				MainGame.Render();

				//1003
				dwTime = GetTickCount();
			}			

			/*MainGame.Update();
			MainGame.Late_Update();
			MainGame.Render();*/
		}		
	}
	
    // �⺻ �޽��� �����Դϴ�.
   /* while (GetMessage(&msg, nullptr, 0, 0))
    {
		// TranslateAccelerator : �޴� ����� ����Ű�� ����� �۵��ϵ��� �˻��ϴ� �Լ�
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
			// TranslateMessage : Ű���� �޼����� �����Ͽ� ���α׷����� ���� ����� �� �ֵ��� ���ִ� �Լ�, 
			// GetMessage �Լ��� �о�� Ű���� �޼����� �����ϴ� ����

            TranslateMessage(&msg);

			// �ý��� �޼��� ť���� ���� �޼����� WndProc�Լ����� ����
            DispatchMessage(&msg);
        }
    }*/

    return (int) msg.wParam;
}



//
//  �Լ�: MyRegisterClass()
//
//  ����: â Ŭ������ ����մϴ�.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;			// ������ â�� ���� �� ���Ǵ� ����ü

    wcex.cbSize = sizeof(WNDCLASSEX);		 // �ڱ� �ڽ��� ����� ������ ����

    wcex.style          = CS_HREDRAW | CS_VREDRAW;	// ������ ��Ÿ���� ����, â �ʱ�ȭ ���� �ǹ�, �������� ���� �Ǵ� ������ ũ�Ⱑ ���� ��� �ٽ� �׸��ٴ� �ǹ� 

	//CS_HREDRAW : ���θ� �ٽ� �׸���.
	//CS_VREDRAW : ���θ� �ٽ� �׸���.

    wcex.lpfnWndProc    = WndProc;	// �޼����� ó���� �Լ��� �̸�
    wcex.cbClsExtra     = 0;		// �����찡 Ư���� �������� ����ϴ� ������ ����
    wcex.cbWndExtra     = 0;		// ������ ���� �����̸� ������� ���� ��� 0

    wcex.hInstance      = hInstance;	// ������ Ŭ������ ����ϴ� ���α׷��� ��ȣ ����
	
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DEFAULTWINDOW));
	// �����찡 ����� ������ ����(���� ǥ����)

    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
	// �����쿡�� ����� ���콺 Ŀ���� ����

    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	// ������ �۾� ������ ��� ���� ����
	
	wcex.lpszMenuName = NULL;
	// ������ ��ܿ� �ִ� �޴� ����

    wcex.lpszClassName  = szWindowClass;
	// ���� ������ �̸��� ���� (�������̸� ������Ʈ �̸��� ��ġ��Ŵ)

    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	// ������ â ��ܿ� �ִ� ���� ������ ����� ����

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

   RECT	rcWindow{ 0, 0, WINCX, WINCY };

   // CreateWindowW : ����� ���� �������� ���� �����츦 ����� �۾��� ����

   // rcWindow = rcWindow + �⺻ â ��Ÿ�� + �޴� ���� ũ�� ��� ����

   AdjustWindowRect(&rcWindow, WS_OVERLAPPEDWINDOW, FALSE);

   HWND hWnd = CreateWindowW(szWindowClass,  // �ռ� ������ ������ Ŭ������ ������ Ŭ���� �̸��� �״�� �־���
						   szTitle,			// ������ ��ܿ� ��Ÿ�� ���ڿ�
						   WS_OVERLAPPEDWINDOW,	// ������� �ϴ� ������ ��Ÿ�� ����(WS_OVERLAPPEDWINDOW : �츮�� ���� ���� â ��Ÿ��)
						   CW_USEDEFAULT, 0,  // ����� â�� left, top ��ǥ
						   rcWindow.right - rcWindow.left,
						   rcWindow.bottom - rcWindow.top,  // ����� â�� ����, ���� ����
						   nullptr,		// �θ� �����찡 �ִٸ� �θ� ������ �ڵ��� ����	
						   nullptr,	 // �����쿡�� ����� �޴��� �ڵ� ����	
						   hInstance,// �����츦 ����� ��ü, ���α׷� �ڵ� ���� 
						   nullptr); // �ü���� Ư���� �������� �����	

   if (!hWnd)
   {
      return FALSE;
   }

   g_hWnd = hWnd;

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

// ������ ���� ���̺귯��

// 1. KERNEL : �޸𸮸� �����ϰ� ���α׷��� ����
// 2. USER : ���� �������̽��� �����츦 ����
// 3. GDI : ȭ�� ó���� �׷��� ���

// ���̺귯�� : ���̳ʸ��� ����(������)�� �Լ����� ��Ƴ��� ����

// �ڵ� ������ ���� ��â�� ��� �� �ϳ��̸�, �ٸ� ���α׷����� ����� �� �ֵ��� �ü���� ����Ʈ���� �����ڷ� ���� ����
// ���̺귯���� ��ټ� �Լ����� �Լ��� ���� �� ������� �ʿ�� �ϱ� ������ ��ũ�Ǳ� �� ��ó���⿡ ���� �ش� ��� ������ ���α׷��� �ݵ�� ���Խ��Ѿ� ��
// ���̺귯������ ������� ���α׷��� ��ũ�Ǿ� ������ ������ ������ ���α׷��� �̷�� ��.

//RECT	rc{ 100, 100, 200, 200 };
//list<RECT>	BulletList;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// �޴� ������ ���� �м��մϴ�.
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;

	// DC : ��¿� ���� ������ ���� �ִ� ������ ����ü
	// GDI�� � ����Ʈ(��)���� ���� ����, ����, ���� ���� ����� �����Ѵ�.

	case WM_PAINT:		// �׸��� �޼��� ó�� ����
	{
		PAINTSTRUCT ps;

		HDC hdc = BeginPaint(hWnd, &ps);

		/*Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);	

		for (auto& iter : BulletList)
		{
			Ellipse(hdc, iter.left, iter.top, iter.right, iter.bottom);

			iter.top	-= 10;
			iter.bottom -= 10;

		}*/

		EndPaint(hWnd, &ps);
	}
	break;

	//case WM_CREATE:

	//	SetTimer(hWnd, 0, 0, 0);
	//	// 1���� : ������ �ڵ�
	//	// 2���� : Ÿ�̸��� id��, ������ Ÿ�̸��� ���� ���� ��
	//	// 3���� : Ÿ�̸� �ֱ�(0�� ��� 1000�� 1��)
	//	// 4���� : NULL(0)�� ��� �ֱ��� WM_TIMER �޼����� �߻���Ŵ
	//	break;

	//case WM_TIMER:

	//	InvalidateRect(hWnd, 0, TRUE);	// ������ �׸��� ����(WM_PAINT �޼����� �߻�)
	//	// 1���� : ������ �ڵ�
	//	// 2���� : ������ ���� ����(0 �Ǵ� null�ΰ�� ������ ��ü ������ �ǹ�)
	//	// 3���� : true�� ��� �׷��� �ִ� �ʴ� �κе� ����, false�� ��� ���� �׸��� �κи� ����
	//	
	//	break;


	case WM_KEYDOWN:

		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;

		/*case VK_RIGHT:
			rc.left		+= 10;
			rc.right	+= 10;
			break;

		case VK_LEFT:
			rc.left		-= 10;
			rc.right	-= 10;
			break;

		case VK_UP:
			rc.top		-= 10;
			rc.bottom   -= 10;
			break;

		case VK_DOWN:
			rc.top		+= 10;
			rc.bottom	+= 10;
			break;

		case VK_SPACE:

			BulletList.push_back(rc);

			break;*/
		}

		break;


    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}


// �Լ� ȣ�� �Ծ� : �Լ��� ������ ����Ǹ� �Ҵ� �Ǿ��� ���� �޸𸮸� �����ؾ� �ϴµ� �Լ��� ȣ���� ȣ���(caller)���� ������ ������, ȣ�� ���� ��ȣ����(callee)���� ������ ���� ���, �Ǵ� �Ծ�

// __cdecl : c / c++����� �⺻ ȣ�� �Ծ�, ȣ����� ���� �޸𸮸� ����, ���� �ڱ� �ڽ��� �Ű� ������ � ���� �󸶳� ������ �𸥴�(���� ���� �Լ�), �Լ� ���� ������ ���� �޸� ������ ����

// __stdcall : WIN32 api �⺻ ȣ�� �Ծ�, �� ȣ���ڰ� ���� �޸𸮸� ����, api���� �����ϴ� ��κ��� �Լ����� '���� ���� �Լ�'�̴�. �Ű� ������ � ���� ���� �� �̹� �����Ǿ� �ֱ� ������ ��ȣ���ڰ� �޸��� ũ�⸦ ��� �� �� �־� ������ ���� �޸𸮸� ���� �� �� �ִ�.

// __fastcall : �Լ� ȣ���� ������ ó���ϱ� ���� ȣ�� �Ծ�, ecx�� edx��� �������͸� ���� ����Ǿ� �Լ� ȣ���� �������� �ٰŰ� �ȴ�. �� ȣ���ڰ� ���� �޸𸮸� ����

// __thiscall : �Լ� �Ű� ������ this�����͸� �Ѱ� ���� �� ����ϴ� ȣ�� �Ծ�, �� ȣ���ڰ� ���� �޸𸮸� ����