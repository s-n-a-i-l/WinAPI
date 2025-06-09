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

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG://����������� 1 ��� ��� ������� ����
		break;

	case WM_COMMAND://������������ ������� ������, ����������� ���� � �.�

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
		case IDCANCEL:EndDialog(hwnd, 0);
			break;
		}
		break;

	case WM_CLOSE:/*������������ ��� ������� �� ������ �������*/

		EndDialog(hwnd, 0);
		break;
	}
	return FALSE;
}