#pragma once
/********************************************************************
 *          ������������ ������ �1 �� ��� 4 �������                 *
 *------------------------------------------------------------------*
 * Project Type  : Win64 Console Application                        *
 * Project Name  : Laba_OOP_1                                       *
 * File Name     : tower.h                                          *
 * Programmer(s) : ������ ����� �3�-209�-22           				*
 * Modifyed By   :                                                  *
 * Created       : 14/04/2023                                       *
 * Last Revision : 14/04/2023                                       *
 * Comment(s)    : ���������� �������� �������						*
 *******************************************************************/

/*-----------------------------------------------------------------------*/
/*                         � � � �    � � � � � �                        */
/*-----------------------------------------------------------------------*/

#define ARR_SIZE 4 //������ ������� ����������� ��������

/*-----------------------------------------------------------------------*/
/*                         � � � �    � � � � � �                        */
/*-----------------------------------------------------------------------*/

/*-----------------------  ����� Location -------------------------*/
class Location {
	protected:		
		int x;							//���������� X
		int y;							//���������� Y

	public:
		Location(int InitX, int InitY); //�����������
		~Location();                    //����������
		int GetX();						//�������� X ���������� �����
		int GetY();						//�������� Y ���������� �����
};

/*-----------------------  ����� Point ----------------------------------*/
class Point : public Location{
	protected:							
		bool visible;								//��������� �����

	public:
		Point(int InitX, int InitY);				//�����������
		~Point();									//����������

		bool IsVisible();							//�������� �������
		virtual void MoveTo(int NewX, int NewY);	//�����������
		
		virtual void Drag(int Step); 				//����������
		virtual void Show();						//�������� 
		virtual void Hide();						//������
};

/*-----------------------  ����������� ������� ����� ABC_Object ---------------------------*/
class ABC_Object: public Point {
	protected:
		int rightSideHB;	//������ ������� ��������
		int downSideHB;		//������ ������� ��������
		int leftSideHB;		//����� ������� ��������
		int upSideHB;		//������� ������� ��������
		int index;			//������ �������
			
	public:
		ABC_Object(int InitX, int InitY);
		ABC_Object();									//���������� �����������
		~ABC_Object();
		
		//�������
		int GetRightSideHB();
		int GetDownSideHB();
		int GetLeftSideHB();
		int GetUpSideHB();
		int GetIndex();									

		virtual void Show();							//�������� 
		virtual void Hide();							//������
		virtual void Draw(HPEN pen1, HPEN pen2) = 0;	//���������� ������� ������
};

/*-----------------------  ��������� ITower ----------------------------------*/
class ITower {
	public: 
		virtual void Draw(HPEN pen1, HPEN pen2) = 0;		//����� �������	
		virtual void Base(HPEN pen) = 0;					//���������
		virtual void Observation(HPEN pen1, HPEN pen2) = 0;	//��������� ��������
		virtual void Body(HPEN pen) = 0;					//����
		virtual void Spire(HPEN pen) = 0;					//�����
};

/*-----------------------  ����� Tower ----------------------------------*/
class Tower : public ABC_Object, ITower {
	protected:
		int BaseLength;						//����� ����������
		int ObservationRadius;				//������ ��������� ��������
		int TotalHigh;						//����� ������
		int ObservationHigh;				//������ ������ ��������� ��������

	public:
		Tower(int InitX, int InitY, int BaseLength, int ObservationRadius, int TotalHigh);	
		~Tower();

		//�������������� ���������� ����������
		void Show();
		void Hide();
		void Drag(int step);							//����������� ������
		void MoveTo(int NewX, int NewY);				//�����������
		
		//���������
		void Draw(HPEN pen1, HPEN pen2);				//���������� �����
		virtual void Base(HPEN pen);					//���������
		virtual void Observation(HPEN pen1, HPEN pen2);	//��������� ��������
		virtual void Body(HPEN pen);					//����
		virtual void Spire(HPEN pen);					//�����
		virtual void DrawHitbox(HPEN pen);				//���������� �������(for debug)

		//������� ��������
		int GetRightSideHB();
		int GetDownSideHB();
		int GetLeftSideHB();
		int GetUpSideHB();
		int GetIndex();									//������ �������
};

/*-----------------------  ����� BrokenTower ----------------------------------*/
class BrokenTower : public Tower {
	public:
		BrokenTower(int InitX, int InitY, int BaseLength, int ObservationRadius, int TotalHigh);	
		~BrokenTower();

		void Spire(HPEN pen);			//�����
};

/*-----------------------  ����� PaintedTower ----------------------------------*/
class PaintedTower : public Tower {
	public:
		PaintedTower(int InitX, int InitY, int BaseLength, int ObservationRadius, int TotalHigh);	
		~PaintedTower();
		void Show();
		void Hide();

		//���������
		void Draw(HPEN pen1, HPEN pen2);
		void Observation(HPEN pen1, HPEN pen2);	//��������� ��������
};

/*-----------------------  ����� SqareTower ----------------------------------*/
class SqareTower : public Tower {
	public:
		SqareTower(int InitX, int InitY, int BaseLength, int ObservationRadius, int TotalHigh);	
		~SqareTower();
		void Show();
		void Hide();
		
		//���������
		void Draw(HPEN pen1, HPEN pen2);
		void Observation(HPEN pen1, HPEN pen2);	//��������� ��������
};

/*-----------------------  ����� Stone ----------------------------------*/
class Stone : public ABC_Object {
	protected:
		int radius; //������ �����
	public:
		Stone(int InitX, int InitY, int r);
		~Stone();
		void Draw(HPEN pen1, HPEN pen2);
};

/*-----------------------  ����� Stop ----------------------------------*/
class Stop : public ABC_Object {
	protected:
		int radius;
		int stick;
	public:
		Stop(int InitX, int InitY, int r, int stick);
		~Stop();
		void Draw(HPEN pen1, HPEN pen2);
};

/*-----------------------  ����� Pond ----------------------------------*/
class Pond : public ABC_Object {
	protected:
		int radius;
	public:
		Pond(int InitX, int InitY, int r);
		~Pond();
		void Show();
		void Draw(HPEN pen1, HPEN pen2);
};

/*-----------------------  ����� Tree ----------------------------------*/
class Tree : public ABC_Object {
	protected:
		int High;
	public:
		Tree(int InitX, int InitY, int High);
		~Tree();
		void Draw(HPEN pen1, HPEN pen2);
};

bool Collision(ABC_Object& obj1, ABC_Object& obj2);