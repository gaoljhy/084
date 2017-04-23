#define _AFXDLL
#define _CRT_SECURE_NO_WARNINGS
#include <afx.h>
#include <fstream>
#include <windows.h>
#include <stdlib.h>
#include <afxdlgs.h>
#include <vector>
#include "resource.h"

using namespace std;

INT_PTR WINAPI getback(
	_In_ HWND   hwndDlg,
	_In_ UINT   uMsg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
);
bool chose(CHAR ch_all[60] , INT numt);

void save_grade(CHAR ch_all[60], CHAR ch[3]);

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
)
{

	DialogBox(hInstance ,LPCSTR(IDD_MAIN) ,NULL ,getback );
	


	
	

	return 0;
}

INT_PTR WINAPI getback(
	_In_ HWND   hwndDlg,
	_In_ UINT   uMsg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
)
{
	static CHAR ch_all[60] = { 0 };
	static INT numt = 0;

	switch (uMsg)
	{
	case WM_COMMAND:
		if (LOWORD(wParam)==IDOK)
		{
			CStdioFile pfile(stdin);
			pfile.Open("allstudent.txt",  CFile::modeRead);

			TCHAR szBuf[6000] = { 0 }, szLine[50] = { 0 };
			for (int  i = 0; pfile.ReadString(szLine, sizeof(szLine)) != NULL; i++)
			{
				szLine[49] = '\n';
				StrCat(szBuf ,szLine);
			}// 读取文件.

			SetDlgItemText( hwndDlg , IDC_EDIT1 , szBuf);
			pfile.Close();
			return TRUE;	
		}
		if (LOWORD(wParam)==IDCANCEL)
		{
			EndDialog(hwndDlg, IDCANCEL);
			return TRUE;
		}
		if (LOWORD(wParam)==IDOK2)
		{
			numt++;
			chose(ch_all , numt);
			SetDlgItemText(hwndDlg , IDC_EDIT2 ,ch_all);
			numt++;
			return TRUE;
			
		}
		if (LOWORD(wParam) == IDOK3 )
		{
			CHAR ch[5] = { 0 };
			ch[4] = '\0';

				
				GetDlgItemText(hwndDlg, IDC_EDIT3 , ch, sizeof(ch));
				
				if (atoi(ch) == 0)
				{
					
					MessageBoxA(hwndDlg, "成绩不能为空！" , "警告", MB_OK);
				}
				else if (atoi(ch) >100 || atoi(ch)<0)
				{
					
					MessageBoxA(hwndDlg, "成绩在100到0之间！" , "警告", MB_OK);
				}
			save_grade(ch_all, ch);
			return true;
		}
















		break;
	default:
		break;
	}
	

	return false;
}



bool chose(CHAR ch_all[60] , INT numt )
{
	fstream fp, ft;

	srand((unsigned int)time_t(numt));
	int temp = 0;
	
	int bl = 1;
	while (bl)
	{
		fp.open("allstudent.txt", ios::in | ios::out);
		ft.open("randed.txt", ios::in | ios::out);
		temp = (rand() % 63);

		for (int i = 0; i < temp; i++)
		{
			char ch[80] = { 0 };
			fp.getline(ch, sizeof(ch), '\n');
		}
		char ch03[63][3] = { 0 };
		char ch01[3] = { 0 };
		char ch02[15] = { 0 }; //学号
		char ch04[10] = { 0 };//姓名
		char ch05[10] = { 0 };//班级
		//char ch_all[60] = { 0 };//所有信息
		fp >> ch01 >> ch02 >> ch04 >> ch05;
		sprintf(ch_all, "%s %s %s %s", ch01, ch02, ch04, ch05);
		ch01[2] = '\0';
		ch02[14] = '\0';
		ch04[9] = '\0';
		ch05[9] = '\0';
		fp.close();
		for (int i = 0; i < 63; i++)
		{
			char ch[80] = { 0 };
			ft >> ch03[i];
			ch03[i][2] = '\0';
			ft.getline(ch, sizeof(ch), '\n');

			if (!strcmp(ch01, ch03[i]))
			{
				//已抽过
				bl = 2;
				break;

			}

			else if (ft.eof())
			{
				//未抽过
				bl = 0;
				return true;

			}


		}
		ft.close();

	}
	return false;
}
	
void save_grade(CHAR ch_all[60] ,CHAR ch[3])
{
	fstream ft;

	ft.open("randed.txt", ios::ate | ios::out | ios::in);
	ft << '\n' << ch_all << " " << ch;
	ft.close();
}
