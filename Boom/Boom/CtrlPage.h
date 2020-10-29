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

#define BUTTON_1	101		//��ťID
#define SLIDER_1	102		//����ID
#define SLIDER_2	103		//����ID
#define STATIC_1	100		//�ı�ID		�ı�ID����Ϊ100��������	��СΪ1��
#define STATIC_2	200		//�ı�ID
#define STATIC_3	300		//�ı�ID
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

	struct WINDOWDATE {	//�Ӵ���
		const wstring _NameClass;	//����
		wstring _NameCh;			//�ı���ʾ����
		int min, max, init;			//�ֱ�Ϊ�������С ��� ��ǰֵ
		int _ID;					//��̬�ı�ID
		void(*Set)(double);
	};
	typedef WINDOWDATE WindowDate;
	struct CHLIDWINDOW {
		WindowDate* p_wd;
		HWND m_SliderHwnd;		//���������
		HWND m_StaticHwnd;		//�ı����
	};
	typedef CHLIDWINDOW ChlidWindow;

	class CtrlPage {
	private:
		WNDCLASSEX m_WndClass;
		HINSTANCE* m_hInstance;	//����ʵ��
		int m_CmdShow;
	public:
		vector<ChlidWindow> m_ArrChlidWindow;
		vector<HWND> m_ArrButton;				//��ѡ����
		vector<int> m_Arrint;
		HWND m_CtrlHwnd;
	private:
		static void OnSearchHWND(HWND _ChlidHwnd, CtrlPage* _pctrlpage, vector<ChlidWindow>::iterator& _vcw);
	protected:
		bool RegisterWIN();		//ע�ᴰ��
		void CreateWIN();		//��������
		void UpdateWIN();		//���´���
		void ShowWIN();			//��ʾ����
		void UnregisterWIN();	//���ٴ���
	public:
		CtrlPage(HINSTANCE _hInstance, int _nCmdShow);
		~CtrlPage();
		void InitWIN();
		void Release();
	public:
		static LRESULT CALLBACK WndProc(HWND _hwnd, UINT _message, WPARAM _wParam, LPARAM _lParam);	//���ڹ��̺���
		//�����Ӵ�������
		static void OnUpdateChlidWindow(HWND _ChlidHwnd, CtrlPage* _pctrlpage);
		void AddChlidWindow(ChlidWindow& _cw);
		bool HandleParam(int _GetMenu, int Pos);
	public:
		//Handle Message����֪ͨ��Ϣ
		void HandleWM_COMMAND(WPARAM _wParam, LPARAM _lParam);

	};

		//������ť
	HWND CreateButton(HWND _hwnd, RECT& _rc, LPTSTR _name, UINT _ID, UINT _style);
		//��������
	HWND CreateSlider(HWND _hwnd, RECT& _rc, LPTSTR _name, UINT _ID, UINT _style,
		int _min, int _max, int _init = 0);	
		//������̬�ı�
	HWND CreateStatic(HWND _hwnd, RECT& _rc, LPTSTR _str, UINT _ID, UINT _style);
		//������ѡ��
	HWND CreateButtom(HWND _hwnd, RECT& _rc, LPTSTR _str, UINT _ID, UINT _Style);

	static WindowDate s_Wd[CHLIDWINDOWW];
	WindowDate* WindowDateInit(bool _bool = true);						//���ര�ڵĸ�ֵ
	ChlidWindow* CreateChlidWindow(HWND _hwnd, bool _bool = true);		//���ര�ڵĴ���
	void TextByName(int, wstring&);
}
#endif