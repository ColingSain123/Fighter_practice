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

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); //дискриптор консоли

void MoveCord_X_Y(short x, short y) { //Функция перемещения символ по определённой координате
	SetConsoleCursorPosition(hStdOut, { x,y });
}

void CursorVisible(bool show, short sizecurs) { //Функция включения видимости курсора в консоли
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hStdOut, &structCursorInfo);
	structCursorInfo.bVisible = show;//видимость
	structCursorInfo.dwSize = sizecurs; //размер очевидно
	SetConsoleCursorInfo(hStdOut, &structCursorInfo);
}

void rules() { //функция с правилами
	SetColor(13, 0);
	cout << "Вы - боец попавший на ринг, ваша задача победить соперника.\nУ вас есть выбор как ударить аппонента.\nУдар правой рукой, левой рукой, ногой или же вовсе, поставить блок,\nкоторый невелирует урон противника. Будьте осторожы,\nведь как и вы, так и ваш соперник можете промахнуться\nили нанести критиеский удар. Желаю удачной игры!\n(чит коды: 8666 - пополнение хп, 22022022 - повышенный урон,\n2404 - режим бога, 2404 - восстановить хп врага)\n";
	SetColor(15, 0);
	cout << "\n\nДля выхода нажмите любую кнопку...";
	_getch();
	system("CLS");
}

int menu_start() {
	int activate_str_of_menu_start = 1;
	char chr;
	CursorVisible(false, 100);
	string menu_start[] = { "<<<БОЕЦ>>>\n","Играть", "Правила", "Выход"};
	SetColor(15, 0);
	MoveCord_X_Y(0, 10);
	cout << "Для управления используйте клавиш <<UP>>, <<DOWN>>";
	MoveCord_X_Y(8, 11);
	cout << "Для выбора используйте <<ENTER>>";
	while (true) {
		int x = 16, y = 3;
		MoveCord_X_Y(x, y);

		for (int i = 0; i < 4; i++) { //Отресовывание меню
			if (i == activate_str_of_menu_start) SetColor(3, 0);
			else SetColor(11, 0);
			MoveCord_X_Y(x, y++);
			cout << menu_start[i] << endl;
		}
		chr = _getch();
		if (chr == -32) {
			chr = _getch(); //снимаем данные с клавиатуры
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
			case 3:system("CLS"); MoveCord_X_Y(x, y); cout << "Выхожу..."; exit(0); break;
			default:
				break;
			}
		default:
			break;
		}
		MoveCord_X_Y(x, y);
	}
}