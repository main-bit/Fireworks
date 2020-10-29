#include "CtrlPage.h"
#include "Lin.h"
#include <time.h>

using Lin::CreateButton;	//��ť
using Lin::CreateSlider;	//����
using Lin::CreateStatic;	//��̬�ı�
using Lin::CreateButtom;




		//������ť
HWND Lin::CreateButton(HWND _hwnd, RECT& _rc, LPTSTR _name, UINT _ID, UINT _style) {
	return CreateWindow(_T("BUTTON"), _name, _style,
		MY_GET_X(_rc), MY_GET_Y(_rc),
		MY_GET_WIDTH(_rc), MY_GET_HEIGHT(_rc),
		_hwnd, HMENU(_ID),
		(HINSTANCE)GetWindowLong(_hwnd, GWL_HINSTANCE), NULL);
}

		//��������
HWND Lin::CreateSlider(HWND _hwnd, RECT& _rc, LPTSTR _name, UINT _ID, UINT _style,
	int _min, int _max, int _init) {	//����������
	HWND _Hwnd = CreateWindow(_T("msctls_trackbar32"),
		_name,
		_style,
		MY_GET_X(_rc), MY_GET_Y(_rc),
		MY_GET_WIDTH(_rc), MY_GET_HEIGHT(_rc),
		_hwnd, HMENU(_ID),
		HINSTANCE(GetWindowLongPtr(_hwnd, GWLP_HINSTANCE)), NULL);
	if (_Hwnd != NULL) {
		SendMessage(_Hwnd, TBM_SETRANGEMIN, true, LPARAM(_min));	//�������Сֵ
		SendMessage(_Hwnd, TBM_SETRANGEMAX, true, LPARAM(_max));	//��������ֵ
		SendMessage(_Hwnd, TBM_SETPOS, true, LPARAM(_init));		//��ǰֵ
	}
	return _Hwnd;
}

		//������̬�ı�
HWND Lin::CreateStatic(HWND _hwnd, RECT& _rc, LPTSTR _str, UINT _ID, UINT _style) {
	HWND hStatic = CreateWindow(
		_T("STATIC"),
		_str,
		_style,		// WS_CHILD | WS_VISIBLE | SS_LEFT | WS_BORDER | SS_CENTERIMAGE | SS_NOTIFY,
		MY_GET_X(_rc), MY_GET_Y(_rc),
		MY_GET_WIDTH(_rc), MY_GET_HEIGHT(_rc),
		_hwnd,
		HMENU(_ID),
		HINSTANCE(GetWindowLongPtr(_hwnd, GWLP_HINSTANCE)),
		nullptr
	);
	return hStatic;
}

		//������ѡ��
HWND Lin::CreateButtom(HWND _hwnd, RECT& _rc, LPTSTR _str, UINT _ID, UINT _style) {
	HWND hButtom = CreateWindow(
		_T("BUTTON"),
		_str,
		_style,
		MY_GET_X(_rc), MY_GET_Y(_rc),
		MY_GET_WIDTH(_rc), MY_GET_HEIGHT(_rc),
		_hwnd,
		HMENU(_ID),
		HINSTANCE(GetWindowLongPtr(_hwnd, GWLP_HINSTANCE)),
		nullptr
	);
	return hButtom;
}

//�˷������Խ����Ż�
const int Lin::Rand(const int _Min, const int _Max) {		//���� [_Min, _Max] ��Χ�������
	if (_Min == _Max)	return _Min;							//��_Min == _Max ��������_Min~_Max����� ������������
	return rand() % (_Max - _Min) + _Min;
}

/*template<typename T>
bool Lin::opposite(T t1, T t2) {
	if (t1 * t2 >= 0)
		return true;
	return false;
}*/

bool Lin::opposite(double t1, double t2) {
	if (t1 * t2 >= 0)
		return true;
	return false;
}