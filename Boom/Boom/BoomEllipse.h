#pragma once
#ifndef BOOMELLIPSE_H
#define BOOMELLIPSE_H

#include "Base.h"
#include "Color.h"

#define DEFAULT_RADIU_MIN	1		//圆的最小半径
#define DEFAULT_RADIU_MAX	7		//圆的最大半径

class BoomEllipse {
private:
	D2D1_POINT_2F Begin;		//圆心
	UINT Radiu;					//圆的当前半径
	Color* pColor;				//圆的颜色
	UINT UnitTime;
private:
	void InitColor(const int _ColorStyle);
	void Release();
	void ReleaseColor();
	BoomEllipse& operator=(const BoomEllipse&) {}		//禁止赋值
	BoomEllipse(const BoomEllipse& _BoomEllipse) {}		//禁止拷贝
public:
	BoomEllipse(D2D1_POINT_2F _Begin, const int _ColorStyle);
	~BoomEllipse();
public:
	const Color* GetColor()const { return pColor; }

	void Draw(ID2D1HwndRenderTarget* pRT, ID2D1SolidColorBrush* pBrush);
	void UpDate();
};
#endif