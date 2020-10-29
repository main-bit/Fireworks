#include "Color.h"

//��ʼ����̬����
int Color::RandR = DEFAULT_RGB;
int Color::RandG = DEFAULT_RGB;
int Color::RandB = DEFAULT_RGB;

Color::Color(int _Style) :Alpha(1.0f) {
	switch (_Style) {
		case STYLE_DEFAULT: {
			//����Ĭ�ϲ���
			R = G = B = 1.0f;
		}
		break;
		case STYLE_RAND: {
			//���
			InitColor();
		}
		break;
	}
}

Color::Color(const int _R, const int _G, const int _B) {
	Alpha = 1.0f;
	R = _R;	G = _G, B = _B;
}

		//�������캯���൱�ڲ���ΪSTYLE_RAND�Ĺ��캯��
Color::Color(const Color& _Color) :Alpha(_Color.GetAlpha()){
	InitColor();
}

Color& Color::operator=(const Color& _Color) {
	if (this == &_Color)	return *this;
	R = _Color.GetR();
	G = _Color.GetG();
	B = _Color.GetB();
	Alpha = _Color.GetAlpha();
	return *this;
}

void Color::InitColor() {
	R = ColorRand(RandR) / 100.0;
	G = ColorRand(RandG) / 100.0;
	B = ColorRand(RandB) / 100.0;
}