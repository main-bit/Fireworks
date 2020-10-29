#pragma once
#ifndef BASE_H
#define BASE_H
#include <windows.h>
#include <ctime>
#include <d2d1.h>
#include <d2d1_1.h>
#include <Dwrite.h>
#include <cmath>
#include <list>
#include "Lin.h"
#pragma comment(lib, "D2D1.lib")
#pragma comment(lib, "Dwrite.lib")


#define PI	3.1415926
#define PAI 180


#define STEPSIZE	1	//����	
#define UNITTIME	5	//ÿ����UIITTIME��	����һ����λʱ��


class Base {
private:
	D2D1_POINT_2F Begin;
	D2D1_POINT_2F End;				//�˵ط��е�Begin��End��������һ�����ӻ�ͼ����ʼ�� ��������ʵ���յ�
	double Width;					//�߿�
	double SpeedX, SpeedY;			//��ǰ�ٶ�
	double AccelX, AccelY;
	UINT UnitTime;					//ÿ����UnitTie��	����һ����λʱ��
	static int s_Accel;	//���������ȡֵ��Χ��[1, 10]
	static double s_Width;
private:
	Base& operator=(const Base& _Base) {}		//��ֹ��ֵ����
public:
	Base(const D2D1_POINT_2F& _Begin, const double _SpeedX, const double _SpeedY, const double _AccelX, const double _AccelY);
	Base(const Base& _Base);
public:
	void UpDate();
	void UpDateSpeedX(const double _SpeedX) { SpeedX += _SpeedX; }		//�����ٶ�ֵ
	void UpDateSpeedY(const double _SpeedY) { SpeedY += _SpeedY; }
	void UpDateEnd();					//�����յ�λ��
	void UpStep() { ++UnitTime; }			//Step����һ��
public:
	void InitStep() { UnitTime = 0; }		//��Step��ʼ��Ϊ0

	void SetBegin(const D2D1_POINT_2F _Begin) { Begin = _Begin; }
	void SetEnd(const D2D1_POINT_2F _End) { End = _End; }

	const D2D1_POINT_2F& GetBegin()const { return Begin; }
	const D2D1_POINT_2F& GetEnd()const { return End; }
	const double GetWidth()const { return Width; }
	const double GetSpeedX()const { return SpeedX; }
	const double GetSpeedY()const { return SpeedY; }

	static void SetStaticAccel(const double _Accel) { s_Accel = int(_Accel); }
	static void SetStaticWidth(const double _Width) { s_Width = _Width; }

	static int GetStaticAccel() { return s_Accel; }
	static int GetStaticWidth() { return s_Width; }
};

#endif