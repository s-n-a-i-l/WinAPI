#include<Windows.h>	
#include<cstdio>
#include <vector>
#include <string>
#include"resource.h"

std::vector<std::string> G_SZ_VALUES = {};
INT EDIT_INDEX = -1;

void SaveToFile(const std::vector<std::string>& data, const char* filename)
{
	FILE* file = fopen(filename, "w");//открою файл (имя файла, режим запись"w")
	if (!file) return;// не удалось открыть
	for (const auto& str : data)// ПРОЙТИ ПО КАЖДОЙ СТРОКЕ
		fprintf(file, "%s\n", str.c_str());//записать ф вайл с переводом
	fclose(file);//закрою файл
}
void LoadFromFile(std::vector<std::string>& data, const char* filename)
{
	FILE* file = fopen(filename, "r");
	if (!file) return;
	char zs_buffer[256];
	while (fgets(zs_buffer, sizeof(zs_buffer), file))
	{
		zs_buffer[strcspn(zs_buffer, "\n")] = 0; // удаляем \n
		data.push_back(zs_buffer);
	}
	fclose(file);
}

BOOL CALLBACK EditDlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		// записываю переданный текст в поле редактирования
		const char* initText = (const char*)lParam;
		SetWindowTextA(GetDlgItem(hwnd, IDC_EDIT_REDACT), initText);
		SetFocus(GetDlgItem(hwnd, IDC_EDIT_REDACT));//автофокус
		return FALSE; // фокус установлен вручную
	}
	break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			char sz_buffer[256];
			GetWindowTextA(GetDlgItem(hwnd, IDC_EDIT_REDACT), sz_buffer, sizeof(sz_buffer));

			if (strlen(sz_buffer) > 0 && EDIT_INDEX >= 0 && (size_t)EDIT_INDEX < G_SZ_VALUES.size())
			{
				// обновляю вектор
				G_SZ_VALUES[EDIT_INDEX] = sz_buffer;

				// обновляю  ListBox
				HWND hList = GetDlgItem(GetParent(hwnd), IDC_LISTBOX);
				SendMessageA(hList, LB_DELETESTRING, EDIT_INDEX, 0);
				SendMessageA(hList, LB_INSERTSTRING, EDIT_INDEX, (LPARAM)sz_buffer);

				SaveToFile(G_SZ_VALUES, "data.txt");
			}
			EndDialog(hwnd, 0);
		}
		break;

		case IDCANCEL:
			EndDialog(hwnd, 0);
			break;
		}
		break;
	}
	return FALSE;
}
BOOL CALLBACK AddDlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		SetFocus(GetDlgItem(hwnd, IDC_EDIT_ADD));//установить фокус курсора чтобы вводить сразу при пуске окна
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			char zs_buffer[256];
			GetWindowTextA(GetDlgItem(hwnd, IDC_EDIT_ADD), zs_buffer, sizeof(zs_buffer));
			if (strlen(zs_buffer) > 0)
			{
				G_SZ_VALUES.push_back(zs_buffer); // добавляем в вектор
				SaveToFile(G_SZ_VALUES, "data.txt");
				// обновим список в главном окне
				HWND hParentList = GetDlgItem(GetParent(hwnd), IDC_LISTBOX);
				SendMessageA(hParentList, LB_ADDSTRING, 0, (LPARAM)zs_buffer);
			}
			EndDialog(hwnd, 0);

		}
		break;
		case IDCANCEL:
			EndDialog(hwnd, 0);

			break;
		}

	}
	return FALSE;
}
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		//GetModulHandle(NULL) возвращает hInstanse нашего ехе файла
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);

		G_SZ_VALUES.clear();
		LoadFromFile(G_SZ_VALUES, "data.txt");

		HWND hList = GetDlgItem(hwnd, IDC_LISTBOX);
		for (const auto& str : G_SZ_VALUES)
		{
			SendMessageA(hList, LB_ADDSTRING, 0, (LPARAM)str.c_str());
		}

	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_LISTBOX:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				HWND hList = GetDlgItem(hwnd, IDC_LISTBOX);
				int sel = (int)SendMessage(hList, LB_GETCURSEL, 0, 0);//вернёт индекс выбранного элемента (от 0 и выше) — если элемент выбран.LB_ERR (обычно -1) — если ничего не выбрано.
				if (sel != LB_ERR)
				{
					EDIT_INDEX = sel;
					char sz_buffer[256] = {};
					SendMessageA(hList, LB_GETTEXT, sel, (LPARAM)sz_buffer);
					DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG_REDACT), hwnd, EditDlgProc, (LPARAM)sz_buffer);
				}
			}
			break;
		}
		case IDC_BUTTON_REMOVE:
		{
			HWND hList = GetDlgItem(hwnd, IDC_LISTBOX);
			INT i = SendMessage(hList, LB_GETCURSEL, 0, 0);
			if (i != LB_ERR)
			{
				if ((size_t)i < G_SZ_VALUES.size())
				{
					G_SZ_VALUES.erase(G_SZ_VALUES.begin() + i);// удаление из вектора G_SZ_VALUES
				}

				SendMessage(hList, LB_DELETESTRING, i, 0);// удаление из ListBox

				SaveToFile(G_SZ_VALUES, "data.txt");// обновить файл после удаления
			}
			else
			{
				MessageBox(hwnd, "Выберите элемент для удаления", "Ошибка", MB_OK | MB_ICONWARNING);
			}
			break;
		}
		case IDC_BUTTON_ADD:
		{
			DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG_ADD), hwnd, AddDlgProc, 0);
			break;
		}
		case IDOK:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			CHAR sz_message[SIZE] = {};

			HWND hList = GetDlgItem(hwnd, IDC_LISTBOX);
			INT i = SendMessage(hList, LB_GETCURSEL, 0, 0);
			if (i == LB_ERR) //(-1)
			{
				strcpy(sz_message, "Выберите ваш вариант");
			}
			else 
			{
				SendMessage(hList, LB_GETTEXT, i, (LPARAM)sz_buffer);
				sprintf(sz_message, "Вы выбрали пункт № %d со значением '%s'", i, sz_buffer);
			}

			MessageBox(hwnd, sz_message, "Info", MB_OK | MB_ICONINFORMATION);
			//SendMessage(hList, CB_GETLBTEXT, i, (LPARAM)sz_buffer);
			//if (i == -1) strcpy(sz_message, "Выберите ваш вариант");
			//else
			//	//sz_message эта строка будет содержать результат форматирования
			//	//"Вы выбрали.." эта строка содержит формат, в ней указывается куда именно ставить значения,
			//	// идущие после этой строки,в данном случае это i и sz_buffer
			//	// sprintf() это функция с произвольным числом параметров
			//	//спецификатор %i заменяется целочисленным значением
			//	//спецификатор %s заменяется строкой
			//	//%е дробное числои тд
			//	sprintf(sz_message, "Вы выбрали пунт № %i со значением '%s'", i, sz_buffer);
			//MessageBox(hwnd, sz_message, "Info", MB_OK | MB_ICONINFORMATION);
			break;
		}
		case IDCANCEL:  EndDialog(hwnd, 0);break;
		case WM_CLOSE:  EndDialog(hwnd, 0);break;
		}
		}
	}
   return FALSE;
}
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG_MAIN), NULL, DlgProc, 0);
	return 0;
}


