#pragma once
/********************************************************************
 *          ЛАБОРАТОРНАЯ РАБОТА №1 ПО ООП 4 СЕМЕСТР                 *
 *------------------------------------------------------------------*
 * Project Type  : Win64 Console Application                        *
 * Project Name  : Laba_OOP_1                                       *
 * File Name     : tower.h                                          *
 * Programmer(s) : Глазов Вадим М3О-209Б-22           				*
 * Modifyed By   :                                                  *
 * Created       : 14/04/2023                                       *
 * Last Revision : 14/04/2023                                       *
 * Comment(s)    : ПРОСТЕЙШАЯ ИЕРАРХИЯ КЛАССОВ						*
 *******************************************************************/

/*-----------------------------------------------------------------------*/
/*                         Т И П Ы    Д А Н Н Ы Х                        */
/*-----------------------------------------------------------------------*/

#define ARR_SIZE 4 //размер массива конфликтных объектов

/*-----------------------------------------------------------------------*/
/*                         Т И П Ы    Д А Н Н Ы Х                        */
/*-----------------------------------------------------------------------*/

/*-----------------------  Класс Location -------------------------*/
class Location {
	protected:		
		int x;							//координата X
		int y;							//координата Y

	public:
		Location(int InitX, int InitY); //конструктор
		~Location();                    //деструктор
		int GetX();						//получить X координату точки
		int GetY();						//получить Y координату точки
};

/*-----------------------  Класс Point ----------------------------------*/
class Point : public Location{
	protected:							
		bool visible;								//видимость точки

	public:
		Point(int InitX, int InitY);				//конструктор
		~Point();									//деструктор

		bool IsVisible();							//является видимой
		virtual void MoveTo(int NewX, int NewY);	//переместить
		
		virtual void Drag(int Step); 				//буксировка
		virtual void Show();						//показать 
		virtual void Hide();						//скрыть
};

/*-----------------------  Абстрактный базовый класс ABC_Object ---------------------------*/
class ABC_Object: public Point {
	protected:
		int rightSideHB;	//правая граница хитбокса
		int downSideHB;		//нижняя граница хитбокса
		int leftSideHB;		//левая граница хитбокса
		int upSideHB;		//верхняя граница хитбокса
		int index;			//индекс объекта
			
	public:
		ABC_Object(int InitX, int InitY);
		ABC_Object();									//формальный конструктор
		~ABC_Object();
		
		//геттеры
		int GetRightSideHB();
		int GetDownSideHB();
		int GetLeftSideHB();
		int GetUpSideHB();
		int GetIndex();									

		virtual void Show();							//показать 
		virtual void Hide();							//скрыть
		virtual void Draw(HPEN pen1, HPEN pen2) = 0;	//нарисовать заданны объект
};

/*-----------------------  Интерфейс ITower ----------------------------------*/
class ITower {
	public: 
		virtual void Draw(HPEN pen1, HPEN pen2) = 0;		//общий рисунок	
		virtual void Base(HPEN pen) = 0;					//фундамент
		virtual void Observation(HPEN pen1, HPEN pen2) = 0;	//смотровая площадка
		virtual void Body(HPEN pen) = 0;					//тело
		virtual void Spire(HPEN pen) = 0;					//шпиль
};

/*-----------------------  Класс Tower ----------------------------------*/
class Tower : public ABC_Object, ITower {
	protected:
		int BaseLength;						//длина фундамента
		int ObservationRadius;				//радиус смотровой площадки
		int TotalHigh;						//общая высота
		int ObservationHigh;				//высота центра смотровой площадки

	public:
		Tower(int InitX, int InitY, int BaseLength, int ObservationRadius, int TotalHigh);	
		~Tower();

		//принудительная реализация интерфейса
		void Show();
		void Hide();
		void Drag(int step);							//перемещение фигуры
		void MoveTo(int NewX, int NewY);				//перемещение
		
		//отрисовка
		void Draw(HPEN pen1, HPEN pen2);				//нарисовать башню
		virtual void Base(HPEN pen);					//фундамент
		virtual void Observation(HPEN pen1, HPEN pen2);	//смотровая площадка
		virtual void Body(HPEN pen);					//тело
		virtual void Spire(HPEN pen);					//шпиль
		virtual void DrawHitbox(HPEN pen);				//нарисовать хитбокс(for debug)

		//геттеры хитбокса
		int GetRightSideHB();
		int GetDownSideHB();
		int GetLeftSideHB();
		int GetUpSideHB();
		int GetIndex();									//геттер индекса
};

/*-----------------------  Класс BrokenTower ----------------------------------*/
class BrokenTower : public Tower {
	public:
		BrokenTower(int InitX, int InitY, int BaseLength, int ObservationRadius, int TotalHigh);	
		~BrokenTower();

		void Spire(HPEN pen);			//шпиль
};

/*-----------------------  Класс PaintedTower ----------------------------------*/
class PaintedTower : public Tower {
	public:
		PaintedTower(int InitX, int InitY, int BaseLength, int ObservationRadius, int TotalHigh);	
		~PaintedTower();
		void Show();
		void Hide();

		//отрисовка
		void Draw(HPEN pen1, HPEN pen2);
		void Observation(HPEN pen1, HPEN pen2);	//смотровая площадка
};

/*-----------------------  Класс SqareTower ----------------------------------*/
class SqareTower : public Tower {
	public:
		SqareTower(int InitX, int InitY, int BaseLength, int ObservationRadius, int TotalHigh);	
		~SqareTower();
		void Show();
		void Hide();
		
		//отрисовка
		void Draw(HPEN pen1, HPEN pen2);
		void Observation(HPEN pen1, HPEN pen2);	//смотровая площадка
};

/*-----------------------  Класс Stone ----------------------------------*/
class Stone : public ABC_Object {
	protected:
		int radius; //радиус камня
	public:
		Stone(int InitX, int InitY, int r);
		~Stone();
		void Draw(HPEN pen1, HPEN pen2);
};

/*-----------------------  Класс Stop ----------------------------------*/
class Stop : public ABC_Object {
	protected:
		int radius;
		int stick;
	public:
		Stop(int InitX, int InitY, int r, int stick);
		~Stop();
		void Draw(HPEN pen1, HPEN pen2);
};

/*-----------------------  Класс Pond ----------------------------------*/
class Pond : public ABC_Object {
	protected:
		int radius;
	public:
		Pond(int InitX, int InitY, int r);
		~Pond();
		void Show();
		void Draw(HPEN pen1, HPEN pen2);
};

/*-----------------------  Класс Tree ----------------------------------*/
class Tree : public ABC_Object {
	protected:
		int High;
	public:
		Tree(int InitX, int InitY, int High);
		~Tree();
		void Draw(HPEN pen1, HPEN pen2);
};

bool Collision(ABC_Object& obj1, ABC_Object& obj2);