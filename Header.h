#pragma once
using namespace std;

int Random_enemy(struct model);
int Random_player(int, struct model);
int menu_start();
int ChekOnInt();
void Game_logic();

void SetColor(int, int);
void MoveCord_X_Y(short, short);
void CursorVisible(bool, short);
struct model
{
	string name;
	int hp, damage, damage_cheat;
	bool critical;
};