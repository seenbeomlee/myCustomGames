#pragma once

#include<iostream>
#include<Windows.h>
#include<conio.h>
#include "Enum.h"
#include "Object.h"
#include "Map.h"


using namespace std;

Direction KeyInput()
{
	int key;
	key = _getwch();
	switch (key)
	{
	case 'w':
		return UP;
	case 'a':
		return LEFT;
	case 'd':
		return RIGHT;
	case 's':
		return DOWN;
	case 'r':
		return RESTART;
	case 'e':
		return EXIT;
	}
}

int main()
{
	string filename;

	while (true) {
		cout << "Read Stage File: ";
		cin >> filename;
		if (!Map::ReadMap(filename)) continue; //파일을 못 읽었으면 다시 입력하게 한다.
		Map::PrintMap();
		cout << filename << " Load Complete. Press Any Key to Continue..." << endl;
		KeyInput();
		while (true) {
			Map::CheckRules(); //문장에 따라 속성을 부여한다.
			Map::ChangeEntity(); //부여된 속성을 적용
			Map::LoseCheck(); //Lose 속성을 가진 개체에 닿은 YOU를 파괴
			Map::PrintMap();
			Map::PrintRules();
			if (Map::CantMoveCheck()) { //YOU 개체가 없을 시 패배
				cout << "YOU does not exist. You Lose" << endl;
				break;
			}
			if (Map::WinCheck()) { //승리 조건 만족시 승리
				cout << "YOU WIN!" << endl;
				break;
			}
			cout << "Key Input: w=up, s=down, a=left, d=right, r=restart, e=exit" << endl;
			Direction dir = KeyInput(); //키 입력을 받는다.
			if (dir == RESTART) {
				Map::ReadMap(filename);
			}
			if (dir == EXIT) {
				system("cls");
				break;
			}
			Map::YouMove(dir);
		}
		Map::Remove_all; //동적할당 받은 object들을 해제한다
	}

	return 0;
}