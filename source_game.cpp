#include <iostream>
#include <stdio.h>
#include <random>
#include "Header.h"
#include <string.h>
#include <Windows.h>
#include <conio.h>
#include <random>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <string>
#define ESC 27
#define ENTER 13
#define DOWN 80
#define UP 72

using namespace std;

void SetColor(int text, int background)//функция установления цвета текста и заднего фона
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

int ChekOnInt(int &y_0) { //проврка на ввод
	int coi;
	while (true) {
		if (scanf_s("%d", &coi) == false || getchar() != '\n') {
			while (getchar() != '\n');
			SetColor(12, 0);
			y_0++;
			cout << "Неверный ввод, повторите попытку: ";
			SetColor(15, 0);
		}
		else {
			y_0++;
			return coi;
		}
	}
}

void Win() { //Вывод псевдограффики победы
	string win;
	SetColor(10, 0);
	ifstream f("Win.txt");
	while (!f.eof()) {
		getline(f, win);
		cout << win << endl;
	}
	f.close();
}

void Lose() { //Вывод псевдограффики поражения
	string lose;
	SetColor(4, 0);
	ifstream f("Lose.txt");
	while (!f.eof()){
		getline(f, lose);
		cout << lose << endl;
	}
}

void Draw() { //Вывод псевдограффики ничьей
	string draw;
	SetColor(14, 0);
	ifstream f("Draw.txt");
	while (!f.eof()) {
		getline(f, draw);
		cout << draw << endl;
	}
}

void Random_player(int hit, model *player) { //Функция расчёта дамага и крита ИГРОКА
	int rd = (rand() % 11) + 2;
	if (hit == 1) {
		if (rd < 6) {
			player->damage = 0;
			player->critical = false;
		}
		else if (rd > 5 && rd < 12) {
			player->damage = 1;
			player->critical = false;
		}
		else if (rd == 12) {
			player->damage = 2;
			player->critical = true;
		}
	}
	if (hit == 2) {
		if (rd < 6) {
			player->damage = 0;
			player->critical = false;
		}
		else if (rd > 5 && rd < 12) {
			player->damage = 2;
			player->critical = false;
		}
		else if (rd == 12) {
			player->damage = 3;
			player->critical = true;
		}
	}
	if (hit == 3) {
		if (rd < 7) {
			player->damage = 0;
			player->critical = false;
		}
		else if (rd > 6 && rd < 12) {
			player->damage = 3;
			player->critical = false;
		}
		else if (rd == 12) {
			player->damage = 4;
			player->critical = true;
		}
	}
	if (hit == 4) {
		player->damage = -1;
		player->critical = false;
	}
}

void Random_enemy(model *enemy) {//Функция расчёта дамага и крита ВРАГА
	int rd = (rand() % 11) + 2;
	if (rd < 4) {
		enemy->damage = 0;
		enemy->critical = false;
	}
	else if (rd > 4 && rd < 9) {
		rd = rand() % 2;
		if (rd == 0) {
			enemy->damage = 1;
			enemy->critical = false;
		}
		if (rd == 1) {
			enemy->damage = 2;
			enemy->critical = false;
		}
	}
	else if (rd > 8 && rd < 11) {
		rd = rand() % 7;
		if (rd == 0) {
			enemy->damage = 1;
			enemy->critical = false;
		}
		if (rd == 1 || rd == 2) {
			enemy->damage = 2;
			enemy->critical = false;
		}
		if (rd == 3 || rd == 4) {
			enemy->damage = 3;
			enemy->critical = false;
		}
		if (rd == 5 || rd == 6) {
			enemy->damage = -1;
			enemy->critical = false;
		}
	}
	else if (rd == 12 || rd == 11) {
		rd = rand() % 5;
		if (rd == 0) {
			enemy->damage = 2;
			enemy->critical = true;
		}
		if (rd == 1) {
			enemy->damage = 3;
			enemy->critical =true;
		}
		if (rd == 2 || rd == 3) {
			enemy->damage = 4;
			enemy->critical = true;
		}
		if (rd == 4) {
			enemy->damage = -1;
			enemy->critical = false;
		}
	}
}

