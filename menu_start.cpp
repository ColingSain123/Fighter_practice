#include <iostream>
#include "Header.h"
#include <conio.h>
#include <Windows.h>
#include <string>
#define ESC 27
#define ENTER 13
#define DOWN 80
#define UP 72

using namespace std;

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); //���������� �������

void MoveCord_X_Y(short x, short y) { //������� ����������� ������ �� ����������� ����������
	SetConsoleCursorPosition(hStdOut, { x,y });
}

void CursorVisible(bool show, short sizecurs) { //������� ��������� ��������� ������� � �������
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hStdOut, &structCursorInfo);
	structCursorInfo.bVisible = show;//���������
	structCursorInfo.dwSize = sizecurs; //������ ��������
	SetConsoleCursorInfo(hStdOut, &structCursorInfo);
}

void rules() { //������� � ���������
	SetColor(13, 0);
	cout << "�� - ���� �������� �� ����, ���� ������ �������� ���������.\n� ��� ���� ����� ��� ������� ���������.\n���� ������ �����, ����� �����, ����� ��� �� �����, ��������� ����,\n������� ���������� ���� ����������. ������ ��������,\n���� ��� � ��, ��� � ��� �������� ������ ������������\n��� ������� ���������� ����. ����� ������� ����!\n(��� ����: 8666 - ���������� ��, 22022022 - ���������� ����,\n2404 - ����� ����, 2404 - ������������ �� �����)\n";
	SetColor(15, 0);
	cout << "\n\n��� ������ ������� ����� ������...";
	_getch();
	system("CLS");
}

int menu_start() {
	int activate_str_of_menu_start = 1;
	char chr;
	CursorVisible(false, 100);
	string menu_start[] = { "<<<����>>>\n","������", "�������", "�����"};
	SetColor(15, 0);
	MoveCord_X_Y(0, 10);
	cout << "��� ���������� ����������� ������ <<UP>>, <<DOWN>>";
	MoveCord_X_Y(8, 11);
	cout << "��� ������ ����������� <<ENTER>>";
	while (true) {
		int x = 16, y = 3;
		MoveCord_X_Y(x, y);

		for (int i = 0; i < 4; i++) { //������������� ����
			if (i == activate_str_of_menu_start) SetColor(3, 0);
			else SetColor(11, 0);
			MoveCord_X_Y(x, y++);
			cout << menu_start[i] << endl;
		}
		chr = _getch();
		if (chr == -32) {
			chr = _getch(); //������� ������ � ����������
		}
		switch (chr)
		{
		case UP: system("CLS"); if (activate_str_of_menu_start > 1) activate_str_of_menu_start--; else break; break;
		case DOWN: system("CLS"); if (activate_str_of_menu_start < 3) activate_str_of_menu_start++; else break; break;
		case ENTER:
			switch (activate_str_of_menu_start)
			{
			case 1:system("CLS"); Game_logic(); break;
			case 2:system("CLS"); rules(); break;
			case 3:system("CLS"); MoveCord_X_Y(x, y); cout << "������..."; exit(0); break;
			default:
				break;
			}
		default:
			break;
		}
		MoveCord_X_Y(x, y);
	}
}