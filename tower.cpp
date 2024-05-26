/********************************************************************
 *          ЛАБОРАТОРНАЯ РАБОТА №1 ПО ООП 4 СЕМЕСТР                 *
 *------------------------------------------------------------------*
 * Project Type  : Win64 Console Application                        *
 * Project Name  : tower	                                        *
 * File Name     : tower.cpp                                        *
 * Programmer(s) : Глазов Вадим Викторович М3О-209Б-22			    *
 * Modifyed By   :                                                  *
 * Created       : 10/04/2024                                       *
 * Last Revision : 16/04/2024                                       *
 * Comment(s)    : ПРОСТЕЙШАЯ ИЕРАРХИЯ КЛАССОВ						*
 *******************************************************************/

#include <windows.h>
#include <iostream>  
#include "tower.h"			//объявление классов
using namespace std;        // Пространство имен std

extern HDC hdc;     		// объявление  контекста устройства
extern ABC_Object* objects[ARR_SIZE];
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

const int timeToSleep = 5; 	// время для задержки экрана в мс

/*----------------------------------------------------------------*/
/*             		ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ		                  */
/*----------------------------------------------------------------*/

void FillCirlce(HDC hdc, int x, int y, int radius){
	for (int i = radius; i > 0; i--){
		Ellipse(hdc, x - i, y - i, x + i, y + i);
	}
}

void FillSquare(HDC hdc, int x, int y, int radius){
	for (int i = radius; i > 0; i--){
		Rectangle(hdc, x - i, y - i, x + i, y + i);
	}
}

/*----------------------------------------------------------------*/
/*             Р Е А Л И З А Ц И Я    М Е Т О Д О В               */
/*----------------------------------------------------------------*/

/*----------------------------------------*/
/*        МЕТОДЫ КЛАССА Location          */
/*----------------------------------------*/
Location:: Location(int InitX, int InitY) {
	x = InitX;
	y = InitY;
};

Location:: ~Location() {
};

int Location:: GetX() {
	return x;
};

int Location:: GetY() {
	return y;
};

/*----------------------------------------*/
/*        МЕТОДЫ КЛАССА Point             */
/*----------------------------------------*/

Point:: Point(int InitX, int InitY) : Location(InitX, InitY) {
	visible = false;
}

Point:: ~Point(){
}

void Point:: Show() {
	visible = true;
	SetPixel(hdc, x+1, y, RGB(255, 0, 0));//рисуем синим цветом или фона
	SetPixel(hdc, x-1, y, RGB(255, 0, 0));//рисуем синим цветом или фона
	SetPixel(hdc, x, y+1, RGB(255, 0, 0));//рисуем синим цветом или фона
	SetPixel(hdc, x, y-1, RGB(255, 0, 0));//рисуем синим цветом или фона
	SetPixel(hdc, x-1, y-1, RGB(255, 0, 0));//рисуем синим цветом или фона
	SetPixel(hdc, x-1, y+1, RGB(255, 0, 0));//рисуем синим цветом или фона
	SetPixel(hdc, x+1, y-1, RGB(255, 0, 0));//рисуем синим цветом или фона
	SetPixel(hdc, x+1, y+1, RGB(255, 0, 0));//рисуем синим цветом или фона
	SetPixel(hdc, x, y, RGB(255, 0, 0));//рисуем синим цветом или фона
}

void Point:: Hide() {
	visible = false;

	SetPixel(hdc, x+1, y, RGB(255, 255, 255));//рисуем синим цветом или фона
	SetPixel(hdc, x-1, y,RGB(255, 255, 255));//рисуем синим цветом или фона
	SetPixel(hdc, x, y+1, RGB(255, 255, 255));//рисуем синим цветом или фона
	SetPixel(hdc, x, y-1, RGB(255, 255, 255));//рисуем синим цветом или фона
	SetPixel(hdc, x-1, y-1, RGB(255, 255, 255));//рисуем синим цветом или фона
	SetPixel(hdc, x-1, y+1, RGB(255, 255, 255));//рисуем синим цветом или фона
	SetPixel(hdc, x+1, y-1, RGB(255, 255, 255));//рисуем синим цветом или фона
	SetPixel(hdc, x+1, y+1, RGB(255, 255, 255));//рисуем синим цветом или фона
	SetPixel(hdc, x, y, RGB(255, 255, 255));//рисуем синим цветом или фона

}

bool Point:: IsVisible() {
	return visible;
};

void Point:: MoveTo(int NewX, int NewY) {
	Hide();		//скрыть точку
	x = NewX;
	y = NewY;
	Show();		//показать точку
};

