#include "BoomEllipse.h"


BoomEllipse::BoomEllipse(D2D1_POINT_2F _Begin, const int _ColorStyle) : pColor(NULL), Begin(_Begin), Radiu(DEFAULT_RADIU_MIN), UnitTime(0) {
	InitColor(_ColorStyle);
}

BoomEllipse::~BoomEllipse() {
	Release();
}

void BoomEllipse::InitColor(const int _ColorStyle) {
	pColor = new Color(_ColorStyle);
}

void BoomEllipse::Release() {
	ReleaseColor();
}

void BoomEllipse::ReleaseColor() {
	if (pColor != NULL)
		delete pColor;
}

void BoomEllipse::Draw(ID2D1HwndRenderTarget* pRT, ID2D1SolidColorBrush* pBrush) {
	pBrush->SetColor(D2D1::ColorF(pColor->GetR(), pColor->GetG(), pColor->GetB(), pColor->GetAlpha()));
	pRT->FillEllipse(D2D1::Ellipse(Begin, Radiu, Radiu), pBrush);
	++UnitTime;
	UpDate();
}

void BoomEllipse::UpDate() {
	if (UnitTime == UNITTIME) {
		++Radiu;
		UnitTime = 0;
	}
	if (Radiu == DEFAULT_RADIU_MAX + 1)	Radiu = DEFAULT_RADIU_MIN;	
}