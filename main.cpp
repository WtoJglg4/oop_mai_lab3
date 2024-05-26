/********************************************************************
 *          ������������ ������ �1 �� ��� 4 �������                 *
 *------------------------------------------------------------------*
 * Project Type  : Win64 Console Application                        *
 * Project Name  : tower	                                        *
 * File Name     : main.cpp		                                    *
 * Programmer(s) : ������ ����� �3�-209�-22                         *
 * Modifyed By   :                                                  *
 * Created       : 13/04/2024                                       *
 * Last Revision : 14/04/2024                                       *
 * Comment(s)    : ���������� �������� �������						*
 *******************************************************************/
#include <windows.h>
#include <iostream>    
using namespace std;

#include "tower.h" 
#include "tower.cpp" 

//������ ��� ����������� ���� ������� �������
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
ABC_Object* objects[ARR_SIZE];

HDC hdc;										// ������� �������� ����������
HWND GetConcolWindow() {
	char str[128];
	char title[128]="xxxxxxxxxxxxxxxxxx";
	// string title = "xxxxxxxxxxxxxxxxxx";		//����� ������ Windows
	GetConsoleTitle(str, sizeof((LPWSTR)str)); 	// �������� ��������� ����
	SetConsoleTitle(LPCSTR(title));				// ���������� ����� ��������� ����
	Sleep(100);									// ���� ����� ��������� ���� (100 ��);

	HWND hwnd = FindWindow(NULL, LPCSTR(title));// ���������� ���������� ����
	SetConsoleTitle(str);						//���������� ������� ���������

	return hwnd;								//������� ���������� ����
}

//������� �������� (�� ������� ����������� �������, �� �������� �����)
// 0 - tower
// 1 - broken tower
// 2 - blue tower
// 3 - square tower
int TransMatrix[ARR_SIZE][ARR_SIZE] = {
	{3, 0, 1, 3},
	{0, 1, 2, 0},
	{1, 1, 2, 2},
	{2, 2, 3, 3}
};


// g++ main.cpp -o main.exe -lgdi32
int main() {
	setlocale(LC_ALL, "ru");
	system("color F0");
	HWND hwnd = GetConcolWindow(); 	//��������� �� ���������� ����

	if (hwnd != NULL) { 			//���� ���������� ����������

		hdc = GetWindowDC(hwnd); 	//������� �������� ���������� ��� ����������� ����

		if (hdc != NULL) {	
			//��������� ����������
			Point Start(400, 700);
			int ObjectWidht = 300, ObjectHigh = 300;
			int BaseLength = 120, ObservationRadius = 50, TotalHigh = 500;
			int DefaultStep = 5;


			Tower tower(Start.GetX(), Start.GetY(), BaseLength, ObservationRadius, TotalHigh);
			BrokenTower brokenTower(Start.GetX(), Start.GetY(), BaseLength, ObservationRadius, TotalHigh);
			PaintedTower paintedTower(Start.GetX(), Start.GetY(), BaseLength, ObservationRadius, TotalHigh);
			SqareTower sqareTower(Start.GetX(), Start.GetY(), BaseLength, ObservationRadius, TotalHigh);

			Tower* currentTower = &tower;

			Tower* towers[ARR_SIZE] = {&tower, &brokenTower, &paintedTower, &sqareTower}; //������ �����

			//�������, � �������� ������������
			Stone stone(200, 200, 50);
			Stop stop(100, 700, 60, 100);
			Pond pond(900, 700, 250);
			Tree tree(1200, 400, 300);

			objects[0] = &stone;
			objects[1] = &stop;
			objects[2] = &pond;
			objects[3] = &tree;
			for(int i = 0; i < ARR_SIZE; i++) objects[i]->Show();

			currentTower->Show(); 

			while (true) {
				currentTower->Drag(DefaultStep);

				for (int i = 0; i < ARR_SIZE; i++)
				{
					if (Collision(*currentTower, *objects[i]))
					{
						currentTower->MoveTo(Start.GetX(), Start.GetY());	// ������� � ��������� �����  
						currentTower->Hide();
						currentTower = towers[TransMatrix[objects[i]->GetIndex()][currentTower->GetIndex()]]; //������� � ������ �������
						currentTower->Show();
						for (int i = 0; i < ARR_SIZE; i++) objects[i]->Show();
						break;
					}
				}
			}
		}
	}
	ReleaseDC(GetConsoleWindow(), hdc);
}