void Point:: Drag(int Step) {
	//получение координат точки
	int figX = GetX();
	int figY = GetY();

	//бесконечный цикл
	while (true) {
		if (KEY_DOWN(VK_ESCAPE)) break;	//esc - выход

		//перемещение фигуры в зависимости от нажатой стрелки
		if (KEY_DOWN(VK_LEFT)) figX -= Step;

		if (KEY_DOWN(VK_RIGHT)) figX += Step;

		if (KEY_DOWN(VK_UP)) figY -= Step;

		if (KEY_DOWN(VK_DOWN)) figY += Step;

		MoveTo(figX, figY);
		Sleep(timeToSleep);
	}
}

/*----------------------------------------*/
/*        МЕТОДЫ КЛАССА ABC_Object        */
/*----------------------------------------*/

//формальный конструктор по умолчанию для создания массива
ABC_Object:: ABC_Object(): Point(0, 0) {	
}

//фактический конструктор
ABC_Object:: ABC_Object(int InitX, int InitY): Point(InitX, InitY) {
}

ABC_Object:: ~ABC_Object() {
}

int ABC_Object:: GetRightSideHB() {
	return rightSideHB;
}

int ABC_Object:: GetDownSideHB() {
	return downSideHB;
}

int ABC_Object:: GetLeftSideHB() {
	return leftSideHB;
}

int ABC_Object:: GetUpSideHB() {
	return upSideHB;
}

int ABC_Object:: GetIndex() {
	return index;
}

//опредление столкновения с каким-либо объектом
// bool ABC_Object::Collision(Tower& tower) {
//     // Получаем координаты хитбокса текущего объекта
//     int leftA = this->leftSideHB;
//     int rightA = this->rightSideHB;
//     int topA = this->upSideHB;
//     int bottomA = this->downSideHB;

//     // Получаем координаты хитбокса другого объекта (башни)
//     int leftB = tower.GetLeftSideHB();
//     int rightB = tower.GetRightSideHB();
//     int topB = tower.GetUpSideHB();
//     int bottomB = tower.GetDownSideHB();

//     // Проверяем, перекрываются ли хитбоксы
//     bool horizontalOverlap = (leftA <= rightB) && (rightA >= leftB);
//     bool verticalOverlap = (topA <= bottomB) && (bottomA >= topB);

//     // Если есть перекрытие по обоим осям, значит прямоугольники сталкиваются
//     return horizontalOverlap && verticalOverlap;
// }


void ABC_Object:: Hide(){
	HPEN white = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	Draw(white, NULL);
}

void ABC_Object:: Show(){
	HPEN black = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	Draw(black, NULL);
}

void ABC_Object:: Draw(HPEN pen1, HPEN pen2){
	
}


/*----------------------------------------*/
/*        МЕТОДЫ КЛАССА Tower             */
/*----------------------------------------*/

Tower:: Tower(int InitX, int InitY, int InitBaseLength, int InitObservationRadius, int InitTotalHigh) : ABC_Object(InitX, InitY) {
	BaseLength = InitBaseLength;
	ObservationRadius = InitObservationRadius;
	TotalHigh = InitTotalHigh;
	ObservationHigh = TotalHigh * 7 / 10;

	rightSideHB = x + BaseLength / 2;
	downSideHB = y + BaseLength / 8;
	leftSideHB = x - BaseLength / 2;	
	upSideHB = y - TotalHigh;
	index = 0;
}

Tower:: ~Tower() {
}

void Tower:: MoveTo(int NewX, int NewY) {
	Hide();		//скрыть точку
	x = NewX;
	y = NewY;
	rightSideHB = x + BaseLength / 2;
	downSideHB = y + BaseLength / 8;
	leftSideHB = x - BaseLength / 2;	
	upSideHB = y - TotalHigh;
	Show();		//показать точку
};

//общая отрисовка
void Tower:: Draw(HPEN pen1, HPEN pen2){
	SelectObject(hdc, pen1);
	
	Base(pen1);
	Observation(pen1, NULL);
	Body(pen1);
	Spire(pen1);
}

//фундамент
void Tower:: Base(HPEN pen){
	Rectangle(hdc, x - BaseLength / 2 , y - BaseLength / 8, x + BaseLength / 2 , y + BaseLength / 8);
}	

