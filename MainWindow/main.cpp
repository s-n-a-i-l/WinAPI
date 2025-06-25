#include<Windows.h>
#include<string>
#include<sstream>



CONST CHAR g_sz_CLASS_NAME[] = " ";//��������� � ������ ������ ���� ���� ���
//��� ������ ����- ��� ������� ������

// ������ ������ ������������
INT ScrWidht = GetSystemMetrics(SM_CXSCREEN);
INT ScrHeight = GetSystemMetrics(SM_CYSCREEN);

//������ ���� 75% �� ������� ������
INT wWidht = ScrWidht * 3 / 4;
INT wHeight = ScrHeight * 3 / 4;

//���������� �� �,�
INT wX = (ScrWidht - wWidht) / 2;
INT wY = (ScrHeight - wHeight) / 2;

INT WINAPI WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE pRevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//1)����������� ������ ����
	WNDCLASSEX wClass;//struktura tip dannih
	ZeroMemory(&wClass, sizeof(wClass));

	wClass.style = 0;
	wClass.cbSize = sizeof(wClass);
	wClass.cbWndExtra = 0;
	wClass.cbClsExtra = 0;

	wClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wClass.hbrBackground = (HBRUSH)COLOR_WINDOW;

	wClass.hInstance = hInstance;
	wClass.lpfnWndProc = (WNDPROC)WndProc;
	wClass.lpszMenuName = NULL;
	wClass.lpszClassName = g_sz_CLASS_NAME;

	if (RegisterClassEx(&wClass) == NULL)
	{
		MessageBox(NULL, "Class registration falied", "", MB_OK | MB_ICONERROR);
		return 0;
	}

	//2)�������� ����
	HWND hwnd = CreateWindowEx
	(
		NULL,//ExStyle
		g_sz_CLASS_NAME,//className
		g_sz_CLASS_NAME,//WindowName(Title)
		WS_OVERLAPPEDWINDOW,//����� ����� ��������� ��� ���� ������� ����
		//��� ���� ����� ������������ ��� ������ ��������������
		wX, wY,//POSITION
		wWidht, wHeight,//SIZE
		NULL,//PARENTWINDOW
		NULL,//������ ���� ��� �������� ���� ��� �� id ������� ��� ��������� ����
		hInstance,//��������� ��� ����� ����� ���������
		NULL
	);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation falied", "", MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);//������ ����� ����������� ����:���������� �� ���� �����,�������� � ����, �������� �� ������ �����
	UpdateWindow(hwnd);//������������� ������� ������� ����

	//3)������ ����� ���������
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.message;
}


INT WINAPI WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{
		std::wstringstream ss;
		ss << "Size:" << wWidht << "x" << wHeight << "   x:"<< wX <<"   y:" << wY;

		SetWindowTextW(hwnd, ss.str().c_str());
	}
		break;
	case WM_COMMAND:break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return FALSE;
}
