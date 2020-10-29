#pragma once
#ifndef BoomLine_H
#define BoomLine_H
#include "Base.h"
#include "Color.h"


class BoomLine{			//ȦȦ
private:
	Base* pBase;
	Color* pColor;
private:
	void Init(const D2D1_POINT_2F& _Begin, const double, const double, const double, const double, const int);
	void InitBase(const D2D1_POINT_2F& _Begin, const double, const double, const double, const double);		//��ʼ��Base��ָ��
	void InitColor(const int _ColorStyle);												//��ʼ��Color��ָ��
	void Release();
	void ReleaseBase();																	//�ͷ�Baseָ��
	void ReleaseColor();																//�ͷ�Colorָ��
	BoomLine& operator=(const BoomLine& _ellipse) {}									//��ֹ��ֵ
public:
	BoomLine(const D2D1_POINT_2F& _Begin, const double , const double , const double, const double, const int _ColorStyle = STYLE_RAND);
	BoomLine(const BoomLine& _ellipse);
	~BoomLine();
public:
	Base* GetBase()const { return pBase; }
	Color* GetColor()const { return pColor; }
};

#endif