#include "CtrlPage.h"
#include <string>
#include <windowsx.h>
using namespace Lin;
using std::wstring;
using std::to_wstring;



CtrlPage::CtrlPage(HINSTANCE _hInstance, int _nCmdShow)
:m_hInstance(&_hInstance),m_CmdShow(_nCmdShow) {
	m_WndClass = { 0 };
	m_WndClass.cbSize = sizeof(WNDCLASSEX);
	m_WndClass.style = CS_DBLCLKS;		//双击鼠标时会发送双击消息
	m_WndClass.lpfnWndProc = static_cast<WNDPROC>(&CtrlPage::WndProc);	//窗口过程函数
	m_WndClass.cbClsExtra = 0;
	m_WndClass.cbWndExtra = 0;
	m_WndClass.hInstance = _hInstance;	//窗口实例
	m_WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);	//程序图标
	m_WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);	//IDC_CROSS为十字光标
	m_WndClass.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	m_WndClass.lpszMenuName = NULL;		//菜单
	m_WndClass.lpszClassName = L"CtrlPage";
	m_WndClass.hIconSm = NULL;


	//注册窗口
	RegisterWIN();
	//创建窗口
	CreateWIN();
}

CtrlPage::~CtrlPage() {
	Release();
}

bool CtrlPage::RegisterWIN() {		//注册窗口
	return RegisterClassExW(&m_WndClass);
}

void CtrlPage::InitWIN() {		//窗口初始化
	//显示窗口
	ShowWIN();
	//更新窗口
	UpdateWIN();
	//窗口透明
	SetWindowLongPtr(m_CtrlHwnd, GWL_EXSTYLE, WS_EX_LAYERED);
	SetLayeredWindowAttributes(m_CtrlHwnd, 0, 200, LWA_ALPHA);

	//将写好的ChlidWindow放入vector中
	ChlidWindow* _cw = CreateChlidWindow(this->m_CtrlHwnd, false);		//获取在此方法中的静态变量ChlidWindow地址
	for (int _i = 0; _i < CHLIDWINDOWW; ++_i) {
		if (_i == 0)
			_cw[_i].p_wd = WindowDateInit(true);//对子类的窗口进行初始化
		else
			_cw[_i].p_wd = _cw[_i - 1].p_wd + 1;
		m_ArrChlidWindow.push_back( *(_cw+_i) );
	}
	//创建复选框
	RECT Rc = { 10,670,110,720 };
	m_ArrButton.push_back(CreateButtom(this->m_CtrlHwnd, Rc, const_cast<wchar_t*>(L"自动放烟花"), BUTTON_1, BS_CHECKBOX | WS_CHILD | WS_VISIBLE | WS_TABSTOP));
	Button_SetCheck(m_ArrButton[0], BST_CHECKED);
}

void CtrlPage::Release() {
	UnregisterWIN();		//销毁窗口
}

void CtrlPage::CreateWIN() {		//创建窗口
	m_CtrlHwnd = CreateWindow(L"CtrlPage", L"属性页", WS_OVERLAPPED,
		20, 60, 450, 750, NULL, NULL, *m_hInstance, NULL);
}

void CtrlPage::ShowWIN() {			//显示窗口
	ShowWindow(m_CtrlHwnd, m_CmdShow);
}

void CtrlPage::UpdateWIN() {		//更新窗口
	UpdateWindow(m_CtrlHwnd);
}

void CtrlPage::UnregisterWIN() {	//销毁窗口
	UnregisterClass(L"CtrlPage", *m_hInstance);
}



void CtrlPage::OnSearchHWND(HWND _ChlidWindow, CtrlPage* _pctrlpage, vector<ChlidWindow>::iterator& _vcw) {
	_vcw = _pctrlpage->m_ArrChlidWindow.begin();
	for (; _vcw != _pctrlpage->m_ArrChlidWindow.end(); ++_vcw) {
		if (_vcw->m_SliderHwnd == _ChlidWindow) {
			//当找到与之对应的_ChlidWindow的位置 立即break
			break;
		}
	}
}

		//从已有的Slider子类窗口中查找_hwnd子窗口
void CtrlPage::OnUpdateChlidWindow(HWND _ChlidHwnd, CtrlPage* _pctrlpage) {
	vector<ChlidWindow>::iterator _vcw;
	OnSearchHWND(_ChlidHwnd, _pctrlpage, _vcw);		//调整_pcw位置 使_pcw->m_SliderHwnd == _ChlidHwnd
	if ( _vcw != _pctrlpage->m_ArrChlidWindow.end() ) {
		//若找到与之对应的值	就获取该跟踪条当前的值
		DWORD dwPos = SendMessage(_ChlidHwnd, TBM_GETPOS, 0, 0);
		_vcw->p_wd->Set((int)dwPos);
		//更改跟踪条对应的静态文本内容
		wstring _wstr(_vcw->p_wd->_NameCh);// = wstring(_vcw->p_wd->_NameCh) + to_wstring(int(dwPos));
		TextByName(int(dwPos), _wstr);
		Static_SetText(_vcw->m_StaticHwnd, _wstr.c_str());
	}
}

