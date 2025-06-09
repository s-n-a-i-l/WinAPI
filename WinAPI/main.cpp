#include<Windows.h>
#include"resource.h"

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//#define MESSAGE_BOX
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
#ifdef MESSAGE_BOX 
	//КОДИРОВКА АСКИ
//1 параметр родительское окно, 2й сообщение,3 ЗАГОЛОВОК ОКНА,4 FLAGS BITS(отдельные биты которые мы можем комбинировать)
	MessageBox
	(
		NULL,
		"Испугался? не бойся!\n я друг))\nсамое простое окно \t'сообщение'",
		"BooOoO"/*NULL*/,
		MB_YESNOCANCEL | MB_ICONINFORMATION | MB_HELP | MB_DEFBUTTON3 | MB_SYSTEMMODAL
	);
#endif // MESSAGE_BOX 

	DialogBoxParam(hInstance, MAKEINTRESOURCEA(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);

	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG://выполняется 1 раз при запуске окна
		break;

	case WM_COMMAND://обрабатывает нажатие кнопок, перемещение мыши и т.д

		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_COPY:
		{
			HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
			HWND hEditPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);
			CONST INT SIZE = 265;
			CHAR sz_buffer[SIZE] = {};
			SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			SendMessage(hEditPassword, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}	
		break;
		case IDOK: MessageBox(hwnd, "Была нажата кнопка 'ok'", "Info", MB_OK | MB_ICONINFORMATION); break;
		case IDCANCEL:EndDialog(hwnd, 0);
			break;
		}
		break;

	case WM_CLOSE:/*отрабатывает при нажатии на кнопку закрыть*/

		EndDialog(hwnd, 0);
		break;
	}
	return FALSE;
}