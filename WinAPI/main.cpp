#include<Windows.h>
#include"resource.h"


BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


//#define MESSAGE_BOX
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
#ifdef MESSAGE_BOX 
	//��������� ����
//1 �������� ������������ ����, 2� ���������,3 ��������� ����,4 FLAGS BITS(��������� ���� ������� �� ����� �������������)
	MessageBox
	(
		NULL,
		"���������? �� �����!\n � ����))\n����� ������� ���� \t'���������'",
		"BooOoO"/*NULL*/,
		MB_YESNOCANCEL | MB_ICONINFORMATION | MB_HELP | MB_DEFBUTTON3 | MB_SYSTEMMODAL
	);
#endif // MESSAGE_BOX 

	DialogBoxParam(hInstance, MAKEINTRESOURCEA(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);

	return 0;
}

VOID EditPlaseholder (HWND hwnd, int editControlId, UINT eventCode, const char* placeholderText)
{
		HWND hEdit = GetDlgItem(hwnd, editControlId);// �� ���� ��� ������
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
			//�� ��� ������ � ���������� ���������
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
	case WM_INITDIALOG://����������� 1 ��� ��� ������� ����
	{
        #define  EM_GETCUEBANNER "������� �����"
        #define  PLACEHOLDER_TEXT "������� ������"
		HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
		SetWindowTextA(hEditLogin, EM_GETCUEBANNER);//if A(char*) else W(WCHAR_T*)
		HWND hEditPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);
		SetWindowTextA(hEditPassword, PLACEHOLDER_TEXT);
		
		break;
	}
	case WM_COMMAND://������������ ������� ������, ����������� ���� � �.�//��� ���� ������������ ������
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
		//		// ������� ���������, ���� ��� ������ ������������
		//		GetWindowTextA(hEditLogin, sz_buffer, SIZE);
		//		if (strcmp(sz_buffer, EM_GETCUEBANNER) == 0)
		//		{
		//			SetWindowTextA(hEditLogin, "");
		//		}
		//		break;
		//	}
		//	case EN_KILLFOCUS:
		//	{
		//		//�� ��� ������ � ���������� ���������
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
		case IDOK: MessageBox(hwnd, "���� ������ ������ 'ok'", "Info", MB_OK | MB_ICONINFORMATION); break;
		case IDCANCEL:
			EndDialog(hwnd, 0);
			break;

			break;

		case WM_CLOSE:/*������������ ��� ������� �� ������ �������*/

			EndDialog(hwnd, 0);
			break;
		}
	}
	
	return FALSE;
	}