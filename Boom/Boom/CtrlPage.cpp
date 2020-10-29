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
	m_WndClass.style = CS_DBLCLKS;		//˫�����ʱ�ᷢ��˫����Ϣ
	m_WndClass.lpfnWndProc = static_cast<WNDPROC>(&CtrlPage::WndProc);	//���ڹ��̺���
	m_WndClass.cbClsExtra = 0;
	m_WndClass.cbWndExtra = 0;
	m_WndClass.hInstance = _hInstance;	//����ʵ��
	m_WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);	//����ͼ��
	m_WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);	//IDC_CROSSΪʮ�ֹ��
	m_WndClass.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	m_WndClass.lpszMenuName = NULL;		//�˵�
	m_WndClass.lpszClassName = L"CtrlPage";
	m_WndClass.hIconSm = NULL;


	//ע�ᴰ��
	RegisterWIN();
	//��������
	CreateWIN();
}

CtrlPage::~CtrlPage() {
	Release();
}

bool CtrlPage::RegisterWIN() {		//ע�ᴰ��
	return RegisterClassExW(&m_WndClass);
}

void CtrlPage::InitWIN() {		//���ڳ�ʼ��
	//��ʾ����
	ShowWIN();
	//���´���
	UpdateWIN();
	//����͸��
	SetWindowLongPtr(m_CtrlHwnd, GWL_EXSTYLE, WS_EX_LAYERED);
	SetLayeredWindowAttributes(m_CtrlHwnd, 0, 200, LWA_ALPHA);

	//��д�õ�ChlidWindow����vector��
	ChlidWindow* _cw = CreateChlidWindow(this->m_CtrlHwnd, false);		//��ȡ�ڴ˷����еľ�̬����ChlidWindow��ַ
	for (int _i = 0; _i < CHLIDWINDOWW; ++_i) {
		if (_i == 0)
			_cw[_i].p_wd = WindowDateInit(true);//������Ĵ��ڽ��г�ʼ��
		else
			_cw[_i].p_wd = _cw[_i - 1].p_wd + 1;
		m_ArrChlidWindow.push_back( *(_cw+_i) );
	}
	//������ѡ��
	RECT Rc = { 10,670,110,720 };
	m_ArrButton.push_back(CreateButtom(this->m_CtrlHwnd, Rc, const_cast<wchar_t*>(L"�Զ����̻�"), BUTTON_1, BS_CHECKBOX | WS_CHILD | WS_VISIBLE | WS_TABSTOP));
	Button_SetCheck(m_ArrButton[0], BST_CHECKED);
}

void CtrlPage::Release() {
	UnregisterWIN();		//���ٴ���
}

void CtrlPage::CreateWIN() {		//��������
	m_CtrlHwnd = CreateWindow(L"CtrlPage", L"����ҳ", WS_OVERLAPPED,
		20, 60, 450, 750, NULL, NULL, *m_hInstance, NULL);
}

void CtrlPage::ShowWIN() {			//��ʾ����
	ShowWindow(m_CtrlHwnd, m_CmdShow);
}

void CtrlPage::UpdateWIN() {		//���´���
	UpdateWindow(m_CtrlHwnd);
}

void CtrlPage::UnregisterWIN() {	//���ٴ���
	UnregisterClass(L"CtrlPage", *m_hInstance);
}



void CtrlPage::OnSearchHWND(HWND _ChlidWindow, CtrlPage* _pctrlpage, vector<ChlidWindow>::iterator& _vcw) {
	_vcw = _pctrlpage->m_ArrChlidWindow.begin();
	for (; _vcw != _pctrlpage->m_ArrChlidWindow.end(); ++_vcw) {
		if (_vcw->m_SliderHwnd == _ChlidWindow) {
			//���ҵ���֮��Ӧ��_ChlidWindow��λ�� ����break
			break;
		}
	}
}

		//�����е�Slider���ര���в���_hwnd�Ӵ���
