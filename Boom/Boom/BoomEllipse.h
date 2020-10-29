#pragma once
#ifndef BOOMELLIPSE_H
#define BOOMELLIPSE_H

#include "Base.h"
#include "Color.h"

#define DEFAULT_RADIU_MIN	1		//Բ����С�뾶
#define DEFAULT_RADIU_MAX	7		//Բ�����뾶

class BoomEllipse {
private:
	D2D1_POINT_2F Begin;		//Բ��
	UINT Radiu;					//Բ�ĵ�ǰ�뾶
	Color* pColor;				//Բ����ɫ
	UINT UnitTime;
private:
	void InitColor(const int _ColorStyle);
	void Release();
	void ReleaseColor();
	BoomEllipse& operator=(const BoomEllipse&) {}		//��ֹ��ֵ
	BoomEllipse(const BoomEllipse& _BoomEllipse) {}		//��ֹ����
public:
	BoomEllipse(D2D1_POINT_2F _Begin, const int _ColorStyle);
	~BoomEllipse();
public:
	const Color* GetColor()const { return pColor; }

	void Draw(ID2D1HwndRenderTarget* pRT, ID2D1SolidColorBrush* pBrush);
	void UpDate();
};
#endif