//смотровая площадка
void Tower:: Observation(HPEN pen1, HPEN pen2){
	Ellipse(hdc, x - ObservationRadius, y - ObservationHigh - ObservationRadius, x + ObservationRadius, y - ObservationHigh + ObservationRadius);
	Rectangle(hdc, x - ObservationRadius / 2 , y - ObservationHigh + ObservationRadius, x + ObservationRadius / 2 , y - ObservationHigh + 3 * ObservationRadius / 2);
	Rectangle(hdc, x - ObservationRadius / 4 , y - ObservationHigh - 5 * ObservationRadius / 3, x + ObservationRadius / 4 , y - ObservationHigh - ObservationRadius);
}	

//тело башни
void Tower:: Body(HPEN pen){
	// MoveToEx(hdc, x - BaseLength / 4, y - BaseLength / 8, NULL);
	// LineTo(hdc, x - ObservationRadius / 4, y - ObservationHigh + 3 * ObservationRadius / 2);

	MoveToEx(hdc, x - BaseLength / 4, y - BaseLength / 8, NULL);
	LineTo(hdc, x - ObservationRadius / 4, y - ObservationHigh + 3 * ObservationRadius / 2);

	MoveToEx(hdc, x + BaseLength / 4, y - BaseLength / 8, NULL);
	LineTo(hdc, x + ObservationRadius / 4, y - ObservationHigh + 3 * ObservationRadius / 2);
}	

//шпиль
void Tower:: Spire(HPEN pen){
	MoveToEx(hdc,  x - ObservationRadius / 8, y - ObservationHigh - 5 * ObservationRadius / 3, NULL);
	LineTo(hdc, x , y - TotalHigh);
	LineTo(hdc, x + ObservationRadius / 8, y - ObservationHigh - 5 * ObservationRadius / 3);
}	

void Tower:: DrawHitbox(HPEN pen){
	SelectObject(hdc, pen);

	MoveToEx(hdc, leftSideHB, upSideHB, NULL);
	LineTo(hdc, rightSideHB , upSideHB);
	LineTo(hdc, rightSideHB , downSideHB);
	LineTo(hdc, leftSideHB , downSideHB);
	LineTo(hdc, leftSideHB , upSideHB);
}

void Tower::  Show() {
	visible = true;
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	Draw(pen, NULL);
	DeleteObject(pen);

	//отрисовка хитбокса
	// HPEN gray = CreatePen(PS_SOLID, 2, RGB(128, 128, 128));	//серый
	// DrawHitbox(gray);
	// DeleteObject(gray);
}

void Tower:: Hide() {
	visible = false;
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	Draw(pen, NULL);
	// DrawHitbox(pen);
	DeleteObject(pen);
}

void Tower:: Drag(int Step) {
	//получение координат точки
	int figX = GetX();
	int figY = GetY();

	//бесконечный цикл
	while (true) {
		if (KEY_DOWN(VK_ESCAPE)) break;	//esc

		if (KEY_DOWN(VK_LEFT)) {	
			figX -= Step;
			leftSideHB -= Step;
			rightSideHB -= Step;
		}

		if (KEY_DOWN(VK_RIGHT)) { 
			figX += Step;
			rightSideHB += Step;
			leftSideHB += Step;
		}

		if (KEY_DOWN(VK_DOWN)) {
			figY += Step;
			downSideHB += Step;
			upSideHB += Step;
		}

		if (KEY_DOWN(VK_UP)) { //38 стрелка вверх		
			figY -= Step;
			downSideHB -= Step;
			upSideHB -= Step;
		}

		for(int i = 0; i < ARR_SIZE; i++){
			if (Collision(*this, *objects[i])){
				return;
			}
		}
		
		MoveTo(figX, figY);
		Sleep(timeToSleep);
	}
}

int Tower:: GetRightSideHB(){
	return rightSideHB;
}

int Tower:: GetDownSideHB(){
	return downSideHB;
}

int Tower:: GetLeftSideHB(){
	return leftSideHB;
}

int Tower:: GetUpSideHB(){
	return upSideHB;
}

int Tower:: GetIndex(){
	return index;
}

/*----------------------------------------*/
/*        МЕТОДЫ КЛАССА BrokenTower       */
/*----------------------------------------*/

BrokenTower:: BrokenTower(int InitX, int InitY, int BaseLength, int ObservationRadius, int TotalHigh): Tower(InitX, InitY, BaseLength, ObservationRadius, TotalHigh){
	index = 1;
}

BrokenTower:: ~BrokenTower(){

}

