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

void SetColor(int text, int background)//������� ������������ ����� ������ � ������� ����
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

int ChekOnInt(int &y_0) { //������� �� ����
	int coi;
	while (true) {
		if (scanf_s("%d", &coi) == false || getchar() != '\n') {
			while (getchar() != '\n');
			SetColor(12, 0);
			y_0++;
			cout << "�������� ����, ��������� �������: ";
			SetColor(15, 0);
		}
		else {
			y_0++;
			return coi;
		}
	}
}

void Win() { //����� �������������� ������
	string win;
	SetColor(10, 0);
	ifstream f("Win.txt");
	while (!f.eof()) {
		getline(f, win);
		cout << win << endl;
	}
	f.close();
}

void Lose() { //����� �������������� ���������
	string lose;
	SetColor(4, 0);
	ifstream f("Lose.txt");
	while (!f.eof()){
		getline(f, lose);
		cout << lose << endl;
	}
}

void Draw() { //����� �������������� ������
	string draw;
	SetColor(14, 0);
	ifstream f("Draw.txt");
	while (!f.eof()) {
		getline(f, draw);
		cout << draw << endl;
	}
}

void Random_player(int hit, model *player) { //������� ������� ������ � ����� ������
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

void Random_enemy(model *enemy) {//������� ������� ������ � ����� �����
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
	string menu_fight[] = { "�������� �����:","������� ����� ����� (1 ����)", "������� ������ ����� (2 �����)", "������� ����� (3 �����)", "��������� ����", "������ ���-���"};
	model player, enemy;
	char chr;
	bool menu_true_false;
	int activate_str_of_menu_fight = 1, cheat;
	SetColor(15, 0);
	CursorVisible(true, 100);
	cout << "������� ��� �����:"; cin >> player.name; cout << endl << endl;
	cout << "������� ��� ����������:"; cin >> enemy.name;
	CursorVisible(false, 100);
	system("CLS");
	cout << player.name.c_str() << " ������� �� ����� ������ " << enemy.name.c_str() << endl << endl;;

	player.hp = 20;
	player.damage_cheat = 0;
	player.critical = false;
	
	enemy.hp = 20;
	enemy.damage_cheat = 0;
	enemy.critical = false;

	do {
		SetColor(15, 0);
		cout << "�������� " << player.name.c_str() << ": ";
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
		cout << "\n�������� " << enemy.name.c_str() << ": ";
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
			for (int i = 0; i < size(menu_fight); i++) { //������������� ����
				if (i == activate_str_of_menu_fight) SetColor(3, 0);
				else SetColor(11, 0);
				MoveCord_X_Y(x, y++);
				cout << menu_fight[i] << endl;
			}

			chr = _getch(); //������ �������� ������� �������
			if (chr == -32) {
				chr = _getch();
			}
			switch (chr){
			case UP:if (activate_str_of_menu_fight > 1) activate_str_of_menu_fight--; else break; break;
			case DOWN:if (activate_str_of_menu_fight < 5) activate_str_of_menu_fight++; else break; break;
			case ENTER:
				switch (activate_str_of_menu_fight){
				case 1:Random_player(1, &player); menu_true_false = false; break;//����� ���� ����� ������� �������
				case 2:Random_player(2, &player); menu_true_false = false; break;//������ ���� ����� ������� �������
				case 3:Random_player(3, &player); menu_true_false = false; break;//���� ����� ����� ������� �������
				case 4:Random_player(4, &player); menu_true_false = false; break;//���� ����� ������� �������
				case 5: SetColor(15, 0);
					cout << "������� ���-���: ";

					cheat = ChekOnInt(y_0);

					if (cheat == 8666) {
						cout << "�� ������������!" << endl;
						y_0++;
						player.hp = 20;
					}
					else if (cheat == 22022022) {
						cout << "����� ������� �� 10 ������!" << endl;
						y_0++;
						player.damage_cheat = 10;
					}
					else if (cheat == 2404) {
						cout << "Godmod" << endl;
						y_0++;
						player.hp = 9999999;
					}
					else if (cheat == 2401) {
						cout << "�� ����� �������������!" << endl;
						y_0++;
						enemy.hp = 20;
					}
					else {
						y_0++;
						cout << "�������� ��� ���!" << endl;
					}
					y_0 += 8;
					
					break;
				default:break;
				}
			default:break;
			}
		}
		system("CLS");
		Random_enemy(&enemy); //����� ������� �������
		SetColor(10, 0);
		if (player.damage > 0) { //��� �������� �������� ����� ������
			if (enemy.damage >= 0) {
				if (player.damage == 1 && player.critical == false) {
					cout << player.name << " ������� ���� �� " << enemy.name << " ����� ����� �� " << player.damage + player.damage_cheat << " ��.�����" << endl;
					enemy.hp -= player.damage + player.damage_cheat;
				}
				if (player.damage == 2 && player.critical == false) {
					cout << player.name << " ������� ���� �� " << enemy.name << " ������ ����� �� " << player.damage + player.damage_cheat << " ��.�����" << endl;
					enemy.hp -= player.damage + player.damage_cheat;
				}
				if (player.damage == 3 && player.critical == false) {
					cout << player.name << " ������� ���� �� " << enemy.name << "  ����� �� " << player.damage + player.damage_cheat << " ��.�����" << endl;
					enemy.hp -= player.damage + player.damage_cheat;
				}
				if (player.damage == 2 && player.critical == true) {
					cout << player.name << " ������� ����������� ���� �� " << enemy.name << " ����� ����� �� " << player.damage + player.damage_cheat << " ��.�����" << endl;
					enemy.hp -= player.damage + player.damage_cheat;
				}
				if (player.damage == 3 && player.critical == true) {
					cout << player.name << " ������� ����������� ���� �� " << enemy.name << " ������ ����� �� " << player.damage + player.damage_cheat << " ��.�����" << endl;
					enemy.hp -= player.damage + player.damage_cheat;
				}
				if (player.damage == 4 && player.critical == true) {
					cout << player.name << " ������� ����������� ���� �� " << enemy.name << "  ����� �� " << player.damage + player.damage_cheat << " ��.�����" << endl;
					enemy.hp -= player.damage + player.damage_cheat;
				}
			}
			if (enemy.damage == -1) {
				if (player.critical == false) {
					cout << player.name << " �� ������ ���� " << enemy.name << endl;
				}
				else {
					if (player.damage == 2) {
						cout << player.name << " ��������� ���� � ������� ���� �� " << enemy.name << " ����� ����� �� " << player.damage + player.damage_cheat - 1 << " ��.�����" << endl;
						enemy.hp -= player.damage + player.damage_cheat - 1;
					}
					if (player.damage == 3) {
						cout << player.name << " ��������� ���� � ������� ���� �� " << enemy.name << " ������ ����� �� " << player.damage + player.damage_cheat - 1 << " ��.�����" << endl;
						enemy.hp -= player.damage + player.damage_cheat - 1;
					}
					if (player.damage == 4) {
						cout << player.name << " ��������� ���� � ������� ���� �� " << enemy.name << "  ����� �� " << player.damage + player.damage_cheat - 1 << " ��.�����" << endl;
						enemy.hp -= player.damage + player.damage_cheat - 1;
					}
				}
			}
		}
		if (player.damage == 0) {
			cout << player.name << " ����������� �� " << enemy.name << endl;
		}
		if (player.damage < 0) {
			cout << player.name << " ������ ����!" << endl;
		}

		SetColor(12, 0);
		if (enemy.damage > 0) {//��� �������� �������� ����� �����
			if (player.damage >= 0) {
				if (enemy.damage == 1 && enemy.critical == false) {
					cout << enemy.name << " ������� ���� �� " << player.name << " ����� ����� �� " << enemy.damage + enemy.damage_cheat << " ��.�����" << endl;
					player.hp -= enemy.damage + enemy.damage_cheat;
				}
				if (enemy.damage == 2 && enemy.critical == false) {
					cout << enemy.name << " ������� ���� �� " << player.name << " ������ ����� �� " << enemy.damage + enemy.damage_cheat << " ��.�����" << endl;
					player.hp -= enemy.damage + enemy.damage_cheat;
				}
				if (enemy.damage == 3 && enemy.critical == false) {
					cout << enemy.name << " ������� ���� �� " << player.name << "  ����� �� " << enemy.damage + enemy.damage_cheat << " ��.�����" << endl;
					player.hp -= enemy.damage + enemy.damage_cheat;
				}
				if (enemy.damage == 2 && enemy.critical == true) {
					cout << enemy.name << " ������� ����������� ���� �� " << player.name << " ����� ����� �� " << enemy.damage + enemy.damage_cheat << " ��.�����" << endl;
					player.hp -= enemy.damage + enemy.damage_cheat;
				}
				if (enemy.damage == 3 && enemy.critical == true) {
					cout << enemy.name << " ������� ����������� ���� �� " << player.name << " ������ ����� �� " << enemy.damage + enemy.damage_cheat << " ��.�����" << endl;
					player.hp -= enemy.damage + enemy.damage_cheat;
				}
				if (enemy.damage == 4 && enemy.critical == true) {
					cout << enemy.name << " ������� ����������� ���� �� " << player.name << "  ����� �� " << enemy.damage + enemy.damage_cheat << " ��.�����" << endl;
					player.hp -= enemy.damage + enemy.damage_cheat;
				}
			}
			if (player.damage == -1) {
				if (enemy.critical == false) {
					cout << enemy.name << " �� ������ ���� " << player.name << endl;
				}
				else {
					if (enemy.damage == 2) {
						cout << enemy.name << " ��������� ���� � ������� ���� �� " << player.name << " ����� ����� �� " << enemy.damage + enemy.damage_cheat - 1 << " ��.�����" << endl;
						player.hp -= enemy.damage + enemy.damage_cheat - 1;
					}
					if (enemy.damage == 3) {
						cout << enemy.name << " ��������� ���� � ������� ���� �� " << player.name << " ������ ����� �� " << enemy.damage + enemy.damage_cheat - 1 << " ��.�����" << endl;
						player.hp -= enemy.damage + enemy.damage_cheat - 1;
					}
					if (enemy.damage == 4) {
						cout << enemy.name << " ��������� ���� � ������� ���� �� " << player.name << "  ����� �� " << enemy.damage + enemy.damage_cheat - 1 << " ��.�����" << endl;
						player.hp -= enemy.damage + enemy.damage_cheat - 1;
					}
				}
			}
		}
		if (enemy.damage == 0) {
			cout << enemy.name << " ����������� �� " << player.name << endl;
		}
		if (enemy.damage < 0) {
			cout << enemy.name << " ������ ����!" << endl;
		}
		if (player.hp <= 0 && enemy.hp > 0) {
			SetColor(15, 0);
			cout << "�������� " << player.name.c_str() << ": ";
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
			cout << "\n�������� " << enemy.name.c_str() << ": ";
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
			cout << "\n���������!" << endl;
			Lose(); //��������������
		}
		if (player.hp > 0 && enemy.hp <= 0) {
			SetColor(15, 0);
			cout << "�������� " << player.name.c_str() << ": ";
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
			cout << "\n�������� " << enemy.name.c_str() << ": ";
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
			cout << "\n������!";
			Win(); //��������������
		}
		if (player.hp <= 0 && enemy.hp <= 0) {
			SetColor(15, 0);
			cout << "�������� " << player.name.c_str() << ": ";
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
			cout << "\n�������� " << enemy.name.c_str() << ": ";
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
			cout << "\n�����!";
			Draw(); //��������������
		}
	} while (player.hp > 0 && enemy.hp > 0);
	SetColor(15, 0);
	cout << "��� ����������� ������� ����� �������...";
	_getch();
	system("CLS");
	menu_start(); //����� ������� ����
}