#pragma once
#ifndef PARTCLE_H
#define PARTCLE_H
#include "Base.h"
#include "BoomLine.h"
using std::list;

#define DEFAULT_FRICTION	0.05			//Ĭ��Ħ����
#define DEFAULT_GRAVITY		0.07			//Ĭ������
#define DEFAULT_SPEED		2				//Ĭ�ϱ�ը�����ٶ�
#define DEFAULT_DIE			-0.03			//Ĭ��������ʧ����

class Partcle{							//��ը����
private:
	BoomLine* pLine;
	double FrictionX;					//x���ϵĺ㶨Ħ����
	double Gravity;						//����
	static double s_Gravity;
	//x���Ϸֱ�Ħ������ȡֵ��Χ
	static double s_FrictionX;
	static double s_Speed;				//�����ٶ�
	static double s_Die;						//������ʧ����
private:
	inline void Init(const D2D1_POINT_2F& _Begin, const int _ColorStyle);
	inline void InitFactionX();
	inline void InitFactionY();
	inline void ReleaseBoomLine() { if (pLine != NULL)	delete pLine; }
	inline void Release() { ReleaseBoomLine(); }
	Partcle& operator=(const Partcle& _Partcle) {}		//��ֹ��ֵ
public:
	Partcle(const D2D1_POINT_2F& _Begin, const int _ColorStyle);
	Partcle(const Partcle& _Partcle);
	~Partcle() { Release(); }
public:
	void Draw(ID2D1HwndRenderTarget* pRT, ID2D1SolidColorBrush* pBrush, ID2D1StrokeStyle* pStyle);
	void UpDate();														//�������ӵ�λ��
	static bool OutDate(list<Partcle*>::iterator& _iter, RECT& _rc);		//�ж϶����Ƿ��ʱ
public:
	void SetFrictionX(double _FrictionX) { FrictionX = _FrictionX; }

	BoomLine* GetBoomLine()const { return pLine; }
	const double GetFrictionX()const { return FrictionX; }

	static void SetStaticGravity(const double _Gravity) { s_Gravity = _Gravity / 100.0f; }
	static void SetStaticFrictionX(const double _FrictionX) { s_FrictionX = _FrictionX / 100.0f; }
	static void SetStaticDie(const double _Die) { s_Die = _Die / -100.0; }

	static double GetStaticGravity() { return s_Gravity * 100; }
	static double GetStaticFrictionX() { return s_FrictionX * 100; }
	static double GetStaticDie() { return s_Die * -100; }
};

#endif 