//шпиль
void BrokenTower:: Spire(HPEN pen){
	MoveToEx(hdc,  x + ObservationRadius / 8, y - ObservationHigh - 5 * ObservationRadius / 3, NULL);
	LineTo(hdc, x +  BaseLength, y - ObservationHigh - 5 * ObservationRadius / 3);
	LineTo(hdc, x + ObservationRadius / 8, y - ObservationHigh - 2 * ObservationRadius);
	LineTo(hdc, x + ObservationRadius / 8, y - ObservationHigh - 5 * ObservationRadius / 3);
}	

/*----------------------------------------*/
/*        МЕТОДЫ КЛАССА PaintedTower      */
/*----------------------------------------*/

PaintedTower:: PaintedTower(int InitX, int InitY, int BaseLength, int ObservationRadius, int TotalHigh): Tower(InitX, InitY, BaseLength, ObservationRadius, TotalHigh){
	index = 2;
}

PaintedTower:: ~PaintedTower(){

}

void PaintedTower::  Show() {
	visible = true;
	HPEN red = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	HPEN blue = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
	Draw(red, blue);
	DeleteObject(red);
	DeleteObject(blue);

	// HPEN gray = CreatePen(PS_SOLID, 2, RGB(128, 128, 128));	//серый
	// DrawHitbox(gray);
	// DeleteObject(gray);
}

void PaintedTower:: Hide() {
	visible = false;
	HPEN white = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	Draw(white, white);
	// DrawHitbox(white);
	DeleteObject(white);
}
		
void PaintedTower:: Draw(HPEN red, HPEN blue){
	SelectObject(hdc, red);

	Base(red);									//фундамент
	Observation(red, blue);	//смотровая площадка
	Body(red);					//тело
	Spire(red);				//шпиль
}

void PaintedTower::  Observation(HPEN red, HPEN blue) {
	SelectObject(hdc, blue);
	FillCirlce(hdc, x, y - ObservationHigh, ObservationRadius);
	SelectObject(hdc, red);
	Rectangle(hdc, x - ObservationRadius / 2 , y - ObservationHigh + ObservationRadius, x + ObservationRadius / 2 , y - ObservationHigh + 3 * ObservationRadius / 2);
	Rectangle(hdc, x - ObservationRadius / 4 , y - ObservationHigh - 5 * ObservationRadius / 3, x + ObservationRadius / 4 , y - ObservationHigh - ObservationRadius);
}


/*----------------------------------------*/
/*        МЕТОДЫ КЛАССА SqareTower        */
/*----------------------------------------*/

SqareTower:: SqareTower(int InitX, int InitY, int BaseLength, int ObservationRadius, int TotalHigh): Tower(InitX, InitY, BaseLength, ObservationRadius, TotalHigh){
	index = 3;
}

SqareTower:: ~SqareTower(){

}

void SqareTower::  Show() {
	visible = true;
	HPEN red = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	HPEN black = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	Draw(red, black);
	DeleteObject(red);
	DeleteObject(black);
}

void SqareTower:: Hide() {
	visible = false;
	HPEN white = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	Draw(white, white);
	// DrawHitbox(white);
	DeleteObject(white);
}
		
void SqareTower:: Draw(HPEN pen1, HPEN pen2){
	SelectObject(hdc, pen1);

	Base(pen1);									//фундамент
	Observation(pen1, pen2);	//смотровая площадка
	Body(pen1);					//тело
	Spire(pen1);				//шпиль
}

void SqareTower::  Observation(HPEN pen1, HPEN pen2) {
	SelectObject(hdc, pen2);
	FillSquare(hdc, x, y - ObservationHigh, ObservationRadius);
	SelectObject(hdc, pen1);
	
	//подставки
	Rectangle(hdc, x - ObservationRadius / 2 , y - ObservationHigh + ObservationRadius, x + ObservationRadius / 2 , y - ObservationHigh + 3 * ObservationRadius / 2);
	Rectangle(hdc, x - ObservationRadius / 4 , y - ObservationHigh - 5 * ObservationRadius / 3, x + ObservationRadius / 4 , y - ObservationHigh - ObservationRadius);
}

/*----------------------------------------*/
/*        МЕТОДЫ КЛАССА Stone             */
/*----------------------------------------*/

Stone:: Stone(int InitX, int InitY, int r) : ABC_Object(InitX, InitY) {
	radius = r;
	index = 0;

	//расчет крайних координат
	rightSideHB = x + radius;
	downSideHB = y + radius;
	leftSideHB = x - radius;
	upSideHB = y - radius;
}

Stone:: ~Stone() {

}

void Stone:: Draw(HPEN pen1, HPEN pen2){
	SelectObject(hdc, pen1);
	Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);
	DeleteObject(pen1);
}

