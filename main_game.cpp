#include <iostream>
#include <locale>
#include <random>
#include <Windows.h>
#include "Header.h"

using namespace std;

int main() {
	srand(time(0));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	SetConsoleTitle(L"Fighter");
	setlocale(LC_ALL, "RU");
	menu_start();
	return 0;
}