void CtrlPage::OnUpdateChlidWindow(HWND _ChlidHwnd, CtrlPage* _pctrlpage) {
	vector<ChlidWindow>::iterator _vcw;
	OnSearchHWND(_ChlidHwnd, _pctrlpage, _vcw);		//����_pcwλ�� ʹ_pcw->m_SliderHwnd == _ChlidHwnd
	if ( _vcw != _pctrlpage->m_ArrChlidWindow.end() ) {
		//���ҵ���֮��Ӧ��ֵ	�ͻ�ȡ�ø�������ǰ��ֵ
		DWORD dwPos = SendMessage(_ChlidHwnd, TBM_GETPOS, 0, 0);
		_vcw->p_wd->Set((int)dwPos);
		//���ĸ�������Ӧ�ľ�̬�ı�����
		wstring _wstr(_vcw->p_wd->_NameCh);// = wstring(_vcw->p_wd->_NameCh) + to_wstring(int(dwPos));
		TextByName(int(dwPos), _wstr);
		Static_SetText(_vcw->m_StaticHwnd, _wstr.c_str());
	}
}

void CtrlPage::AddChlidWindow(ChlidWindow& _cw) {
	m_ArrChlidWindow.push_back(_cw);
}

//�������
bool CtrlPage::HandleParam(int _IDMENU, int Pos) {
	switch (_IDMENU) {
	case 0:		//������ٶ�
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
		//��ʼ����STATIC��˫����Ϣ
		#define GETMENU(_ID)	((_ID / 100) - 1)
		int dwPos = WindowDateInit(false)[GETMENU(wmID)].init;	//��ȡ��������ǰ��λ��
		//���Ĳ���
		if (HandleParam(GETMENU(wmID), dwPos)) {	//���ĳɹ�	������һ��
			//���ø�������ǰλ��
			SendMessage(m_ArrChlidWindow[GETMENU(wmID)].m_SliderHwnd, TBM_SETPOS, true, LPARAM(dwPos));
			//�����ı�����
			wstring _wstr(m_ArrChlidWindow[GETMENU(wmID)].p_wd->_NameCh);
			TextByName(dwPos, _wstr);	//����_wstr����
			//�����ı�����
			Static_SetText(m_ArrChlidWindow[GETMENU(wmID)].m_StaticHwnd, const_cast<wchar_t*>(_wstr.c_str()));
		}
		//�������	��ȡ�����ʶ
		#undef GETMENU(_ID);
	}
	else if (wmEvent == BN_CLICKED) {
		//��ʼ����ѡ����Ϣ
		if (wmID == BUTTON_1)
			if (SendMessage(m_ArrButton[0], BM_GETCHECK, 0, 0) == BST_CHECKED) {
				//ȡ���Զ����̻�
				Bullet::SetStaticAutoBullet(false);
				Button_SetCheck(m_ArrButton[0], BST_UNCHECKED);
			}
			else {
				//�Զ����̻�
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
			FILLWINDOWDATE(Base::SetStaticAccel, "�ڵ����ٶ�", 1, 10, BaseAccel,	STATIC_1),
			FILLWINDOWDATE(Base::SetStaticWidth, "�߿�", 1, 40, BaseWidth, STATIC_2),
			FILLWINDOWDATE(Bullet::SetStaticSpeed, "�ڵ��ٶ�", 1, 30, BulletSpeed, STATIC_3),
			FILLWINDOWDATE(Bullet::SetDefaultPartcleNum, "��ը������", 0, 500, BulletNum, STATIC_4),
			FILLWINDOWDATE(Partcle::SetStaticGravity, "������������", 0, 15, PartcleGravity, STATIC_5),
			FILLWINDOWDATE(Partcle::SetStaticFrictionX, "����Ħ����", 0, 20, PartcleFaction, STATIC_6),
			FILLWINDOWDATE(Partcle::SetStaticDie, "������ʧ����", 1, 10, PartcleDie, STATIC_7),
			FILLWINDOWDATE(Color::SetStaticR, "��ɫRȡֵ��Χ", 1, 100, ColorR, STATIC_8),
			FILLWINDOWDATE(Color::SetStaticG, "��ɫGȡֵ��Χ", 1, 100, ColorG, STATIC_9),
			FILLWINDOWDATE(Color::SetStaticB, "��ɫBȡֵ��Χ", 1, 100, ColorB, STATIC_10),
			FILLWINDOWDATE(Bullet::SetStaticTransparent, "ˢ��͸����", 0, 100, BulletTransparent, STATIC_11)
		};
		_pwd = s_wd;
	}
	return _pwd;
}

