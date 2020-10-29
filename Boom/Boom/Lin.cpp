#include "CtrlPage.h"
#include "Lin.h"
#include <time.h>

using Lin::CreateButton;	//按钮
using Lin::CreateSlider;	//滑块
using Lin::CreateStatic;	//静态文本
using Lin::CreateButtom;




		//创建按钮
HWND Lin::CreateButton(HWND _hwnd, RECT& _rc, LPTSTR _name, UINT _ID, UINT _style) {
	return CreateWindow(_T("BUTTON"), _name, _style,
		MY_GET_X(_rc), MY_GET_Y(_rc),
		MY_GET_WIDTH(_rc), MY_GET_HEIGHT(_rc),
		_hwnd, HMENU(_ID),
		(HINSTANCE)GetWindowLong(_hwnd, GWL_HINSTANCE), NULL);
}

		//创建滑块
HWND Lin::CreateSlider(HWND _hwnd, RECT& _rc, LPTSTR _name, UINT _ID, UINT _style,
	int _min, int _max, int _init) {	//创建滑块条
	HWND _Hwnd = CreateWindow(_T("msctls_trackbar32"),
		_name,
		_style,
		MY_GET_X(_rc), MY_GET_Y(_rc),
		MY_GET_WIDTH(_rc), MY_GET_HEIGHT(_rc),
		_hwnd, HMENU(_ID),
		HINSTANCE(GetWindowLongPtr(_hwnd, GWLP_HINSTANCE)), NULL);
	if (_Hwnd != NULL) {
		SendMessage(_Hwnd, TBM_SETRANGEMIN, true, LPARAM(_min));	//滑块的最小值
		SendMessage(_Hwnd, TBM_SETRANGEMAX, true, LPARAM(_max));	//滑块的最大值
		SendMessage(_Hwnd, TBM_SETPOS, true, LPARAM(_init));		//当前值
	}
	return _Hwnd;
}

		//创建静态文本
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

		//创建复选框
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

//此方法可以进行优化
const int Lin::Rand(const int _Min, const int _Max) {		//产生 [_Min, _Max] 范围的随机数
	if (_Min == _Max)	return _Min;							//若_Min == _Max 则代表产生_Min~_Max间的数 即他们俩本身
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