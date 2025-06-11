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

VOID EditPlaseholder (HWND hwnd, int editControlId, UINT eventCode, const char* placeholderText)
{
		HWND hEdit = GetDlgItem(hwnd, editControlId);// по айди что меняем
		if (!hEdit) return;

		CONST INT SIZE = 265;
		CHAR sz_buffer[SIZE] = {};
		GetWindowTextA(hEdit, sz_buffer, SIZE);

		switch (eventCode)
		{
		case EN_SETFOCUS:
		{
			if (strcmp(sz_buffer, placeholderText) == 0)
			{
				SetWindowTextA(hEdit, "");
			}
			break;
		}
		case EN_KILLFOCUS:
		{
			//не ввёл ничего — возвращаем подсказку
			GetWindowTextA(hEdit, sz_buffer, SIZE);
			if (strlen(sz_buffer) == 0)
			{
				SetWindowTextA(hEdit, placeholderText);
			}
			break;
		}

		}
	
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
   
	switch (uMsg)
	{
	case WM_INITDIALOG://выполняется 1 раз при запуске окна
	{
        #define  EM_GETCUEBANNER "Введите Логин"
        #define  PLACEHOLDER_TEXT "Введите Пароль"
		HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
		SetWindowTextA(hEditLogin, EM_GETCUEBANNER);//if A(char*) else W(WCHAR_T*)
		HWND hEditPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);
		SetWindowTextA(hEditPassword, PLACEHOLDER_TEXT);
		
		break;
	}
	case WM_COMMAND://обрабатывает нажатие кнопок, перемещение мыши и т.д//тут надо обрабатывать курсор
	{
		if (LOWORD(wParam) == IDC_EDIT_LOGIN || IDC_EDIT_PASSWORD)
		{
			const char* plaseholder = (LOWORD(wParam) == IDC_EDIT_LOGIN) ? EM_GETCUEBANNER : PLACEHOLDER_TEXT;
			EditPlaseholder(hwnd, IDC_EDIT_LOGIN, HIWORD(wParam), plaseholder);
			EditPlaseholder(hwnd, IDC_EDIT_PASSWORD, HIWORD(wParam), plaseholder);
		}


		//if (LOWORD(wParam) == IDC_EDIT_LOGIN)
		//{

		//	HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
		//	CONST INT SIZE = 265;
		//	CHAR sz_buffer[SIZE] = {};

		//	switch (HIWORD(wParam))
		//	{
		//	case EN_SETFOCUS:
		//	{
		//		// Удаляем подсказку, если она сейчас отображается
		//		GetWindowTextA(hEditLogin, sz_buffer, SIZE);
		//		if (strcmp(sz_buffer, EM_GETCUEBANNER) == 0)
		//		{
		//			SetWindowTextA(hEditLogin, "");
		//		}
		//		break;
		//	}
		//	case EN_KILLFOCUS:
		//	{
		//		//не ввёл ничего — возвращаем подсказку
		//		GetWindowTextA(hEditLogin, sz_buffer, SIZE);
		//		if (strlen(sz_buffer) == 0)
		//		{
		//			SetWindowTextA(hEditLogin, EM_GETCUEBANNER);
		//		}
		//		break;
		//	}

		//	}
		//}
		//if (LOWORD(wParam) == IDC_EDIT_PASSWORD)
		//{

		//	HWND hEditPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);
		//	CONST INT SIZE = 265;
		//	CHAR sz_buffer[SIZE] = {};

		//	switch (HIWORD(wParam))
		//	{
		//	case EN_SETFOCUS:
		//	{
		//		
		//		GetWindowTextA(hEditPassword, sz_buffer, SIZE);
		//		if (strcmp(sz_buffer, PLACEHOLDER_TEXT) == 0)
		//		{
		//			SetWindowTextA(hEditPassword, "");
		//		}
		//		break;
		//	}
		//	case EN_KILLFOCUS:
		//	{
		//		
		//		GetWindowTextA(hEditPassword, sz_buffer, SIZE);
		//		if (strlen(sz_buffer) == 0)
		//		{
		//			SetWindowTextA(hEditPassword, PLACEHOLDER_TEXT);
		//		}
		//		break;
		//	}

		//	}
		//}
	}
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
		case IDCANCEL:
			EndDialog(hwnd, 0);
			break;

			break;

		case WM_CLOSE:/*отрабатывает при нажатии на кнопку закрыть*/

			EndDialog(hwnd, 0);
			break;
		}
	}
	
	return FALSE;
	}