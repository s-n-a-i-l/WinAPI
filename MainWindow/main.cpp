#include<Windows.h>
#include<string>
#include<sstream>



CONST CHAR g_sz_CLASS_NAME[] = " ";//абсолютно у любого класса окна есть имя
//имя класса окна- это обычная строка

// размер экрана пользователя
INT ScrWidht = GetSystemMetrics(SM_CXSCREEN);
INT ScrHeight = GetSystemMetrics(SM_CYSCREEN);

//размер окна 75% от размера экрана
INT wWidht = ScrWidht * 3 / 4;
INT wHeight = ScrHeight * 3 / 4;

//калибровка по х,у
INT wX = (ScrWidht - wWidht) / 2;
INT wY = (ScrHeight - wHeight) / 2;

INT WINAPI WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE pRevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//1)Регистрация класса окна
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

	//2)Создание окна
	HWND hwnd = CreateWindowEx
	(
		NULL,//ExStyle
		g_sz_CLASS_NAME,//className
		g_sz_CLASS_NAME,//WindowName(Title)
		WS_OVERLAPPEDWINDOW,//Такой стиль создается для всех главных окон
		//Это окно будет родительским для других оконприложения
		wX, wY,//POSITION
		wWidht, wHeight,//SIZE
		NULL,//PARENTWINDOW
		NULL,//строка меню для главного окна или же id ресурса для дочернего окна
		hInstance,//экземпляр ехе файла нашей программы
		NULL
	);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation falied", "", MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);//задает режим отображения окна:развернуто на весь экран,свернуто в окно, свернуть на панель задач
	UpdateWindow(hwnd);//прорисовывает рабочую область окна

	//3)Запуск цикла сообщений
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
