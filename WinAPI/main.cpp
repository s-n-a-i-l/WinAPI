#include<Windows.h>
#include"resource.h"


BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
bool is�lueShown = true;// ������ ���� �� ��������� ������ ����

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

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
   
	switch (uMsg)
	{
	case WM_INITDIALOG://����������� 1 ��� ��� ������� ����
	{
#define  EM_GETCUEBANNER "������� �����"
		HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
		SetWindowTextA(hEditLogin, EM_GETCUEBANNER);//if A(char*) else W(WCHAR_T*)

		break;
	}
	case WM_COMMAND://������������ ������� ������, ����������� ���� � �.�//��� ���� ������������ ������
	{
		if (LOWORD(wParam) == IDC_EDIT_LOGIN)
		{
			HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
			CONST INT SIZE = 265;
			CHAR sz_buffer[SIZE] = {};

			switch (HIWORD(wParam))
			{
			case EN_SETFOCUS:
			{
				// ������� ���������, ���� ��� ������ ������������
				GetWindowTextA(hEditLogin, sz_buffer, sizeof(sz_buffer));
				if (strcmp(sz_buffer, EM_GETCUEBANNER) == 0)
				{
					SetWindowTextA(hEditLogin, "");
				}
				break;
			}
			case EN_KILLFOCUS:
			{
				// ���� ������������ �� ��� ������ � ���������� ���������
				GetWindowTextA(hEditLogin, sz_buffer, sizeof(sz_buffer));
				if (strlen(sz_buffer) == 0)
				{
					SetWindowTextA(hEditLogin, EM_GETCUEBANNER);
				}
				break;
			}

			}
		}
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