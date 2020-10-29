#pragma once
#ifndef CTRLPAGE_H
#define CTRLPAGE_H

#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <CommCtrl.h>
#include <Shlwapi.h>
#include <string>
#include <vector>
#include "Base.h"
#include "Bullet.h"
#include "Partcle.h"
#include "Color.h"

//#include <atlbase.h>	//CComPtr
using std::wstring;
using std::vector;

#define BUTTON_1	101		//按钮ID
#define SLIDER_1	102		//滑块ID
#define SLIDER_2	103		//滑块ID
#define STATIC_1	100		//文本ID		文本ID必须为100的整数倍	最小为1倍
#define STATIC_2	200		//文本ID
#define STATIC_3	300		//文本ID
#define STATIC_4	400
#define STATIC_5	500
#define STATIC_6	600
#define STATIC_7	700
#define STATIC_8	800
#define STATIC_9	900
#define STATIC_10	1000
#define STATIC_11	1100
#define CHLIDWINDOWW	11

#define MY_GET_X(rect) (rect.left)
#define MY_GET_Y(rect) (rect.top)
#define MY_GET_WIDTH(rect)  (rect.right-rect.left)
#define MY_GET_HEIGHT(rect) (rect.bottom-rect.top)


namespace Lin {
	class CtrlPage;

	struct WINDOWDATE {	//子窗口
		const wstring _NameClass;	//类名
		wstring _NameCh;			//文本显示内容
		int min, max, init;			//分别为滑块的最小 最大 当前值
		int _ID;					//静态文本ID
		void(*Set)(double);
	};
	typedef WINDOWDATE WindowDate;
	struct CHLIDWINDOW {
		WindowDate* p_wd;
		HWND m_SliderHwnd;		//跟踪条句柄
		HWND m_StaticHwnd;		//文本句柄
	};
	typedef CHLIDWINDOW ChlidWindow;

	class CtrlPage {
	private:
		WNDCLASSEX m_WndClass;
		HINSTANCE* m_hInstance;	//窗口实例
		int m_CmdShow;
	public:
		vector<ChlidWindow> m_ArrChlidWindow;
		vector<HWND> m_ArrButton;				//复选框句柄
		vector<int> m_Arrint;
		HWND m_CtrlHwnd;
	private:
		static void OnSearchHWND(HWND _ChlidHwnd, CtrlPage* _pctrlpage, vector<ChlidWindow>::iterator& _vcw);
	protected:
		bool RegisterWIN();		//注册窗口
		void CreateWIN();		//创建窗口
		void UpdateWIN();		//更新窗口
		void ShowWIN();			//显示窗口
		void UnregisterWIN();	//销毁窗口
	public:
		CtrlPage(HINSTANCE _hInstance, int _nCmdShow);
		~CtrlPage();
		void InitWIN();
		void Release();
	public:
		static LRESULT CALLBACK WndProc(HWND _hwnd, UINT _message, WPARAM _wParam, LPARAM _lParam);	//窗口过程函数
		//更新子窗口内容
		static void OnUpdateChlidWindow(HWND _ChlidHwnd, CtrlPage* _pctrlpage);
		void AddChlidWindow(ChlidWindow& _cw);
		bool HandleParam(int _GetMenu, int Pos);
	public:
		//Handle Message处理通知消息
		void HandleWM_COMMAND(WPARAM _wParam, LPARAM _lParam);

	};

		//创建按钮
	HWND CreateButton(HWND _hwnd, RECT& _rc, LPTSTR _name, UINT _ID, UINT _style);
		//创建滑块
	HWND CreateSlider(HWND _hwnd, RECT& _rc, LPTSTR _name, UINT _ID, UINT _style,
		int _min, int _max, int _init = 0);	
		//创建静态文本
	HWND CreateStatic(HWND _hwnd, RECT& _rc, LPTSTR _str, UINT _ID, UINT _style);
		//创建复选框
	HWND CreateButtom(HWND _hwnd, RECT& _rc, LPTSTR _str, UINT _ID, UINT _Style);

	static WindowDate s_Wd[CHLIDWINDOWW];
	WindowDate* WindowDateInit(bool _bool = true);						//子类窗口的赋值
	ChlidWindow* CreateChlidWindow(HWND _hwnd, bool _bool = true);		//子类窗口的创建
	void TextByName(int, wstring&);
}
#endif