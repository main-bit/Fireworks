#pragma once
#ifndef COLOR_H
#define COLOR_H
#include <ctime>
#include <windows.h>


#define STYLE_DEFAULT	0	//默认风格
#define STYLE_RAND		1	//随机颜色
#define DEFAULT_RGB		100	//RGB的随机范围设置为255
struct Color {
	double Alpha;
	float R, G, B;
	static int RandR, RandG, RandB;
	Color(int _Style = STYLE_DEFAULT);
	Color(const int _R, const int _G, const int _B);
	Color(const Color& _Color);
	Color& operator=(const Color& _Color);

	void InitColor();

	void AddAlpha(const double _Alpha) { Alpha += _Alpha; }
	void SetRGB(const int _R, const int _G, const int _B) { R = _R;	G = _G;	B = _B; }

	const double GetAlpha()const { return Alpha; }
	const float GetR()const { return R; }
	const float GetG()const { return G; }
	const float GetB()const { return B; }

	static int GetStaticR() { return RandR; }
	static int GetStaticG() { return RandG; }
	static int GetStaticB() { return RandB; }

	static void SetStaticR(double _R) { RandR = int(_R); }
	static void SetStaticG(double _G) { RandG = int(_G); }
	static void SetStaticB(double _B) { RandB = int(_B); }

	static void SetRandRGB(int _R, int _G, int _B) {
		RandR = _R;
		RandG = _G;
		RandB = _B;
	}

	static const int ColorRand(int _Num) {
		return rand() % (_Num + 1);
	}
};



#endif