void CtrlPage::AddChlidWindow(ChlidWindow& _cw) {
	m_ArrChlidWindow.push_back(_cw);
}

//处理参数
bool CtrlPage::HandleParam(int _IDMENU, int Pos) {
	switch (_IDMENU) {
	case 0:		//处理加速度
		Base::SetStaticAccel(Pos);
		return true;
	case 1:
		Base::SetStaticWidth(Pos);
		return true;
	case 2:
		Bullet::SetStaticSpeed(Pos);
		return true;
	case 3:
		Bullet::SetDefaultPartcleNum(Pos);
		return true;
	case 4:
		Partcle::SetStaticGravity(Pos);
		return true;
	case 5:
		Partcle::SetStaticFrictionX(Pos);
		return true;
	case 6:
		Partcle::SetStaticDie(Pos);
		return true;
	case 7:
		Color::SetStaticR(Pos);
		return true;
	case 8:
		Color::SetStaticG(Pos);
		return true;
	case 9:
		Color::SetStaticB(Pos);
		return true;
	case 10:
		Bullet::SetStaticTransparent(Pos);
		return true;
	}
	return false;
}

void CtrlPage::HandleWM_COMMAND(WPARAM _wParam, LPARAM _lParam) {
	int wmID = LOWORD(_wParam);
	int wmEvent = HIWORD(_wParam);
	if (wmEvent == STN_DBLCLK) {
		//开始处理STATIC的双击消息
		#define GETMENU(_ID)	((_ID / 100) - 1)
		int dwPos = WindowDateInit(false)[GETMENU(wmID)].init;	//获取跟踪条当前的位置
		//更改参数
		if (HandleParam(GETMENU(wmID), dwPos)) {	//更改成功	继续下一步
			//设置跟踪条当前位置
			SendMessage(m_ArrChlidWindow[GETMENU(wmID)].m_SliderHwnd, TBM_SETPOS, true, LPARAM(dwPos));
			//设置文本内容
			wstring _wstr(m_ArrChlidWindow[GETMENU(wmID)].p_wd->_NameCh);
			TextByName(dwPos, _wstr);	//更改_wstr内容
			//更新文本内容
			Static_SetText(m_ArrChlidWindow[GETMENU(wmID)].m_StaticHwnd, const_cast<wchar_t*>(_wstr.c_str()));
		}
		//处理结束	将取消宏标识
		#undef GETMENU(_ID);
	}
	else if (wmEvent == BN_CLICKED) {
		//开始处理复选框消息
		if (wmID == BUTTON_1)
			if (SendMessage(m_ArrButton[0], BM_GETCHECK, 0, 0) == BST_CHECKED) {
				//取消自动放烟花
				Bullet::SetStaticAutoBullet(false);
				Button_SetCheck(m_ArrButton[0], BST_UNCHECKED);
			}
			else {
				//自动放烟花
				Bullet::SetStaticAutoBullet(true);
				Button_SetCheck(m_ArrButton[0], BST_CHECKED);
			}
	}
}

#define FILLWINDOWDATE(_fun, _name, _min, _max, _init, _ID) {_T(#_fun), _T(_name), _min, _max, _init, _ID, &(##_fun)}
#define ASSFILLWINDOWDATE(_Arr, _i, _fun, _name, _min, _max, _init, _ID)	_Arr[_i] = FILLWINDOWDATE(_fun, _name, _min, _max, _init, _ID)
WindowDate* Lin::WindowDateInit(bool _bool) {
	static WindowDate* _pwd = NULL;
	int BaseAccel = Base::GetStaticAccel();
	int BaseWidth = Base::GetStaticWidth();
	int BulletSpeed = Bullet::GetStaticSpeed();
	int BulletNum = Bullet::GetDefaultPartcleNum();
	int PartcleGravity = Partcle::GetStaticGravity();
	int PartcleFaction = Partcle::GetStaticFrictionX();
	int PartcleDie = Partcle::GetStaticDie();
	int ColorR = Color::GetStaticR();
	int ColorG = Color::GetStaticG();
	int ColorB = Color::GetStaticB();
	int BulletTransparent = Bullet::GetStaticTransparent();
	if (_bool) {
		static WindowDate s_wd[CHLIDWINDOWW] = {
			FILLWINDOWDATE(Base::SetStaticAccel, "炮弹加速度", 1, 10, BaseAccel,	STATIC_1),
			FILLWINDOWDATE(Base::SetStaticWidth, "线宽", 1, 40, BaseWidth, STATIC_2),
			FILLWINDOWDATE(Bullet::SetStaticSpeed, "炮弹速度", 1, 30, BulletSpeed, STATIC_3),
			FILLWINDOWDATE(Bullet::SetDefaultPartcleNum, "爆炸粒子数", 0, 500, BulletNum, STATIC_4),
			FILLWINDOWDATE(Partcle::SetStaticGravity, "粒子所受重力", 0, 15, PartcleGravity, STATIC_5),
			FILLWINDOWDATE(Partcle::SetStaticFrictionX, "粒子摩擦力", 0, 20, PartcleFaction, STATIC_6),
			FILLWINDOWDATE(Partcle::SetStaticDie, "粒子消失速率", 1, 10, PartcleDie, STATIC_7),
			FILLWINDOWDATE(Color::SetStaticR, "颜色R取值范围", 1, 100, ColorR, STATIC_8),
			FILLWINDOWDATE(Color::SetStaticG, "颜色G取值范围", 1, 100, ColorG, STATIC_9),
			FILLWINDOWDATE(Color::SetStaticB, "颜色B取值范围", 1, 100, ColorB, STATIC_10),
			FILLWINDOWDATE(Bullet::SetStaticTransparent, "刷新透明率", 0, 100, BulletTransparent, STATIC_11)
		};
		_pwd = s_wd;
	}
	return _pwd;
}

