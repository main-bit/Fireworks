#include "Fireworks.h"


FireWorks::FireWorks(HINSTANCE _hInstance, int _CmdShow) :pFactory(NULL), pRT(NULL), pBrush(NULL), pCtrlPage(NULL), Exit(true), 
								BulletNum(0), FireWorksHwnd(NULL), WindowRc({ 0 }), hInstance(&_hInstance), CmdShow(_CmdShow){
	WndClass = { 0 };
	WndClass.cbSize = sizeof(WNDCLASSEX);
	WndClass.style = CS_GLOBALCLASS;
	WndClass.lpfnWndProc = static_cast<WNDPROC>(&FireWorks::WndProc);	//���ڹ��̺���
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = _hInstance;	//����ʵ��
	WndClass.hIcon = LoadIcon(_hInstance, MAKEINTRESOURCE(IDI_ICON1));	//����ͼ��
	WndClass.hCursor = LoadCursor(NULL, IDC_CROSS);		//IDC_CROSSΪʮ�ֹ��
	WndClass.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	WndClass.lpszMenuName = NULL;		//�˵�
	WndClass.lpszClassName = L"FireWorks";
	WndClass.hIconSm = LoadIcon(_hInstance, MAKEINTRESOURCE(IDI_ICON1));


	//ע�ᴰ��
	RegisterWIN();
	//��������
	CreateWIN();

	NowTime = GetTickCount();
}

FireWorks::~FireWorks() {
	Release();
}

void FireWorks::Init() {
	InitWIN();
	InitD2D1();
	InitTime();
	InitCtrlPage();
}

void FireWorks::InitWIN() {		//���ڳ�ʼ��
	//��ʾ����
	ShowWIN();
	//���´���
	UpdateWIN();

	GetClientRect(FireWorksHwnd, &WindowRc);	//��ȡ���ڳߴ�
}

void FireWorks::InitD2D1() {	//D2D1��Դ��ʼ��
	InitD2D1Factory();
	InitD2D1HwndRenderTarget();
	InitD2D1SolidColorBrush();
	InitD2D1StrokeStyle();
}

void FireWorks::InitTime() {	//��ʱ����ʼ��
	phWait = CreateWaitableTimer(NULL, FALSE, NULL);
	liDueTime.QuadPart = -1i64;
	SetWaitableTimer(phWait, &liDueTime, 10, NULL, NULL, 0);
	dwRet = 0;
}

void FireWorks::InitCtrlPage() {
	pCtrlPage = new CtrlPage(*hInstance, CmdShow);
	pCtrlPage->InitWIN();
}



void FireWorks::InitD2D1Factory() {
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory);
}

void FireWorks::InitD2D1HwndRenderTarget() {
	pFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(
			FireWorksHwnd, D2D1::SizeU(
				WindowRc.right - WindowRc.left,
				WindowRc.bottom - WindowRc.top)),
		&pRT);
}

void FireWorks::InitD2D1SolidColorBrush() {
	pRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &pBrush);
}

void FireWorks::InitD2D1StrokeStyle() {		//���û��߷��
	pFactory->CreateStrokeStyle(D2D1::StrokeStyleProperties(
		D2D1_CAP_STYLE_ROUND,
		D2D1_CAP_STYLE_ROUND,
		D2D1_CAP_STYLE_ROUND,
		D2D1_LINE_JOIN_ROUND), 0, 0, &pStyle);
}

void FireWorks::Release() {
	ReleaseWIN();
	ReleaseD2D1();
	ReleaseCtrlPage();
}

void FireWorks::ReleaseWIN() {
	UnregisterWIN();			//���ٴ���
}

void FireWorks::ReleaseD2D1() {
	ReleaseD2D1Factory();
	ReleaseD2D1HwndRenderTarget();
	ReleaseD2D1SolidColorBrush();
	ReleaseD2D1StrokeStyle();
}

void FireWorks::ReleaseCtrlPage() {
	delete pCtrlPage;
}

void FireWorks::ReleaseD2D1Factory() {
	ReleaseD2D1Date(pFactory);
}

void FireWorks::ReleaseD2D1HwndRenderTarget() {
	ReleaseD2D1Date(pRT);
}

void FireWorks::ReleaseD2D1SolidColorBrush() {
	ReleaseD2D1Date(pBrush);
}

void FireWorks::ReleaseD2D1StrokeStyle() {
	ReleaseD2D1Date(pStyle);
}

template<typename T>
void FireWorks::ReleaseD2D1Date(T _D2D1_Date) {
	if (_D2D1_Date != NULL)
		_D2D1_Date->Release();
}

bool FireWorks::RegisterWIN() {		//ע�ᴰ��
	return RegisterClassExW(&WndClass);
}

void FireWorks::CreateWIN() {		//��������
	FireWorksHwnd = CreateWindow(L"FireWorks", L"Boom~~~!!!", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
		500, 60, 1100, 750, NULL, NULL, *hInstance, NULL);
}

void FireWorks::ShowWIN() {			//��ʾ����
	ShowWindow(FireWorksHwnd, CmdShow);
}

void FireWorks::UpdateWIN() {		//���´���
	UpdateWindow(FireWorksHwnd);
}

void FireWorks::UnregisterWIN() {	//���ٴ���
	UnregisterClass(L"CtrlPage", *hInstance);
}

void FireWorks::Run() {
	Init();					//���г�ʼ��
	while (Exit) {
		dwRet = MsgWaitForMultipleObjects(1, &phWait, FALSE, INFINITE, QS_ALLINPUT);
		switch (dwRet) {
			case WAIT_OBJECT_0: {
				//��ͼ
				pRT->BeginDraw();
				Draw();
				pRT->EndDraw();
			}
			break;
			case WAIT_OBJECT_0 + 1: {
				MSG msg;
				while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
			break;
		}
	}
}

void FireWorks::Draw() {
	if(Bullet::GetStaticAutoBullet())
		RandUpDateBullet();
	pBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Black, Bullet::GetStaticTransparent() / 100.f));
	pRT->FillRectangle(D2D1::RectF(WindowRc.left, WindowRc.top, WindowRc.right, WindowRc.bottom), pBrush);
	list<Bullet*>::iterator _iter = pBullet.begin();
	for (; _iter != pBullet.end(); ++_iter) {
		//���ж϶����Ƿ����
		if ((*_iter)->OutDate()) {
			delete *_iter;
			_iter = pBullet.erase(_iter);
		}
		if (_iter == pBullet.end())	break;
		//���ƶ���
		(*_iter)->Draw(pRT, pBrush, pStyle, WindowRc);
	}
}

void FireWorks::AddBullet(D2D1_POINT_2F& _End) {
	D2D1_POINT_2F _Begin = { (WindowRc.right - WindowRc.left) / 2, WindowRc.bottom };
	pBullet.push_back(new Bullet(_Begin, _End));
}

void FireWorks::RandUpDateBullet() {
	DWORD _Old = GetTickCount();
	if (_Old - NowTime > RAND_BULLET_TIME * 1000) {
		pBullet.push_back(new Bullet(D2D1::Point2F((WindowRc.right - WindowRc.left) / 2, WindowRc.bottom), WindowRc));
		NowTime = GetTickCount();
	}
}