/*----------------------------------------*/
/*        МЕТОДЫ КЛАССА Stop             */
/*----------------------------------------*/
Stop:: Stop(int InitX, int InitY, int r, int s) : ABC_Object(InitX, InitY) {
	radius = r;
	index = 1;
	stick = s;

	//расчет крайних координат
	rightSideHB = x + radius;
	downSideHB = y;
	leftSideHB = x - radius;
	upSideHB = y - stick - 2 * radius;
}

Stop:: ~Stop() {
	 
}

void Stop:: Draw(HPEN pen1, HPEN pen2){
	SelectObject(hdc, pen1);	//сделаем перо активным
	MoveToEx(hdc, x, y, NULL);
	LineTo(hdc, x, y - stick);
	MoveToEx(hdc, x, y - radius - stick, NULL);
	Ellipse(hdc, x - radius, y - 2 * radius - stick, x + radius, y - stick); //знак
	Rectangle(hdc, x - 0.5 * radius, y - 1.25 * radius - stick, x + 0.5 * radius, y - 0.75 * radius - stick); //прямоугольник на знаке
	DeleteObject(pen1);
}

/*----------------------------------------*/
/*        МЕТОДЫ КЛАССА Pond              */
/*----------------------------------------*/
Pond:: Pond(int InitX, int InitY, int r) : ABC_Object(InitX, InitY) {
	radius = r;
	index = 2;

	//расчет крайних координат, radius = 10
	rightSideHB = InitX + radius;
	downSideHB = InitY + radius / 4;
	leftSideHB = InitX - radius;
	upSideHB = InitY - radius / 4;
}

Pond:: ~Pond() {

}

void Pond:: Show(){
	HPEN black = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
	Draw(black, NULL);
}

void Pond:: Draw(HPEN pen1, HPEN pen2){
	SelectObject(hdc, pen1);	//сделаем перо активным
	for (int i = radius; i > 0; i--){
		Ellipse(hdc, x - i, y - i/4, x + i, y + i/4); //лужа
	}
	DeleteObject(pen1);
}

/*----------------------------------------*/
/*        МЕТОДЫ КЛАССА Tree              */
/*----------------------------------------*/
Tree:: Tree(int InitX, int InitY, int high) : ABC_Object(InitX, InitY) {
	High = high;
	index = 3;

	//расчет крайних координат
	rightSideHB = x + high / 4;
	downSideHB = y;
	leftSideHB = x - high / 4;
	upSideHB = y - high;
}

Tree:: ~Tree() {

}

void Tree:: Draw(HPEN pen1, HPEN pen2){
	SelectObject(hdc, pen1);	//сделаем перо активным

	MoveToEx(hdc, x, y, NULL);
	LineTo(hdc, x, y - High / 4);
	LineTo(hdc, x - High / 4, y - High / 4);
	LineTo(hdc, x, y - High / 2);
	LineTo(hdc, x + High / 4, y - High / 4);
	LineTo(hdc, x, y - High / 4);

	MoveToEx(hdc, x, y - 3 * High / 4, NULL);
	LineTo(hdc, x - High / 5, y - High / 2);
	LineTo(hdc, x + High / 5, y - High / 2);
	LineTo(hdc, x, y - 3 * High / 4);

	MoveToEx(hdc, x, y - High, NULL);
	LineTo(hdc, x - High / 6, y - 3 * High / 4);
	LineTo(hdc, x + High / 6, y - 3 * High / 4);
	LineTo(hdc, x, y - High);

	DeleteObject(pen1);
}

bool Collision(ABC_Object& objA, ABC_Object& objB)
{
	// Получаем координаты хитбокса текущего объекта
    int leftA = objA.GetLeftSideHB();
    int rightA = objA.GetRightSideHB();
    int topA = objA.GetUpSideHB();
    int bottomA = objA.GetDownSideHB();

    // Получаем координаты хитбокса другого объекта (башни)
    int leftB = objB.GetLeftSideHB();
    int rightB = objB.GetRightSideHB();
    int topB = objB.GetUpSideHB();
    int bottomB = objB.GetDownSideHB();

    // Проверяем, перекрываются ли хитбоксы
    bool horizontalOverlap = (leftA <= rightB) && (rightA >= leftB);
    bool verticalOverlap = (topA <= bottomB) && (bottomA >= topB);

    // Если есть перекрытие по обоим осям, значит прямоугольники сталкиваются
    return horizontalOverlap && verticalOverlap;
}