void Game_logic() {
	string menu_fight[] = { "Сделайте выбор:","Ударить левой рукой (1 урон)", "Ударить правой рукой (2 урона)", "Ударить ногой (3 урона)", "Поставить блок", "Ввести чит-код"};
	model player, enemy;
	char chr;
	bool menu_true_false;
	int activate_str_of_menu_fight = 1, cheat;
	SetColor(15, 0);
	CursorVisible(true, 100);
	cout << "Введите имя бойца:"; cin >> player.name; cout << endl << endl;
	cout << "Введите имя противника:"; cin >> enemy.name;
	CursorVisible(false, 100);
	system("CLS");
	cout << player.name.c_str() << " выходит на арену против " << enemy.name.c_str() << endl << endl;;

	player.hp = 20;
	player.damage_cheat = 0;
	player.critical = false;
	
	enemy.hp = 20;
	enemy.damage_cheat = 0;
	enemy.critical = false;

	do {
		SetColor(15, 0);
		cout << "Здоровье " << player.name.c_str() << ": ";
		if (player.hp < 9) {
			SetColor(12, 0);
			cout << player.hp;
		}
		if (player.hp < 15 && player.hp > 8) {
			SetColor(14, 0);
			cout << player.hp;
		}
		if (player.hp > 14) {
			SetColor(10, 0);
			cout << player.hp;
		}
		SetColor(15, 0);
		cout << "\nЗдоровье " << enemy.name.c_str() << ": ";
		if (enemy.hp < 9) {
			SetColor(12, 0);
			cout << enemy.hp;
		}
		if (enemy.hp < 15 && enemy.hp > 8) {
			SetColor(14, 0);
			cout << enemy.hp;
		}
		if (enemy.hp > 14) {
			SetColor(10, 0);
			cout << enemy.hp;
		}
		cout << endl;
		menu_true_false = true;
		int y_0 = 0;
		while (menu_true_false) {
			int x = 0, y = 5+y_0;
			for (int i = 0; i < size(menu_fight); i++) { //Отресовывание меню
				if (i == activate_str_of_menu_fight) SetColor(3, 0);
				else SetColor(11, 0);
				MoveCord_X_Y(x, y++);
				cout << menu_fight[i] << endl;
			}

			chr = _getch(); //снятие значения нажатой клавиши
			if (chr == -32) {
				chr = _getch();
			}
			switch (chr){
			case UP:if (activate_str_of_menu_fight > 1) activate_str_of_menu_fight--; else break; break;
			case DOWN:if (activate_str_of_menu_fight < 5) activate_str_of_menu_fight++; else break; break;
			case ENTER:
				switch (activate_str_of_menu_fight){
				case 1:Random_player(1, &player); menu_true_false = false; break;//Левая рука вызов функции расчёта
				case 2:Random_player(2, &player); menu_true_false = false; break;//Правая рука вызов функции расчёта
				case 3:Random_player(3, &player); menu_true_false = false; break;//Удар ногой вызов функции расчёта
				case 4:Random_player(4, &player); menu_true_false = false; break;//БЛОК вывоз функции расчёта
				case 5: SetColor(15, 0);
					cout << "Введите чит-код: ";

					cheat = ChekOnInt(y_0);

					if (cheat == 8666) {
						cout << "Хп востановлены!" << endl;
						y_0++;
						player.hp = 20;
					}
					else if (cheat == 22022022) {
						cout << "Урона повышен на 10 едениц!" << endl;
						y_0++;
						player.damage_cheat = 10;
					}
					else if (cheat == 2404) {
						cout << "Godmod" << endl;
						y_0++;
						player.hp = 9999999;
					}
					else if (cheat == 2401) {
						cout << "Хп врага востановленны!" << endl;
						y_0++;
						enemy.hp = 20;
					}
					else {
						y_0++;
						cout << "Неверный чит код!" << endl;
					}
					y_0 += 8;
					
					break;
				default:break;
				}
			default:break;
			}
		}
		system("CLS");
		Random_enemy(&enemy); //вызов функции расчёта
		SetColor(10, 0);
		if (player.damage > 0) { //Все возможне варинаты удара игрока
			if (enemy.damage >= 0) {
				if (player.damage == 1 && player.critical == false) {
					cout << player.name << " наносит удар по " << enemy.name << " левой рукой на " << player.damage + player.damage_cheat << " ед.урона" << endl;
					enemy.hp -= player.damage + player.damage_cheat;
				}
				if (player.damage == 2 && player.critical == false) {
					cout << player.name << " наносит удар по " << enemy.name << " правой рукой на " << player.damage + player.damage_cheat << " ед.урона" << endl;
					enemy.hp -= player.damage + player.damage_cheat;
				}
				if (player.damage == 3 && player.critical == false) {
					cout << player.name << " наносит удар по " << enemy.name << "  ногой на " << player.damage + player.damage_cheat << " ед.урона" << endl;
					enemy.hp -= player.damage + player.damage_cheat;
				}
				if (player.damage == 2 && player.critical == true) {
					cout << player.name << " наносит критический удар по " << enemy.name << " левой рукой на " << player.damage + player.damage_cheat << " ед.урона" << endl;
					enemy.hp -= player.damage + player.damage_cheat;
				}
				if (player.damage == 3 && player.critical == true) {
					cout << player.name << " наносит критический удар по " << enemy.name << " правой рукой на " << player.damage + player.damage_cheat << " ед.урона" << endl;
					enemy.hp -= player.damage + player.damage_cheat;
				}
				if (player.damage == 4 && player.critical == true) {
					cout << player.name << " наносит критический удар по " << enemy.name << "  ногой на " << player.damage + player.damage_cheat << " ед.урона" << endl;
					enemy.hp -= player.damage + player.damage_cheat;
				}
			}
			if (enemy.damage == -1) {
				if (player.critical == false) {
					cout << player.name << " не пробил блок " << enemy.name << endl;
				}
				else {
					if (player.damage == 2) {
						cout << player.name << " пробивает блок и наносит удар по " << enemy.name << " левой рукой на " << player.damage + player.damage_cheat - 1 << " ед.урона" << endl;
						enemy.hp -= player.damage + player.damage_cheat - 1;
					}
					if (player.damage == 3) {
						cout << player.name << " пробивает блок и наносит удар по " << enemy.name << " правой рукой на " << player.damage + player.damage_cheat - 1 << " ед.урона" << endl;
						enemy.hp -= player.damage + player.damage_cheat - 1;
					}
					if (player.damage == 4) {
						cout << player.name << " пробивает блок и наносит удар по " << enemy.name << "  ногой на " << player.damage + player.damage_cheat - 1 << " ед.урона" << endl;
						enemy.hp -= player.damage + player.damage_cheat - 1;
					}
				}
			}
		}
		if (player.damage == 0) {
			cout << player.name << " промахнулся по " << enemy.name << endl;
		}
		if (player.damage < 0) {
			cout << player.name << " ставит блок!" << endl;
		}

		SetColor(12, 0);
		if (enemy.damage > 0) {//Все возможне варинаты удара врага
			if (player.damage >= 0) {
				if (enemy.damage == 1 && enemy.critical == false) {
					cout << enemy.name << " наносит удар по " << player.name << " левой рукой на " << enemy.damage + enemy.damage_cheat << " ед.урона" << endl;
					player.hp -= enemy.damage + enemy.damage_cheat;
				}
				if (enemy.damage == 2 && enemy.critical == false) {
					cout << enemy.name << " наносит удар по " << player.name << " правой рукой на " << enemy.damage + enemy.damage_cheat << " ед.урона" << endl;
					player.hp -= enemy.damage + enemy.damage_cheat;
				}
				if (enemy.damage == 3 && enemy.critical == false) {
					cout << enemy.name << " наносит удар по " << player.name << "  ногой на " << enemy.damage + enemy.damage_cheat << " ед.урона" << endl;
					player.hp -= enemy.damage + enemy.damage_cheat;
				}
				if (enemy.damage == 2 && enemy.critical == true) {
					cout << enemy.name << " наносит критический удар по " << player.name << " левой рукой на " << enemy.damage + enemy.damage_cheat << " ед.урона" << endl;
					player.hp -= enemy.damage + enemy.damage_cheat;
				}
				if (enemy.damage == 3 && enemy.critical == true) {
					cout << enemy.name << " наносит критический удар по " << player.name << " правой рукой на " << enemy.damage + enemy.damage_cheat << " ед.урона" << endl;
					player.hp -= enemy.damage + enemy.damage_cheat;
				}
				if (enemy.damage == 4 && enemy.critical == true) {
					cout << enemy.name << " наносит критический удар по " << player.name << "  ногой на " << enemy.damage + enemy.damage_cheat << " ед.урона" << endl;
					player.hp -= enemy.damage + enemy.damage_cheat;
				}
			}
			if (player.damage == -1) {
				if (enemy.critical == false) {
					cout << enemy.name << " не пробил блок " << player.name << endl;
				}
				else {
					if (enemy.damage == 2) {
						cout << enemy.name << " пробивает блок и наносит удар по " << player.name << " левой рукой на " << enemy.damage + enemy.damage_cheat - 1 << " ед.урона" << endl;
						player.hp -= enemy.damage + enemy.damage_cheat - 1;
					}
					if (enemy.damage == 3) {
						cout << enemy.name << " пробивает блок и наносит удар по " << player.name << " правой рукой на " << enemy.damage + enemy.damage_cheat - 1 << " ед.урона" << endl;
						player.hp -= enemy.damage + enemy.damage_cheat - 1;
					}
					if (enemy.damage == 4) {
						cout << enemy.name << " пробивает блок и наносит удар по " << player.name << "  ногой на " << enemy.damage + enemy.damage_cheat - 1 << " ед.урона" << endl;
						player.hp -= enemy.damage + enemy.damage_cheat - 1;
					}
				}
			}
		}
		if (enemy.damage == 0) {
			cout << enemy.name << " промахнулся по " << player.name << endl;
		}
		if (enemy.damage < 0) {
			cout << enemy.name << " ставит блок!" << endl;
		}
		if (player.hp <= 0 && enemy.hp > 0) {
			SetColor(15, 0);
			cout << "Здоровье " << player.name.c_str() << ": ";
			if (player.hp < 9) {
				SetColor(12, 0);
				cout << player.hp;
			}
			if (player.hp < 15 && player.hp > 8) {
				SetColor(14, 0);
				cout << player.hp;
			}
			if (player.hp > 14) {
				SetColor(10, 0);
				cout << player.hp;
			}
			SetColor(15, 0);
			cout << "\nЗдоровье " << enemy.name.c_str() << ": ";
			if (enemy.hp < 9) {
				SetColor(12, 0);
				cout << enemy.hp;
			}
			if (enemy.hp < 15 && enemy.hp > 8) {
				SetColor(14, 0);
				cout << enemy.hp;
			}
			if (enemy.hp > 14) {
				SetColor(10, 0);
				cout << enemy.hp;
			}
			SetColor(4, 0);
			cout << "\nПоражение!" << endl;
			Lose(); //Псевдограффика
		}
		if (player.hp > 0 && enemy.hp <= 0) {
			SetColor(15, 0);
			cout << "Здоровье " << player.name.c_str() << ": ";
			if (player.hp < 9) {
				SetColor(12, 0);
				cout << player.hp;
			}
			if (player.hp < 15 && player.hp > 8) {
				SetColor(14, 0);
				cout << player.hp;
			}
			if (player.hp > 14) {
				SetColor(10, 0);
				cout << player.hp;
			}
			SetColor(15, 0);
			cout << "\nЗдоровье " << enemy.name.c_str() << ": ";
			if (enemy.hp < 9) {
				SetColor(12, 0);
				cout << enemy.hp;
			}
			if (enemy.hp < 15 && enemy.hp > 8) {
				SetColor(14, 0);
				cout << enemy.hp;
			}
			if (enemy.hp > 14) {
				SetColor(10, 0);
				cout << enemy.hp;
			}
			SetColor(2, 0);
			cout << "\nПобеда!";
			Win(); //Псевдограффика
		}
		if (player.hp <= 0 && enemy.hp <= 0) {
			SetColor(15, 0);
			cout << "Здоровье " << player.name.c_str() << ": ";
			if (player.hp < 9) {
				SetColor(12, 0);
				cout << player.hp;
			}
			if (player.hp < 15 && player.hp > 8) {
				SetColor(14, 0);
				cout << player.hp;
			}
			if (player.hp > 14) {
				SetColor(10, 0);
				cout << player.hp;
			}
			SetColor(15, 0);
			cout << "\nЗдоровье " << enemy.name.c_str() << ": ";
			if (enemy.hp < 9) {
				SetColor(12, 0);
				cout << enemy.hp;
			}
			if (enemy.hp < 15 && enemy.hp > 8) {
				SetColor(14, 0);
				cout << enemy.hp;
			}
			if (enemy.hp > 14) {
				SetColor(10, 0);
				cout << enemy.hp;
			}
			SetColor(14, 0);
			cout << "\nНичья!";
			Draw(); //Псевдограффика
		}
	} while (player.hp > 0 && enemy.hp > 0);
	SetColor(15, 0);
	cout << "Для продолжения нажмите любую клавишу...";
	_getch();
	system("CLS");
	menu_start(); //Вызов функции меню
}