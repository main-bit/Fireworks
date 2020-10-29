#include "BoomLine.h"


BoomLine::BoomLine(const D2D1_POINT_2F& _Begin, const double _SpeedX, const double _SpeedY, const double _AccelX, const double _AccelY, const int _ColorStyle) :
						pBase(NULL), pColor(NULL){
	Init(_Begin, _SpeedX, _SpeedY, _AccelX, _AccelY, _ColorStyle);
}

BoomLine::BoomLine(const BoomLine& _Ellipse): pBase(NULL), pColor(NULL)
{
	pBase = new Base(*_Ellipse.GetBase());		//调用拷贝构造函数
	pColor = new Color(*_Ellipse.GetColor());	//调用拷贝构造函数
}

BoomLine::~BoomLine() {
	Release();
}

void BoomLine::InitBase(const D2D1_POINT_2F& _Begin, const double _SpeedX, const double _SpeedY, const double _AccelX, const double _AccelY) {
	pBase = new Base(_Begin, _SpeedX, _SpeedY, _AccelX, _AccelY);		//调用构造函数
}

void BoomLine::InitColor(const int _ColorStyle) {
	pColor = new Color(_ColorStyle);		//调用构造函数
}

void BoomLine::Init(const D2D1_POINT_2F& _Begin, const double  _X, const double _Y,const double _AccelX, const double _AccelY, const int _ColorStyle) {
	InitBase(_Begin, _X, _Y, _AccelX, _AccelY);
	InitColor(_ColorStyle);
}

void BoomLine::ReleaseBase() {
	if(pBase != NULL)
		delete pBase;
}

void BoomLine::ReleaseColor() {
	if (pColor != NULL)
		delete pColor;
}

void BoomLine::Release() {
	ReleaseBase();
	ReleaseColor();
}