ChlidWindow* Lin::CreateChlidWindow(HWND _hwnd, bool _bool) {		//窗口子类的创建
	static ChlidWindow s_cw[CHLIDWINDOWW];
	if (_bool) {
		for (int _i = 0; _i < CHLIDWINDOWW; ++_i) {
			if (_i == 0)
				s_cw[_i].p_wd = WindowDateInit(_bool);//对子类的窗口进行初始化
			else
				s_cw[_i].p_wd = s_cw[_i - 1].p_wd + 1;
		}
		#define CONTROL_WIDTH			10		//控件之间的宽度间隔
		//Slider
		#define CONTROL_SLIDER_X		10
		#define CONTROL_SLIDER_Y		10		//跟踪条初始左上角坐标
		#define CONTROL_SLIDER_WIDTH	250		//跟踪条宽度
		#define CONTROL_SLIDER_HEIGHT	50		//跟踪条高度
		//Static
		#define CONTROL_STATIC_X		CONTROL_WIDTH + CONTROL_SLIDER_X + CONTROL_SLIDER_WIDTH		
		#define CONTROL_STATIC_Y		CONTROL_SLIDER_Y						//静态文本初始左上角坐标
		#define CONTROL_STATIC_WIDTH	150										//静态文本宽度
		#define CONTROL_STATIC_HEIGHT	CONTROL_SLIDER_HEIGHT					//静态文本高度

		RECT _SliderRc = { CONTROL_SLIDER_X, CONTROL_SLIDER_Y,
						   CONTROL_SLIDER_X + CONTROL_SLIDER_WIDTH, CONTROL_SLIDER_Y + CONTROL_SLIDER_HEIGHT };
		RECT _StaticRc = { CONTROL_STATIC_X, CONTROL_STATIC_Y,
						   CONTROL_STATIC_X + CONTROL_STATIC_WIDTH, CONTROL_STATIC_Y + CONTROL_STATIC_HEIGHT };
		for (int _i = 0; _i < CHLIDWINDOWW; ++_i) {
			//更新跟踪条的RECT数据
			if (_i != 0) {
				_SliderRc.top += CONTROL_SLIDER_HEIGHT;
				_SliderRc.bottom += CONTROL_SLIDER_HEIGHT;
			}
			//创建跟踪条
			s_cw[_i].m_SliderHwnd = CreateSlider(_hwnd, _SliderRc, const_cast<wchar_t*>(s_cw[_i].p_wd->_NameClass.c_str()),
				0, WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS | TBS_BOTH | WS_BORDER,
				s_cw[_i].p_wd->min, s_cw[_i].p_wd->max, s_cw[_i].p_wd->init);
			//添加跟踪条之间的空隙
			_SliderRc.top += CONTROL_WIDTH;
			_SliderRc.bottom += CONTROL_WIDTH;

			//更新静态文本的RECT数据
			if (_i != 0) {
				_StaticRc.top += CONTROL_STATIC_HEIGHT;
				_StaticRc.bottom += CONTROL_STATIC_HEIGHT;
			}
			//创建静态文本
			wstring _wstr(s_cw[_i].p_wd->_NameCh);
			TextByName(s_cw[_i].p_wd->init, _wstr);
			s_cw[_i].m_StaticHwnd = CreateStatic(_hwnd, _StaticRc, 
				const_cast<wchar_t*>(_wstr.c_str()),
				s_cw[_i].p_wd->_ID, WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_CENTER | SS_NOTIFY | WS_BORDER);
			//添加静态文本之间的空隙
			_StaticRc.top += CONTROL_WIDTH;
			_StaticRc.bottom += CONTROL_WIDTH;
		}
		#undef CONTROL_WIDTH
		//Slider
		#undef CONTROL_SLIDER_X
		#undef CONTROL_SLIDER_Y
		#undef CONTROL_SLIDER_WIDTH
		#undef CONTROL_SLIDER_HEIGHT
		//Static
		#undef CONTROL_STATIC_X
		#undef CONTROL_STATIC_Y
		#undef CONTROL_STATIC_WIDTH
		#undef CONTROL_STATIC_HEIGHT
	}
	return s_cw;
}

void Lin::TextByName(int _pos, wstring& _wstr) {
	_wstr = _wstr + wstring(L":") + to_wstring(_pos);
}