ChlidWindow* Lin::CreateChlidWindow(HWND _hwnd, bool _bool) {		//��������Ĵ���
	static ChlidWindow s_cw[CHLIDWINDOWW];
	if (_bool) {
		for (int _i = 0; _i < CHLIDWINDOWW; ++_i) {
			if (_i == 0)
				s_cw[_i].p_wd = WindowDateInit(_bool);//������Ĵ��ڽ��г�ʼ��
			else
				s_cw[_i].p_wd = s_cw[_i - 1].p_wd + 1;
		}
		#define CONTROL_WIDTH			10		//�ؼ�֮��Ŀ�ȼ��
		//Slider
		#define CONTROL_SLIDER_X		10
		#define CONTROL_SLIDER_Y		10		//��������ʼ���Ͻ�����
		#define CONTROL_SLIDER_WIDTH	250		//���������
		#define CONTROL_SLIDER_HEIGHT	50		//�������߶�
		//Static
		#define CONTROL_STATIC_X		CONTROL_WIDTH + CONTROL_SLIDER_X + CONTROL_SLIDER_WIDTH		
		#define CONTROL_STATIC_Y		CONTROL_SLIDER_Y						//��̬�ı���ʼ���Ͻ�����
		#define CONTROL_STATIC_WIDTH	150										//��̬�ı����
		#define CONTROL_STATIC_HEIGHT	CONTROL_SLIDER_HEIGHT					//��̬�ı��߶�

		RECT _SliderRc = { CONTROL_SLIDER_X, CONTROL_SLIDER_Y,
						   CONTROL_SLIDER_X + CONTROL_SLIDER_WIDTH, CONTROL_SLIDER_Y + CONTROL_SLIDER_HEIGHT };
		RECT _StaticRc = { CONTROL_STATIC_X, CONTROL_STATIC_Y,
						   CONTROL_STATIC_X + CONTROL_STATIC_WIDTH, CONTROL_STATIC_Y + CONTROL_STATIC_HEIGHT };
		for (int _i = 0; _i < CHLIDWINDOWW; ++_i) {
			//���¸�������RECT����
			if (_i != 0) {
				_SliderRc.top += CONTROL_SLIDER_HEIGHT;
				_SliderRc.bottom += CONTROL_SLIDER_HEIGHT;
			}
			//����������
			s_cw[_i].m_SliderHwnd = CreateSlider(_hwnd, _SliderRc, const_cast<wchar_t*>(s_cw[_i].p_wd->_NameClass.c_str()),
				0, WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS | TBS_BOTH | WS_BORDER,
				s_cw[_i].p_wd->min, s_cw[_i].p_wd->max, s_cw[_i].p_wd->init);
			//��Ӹ�����֮��Ŀ�϶
			_SliderRc.top += CONTROL_WIDTH;
			_SliderRc.bottom += CONTROL_WIDTH;

			//���¾�̬�ı���RECT����
			if (_i != 0) {
				_StaticRc.top += CONTROL_STATIC_HEIGHT;
				_StaticRc.bottom += CONTROL_STATIC_HEIGHT;
			}
			//������̬�ı�
			wstring _wstr(s_cw[_i].p_wd->_NameCh);
			TextByName(s_cw[_i].p_wd->init, _wstr);
			s_cw[_i].m_StaticHwnd = CreateStatic(_hwnd, _StaticRc, 
				const_cast<wchar_t*>(_wstr.c_str()),
				s_cw[_i].p_wd->_ID, WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_CENTER | SS_NOTIFY | WS_BORDER);
			//��Ӿ�̬�ı�֮��Ŀ�϶
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
