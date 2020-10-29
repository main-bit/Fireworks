#pragma once
#ifndef BoomLine_H
#define BoomLine_H
#include "Base.h"
#include "Color.h"


class BoomLine{			//圈圈
private:
	Base* pBase;
	Color* pColor;
private:
	void Init(const D2D1_POINT_2F& _Begin, const double, const double, const double, const double, const int);
	void InitBase(const D2D1_POINT_2F& _Begin, const double, const double, const double, const double);		//初始化Base类指针
	void InitColor(const int _ColorStyle);												//初始化Color类指针
	void Release();
	void ReleaseBase();																	//释放Base指针
	void ReleaseColor();																//释放Color指针
	BoomLine& operator=(const BoomLine& _ellipse) {}									//禁止赋值
public:
	BoomLine(const D2D1_POINT_2F& _Begin, const double , const double , const double, const double, const int _ColorStyle = STYLE_RAND);
	BoomLine(const BoomLine& _ellipse);
	~BoomLine();
public:
	Base* GetBase()const { return pBase; }
	Color* GetColor()const { return pColor; }
};

#endif