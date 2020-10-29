#pragma once
#ifndef FIREWORKS_H
#define FIREWORKS_H
#include "Partcle.h"
#include "Bullet.h"
#include "CtrlPage.h"
#include "resource.h"
using std::list;
using Lin::CtrlPage;

#define RAND_BULLET_TIME	1	//ÿ����RAND_BULLET_TIME���������һ���ڵ�
#define TRANSPARENT			0.2	//���͸����

class FireWorks {		//�̻�
private:
	//D2D����
	ID2D1Factory* pFactory;
	ID2D1HwndRenderTarget* pRT;
	ID2D1SolidColorBrush* pBrush;
	ID2D1StrokeStyle* pStyle;		//�������
private:
	//�ڵ�
	list<Bullet*> pBullet;
	UINT BulletNum;		//�ڵ�����
	DWORD NowTime;
private:
	//��������
	HWND FireWorksHwnd;
	RECT WindowRc;
	WNDCLASSEX WndClass;
	HINSTANCE* hInstance;
	int CmdShow;
private:
	//����ҳ
	CtrlPage* pCtrlPage;
private:
	HANDLE phWait;			//����һ����ʱ��
	LARGE_INTEGER liDueTime;
	DWORD dwRet;
	bool Exit;				//�Ƿ��˳�
private:
	//����Ϊ��ʼ��������Դ
	void Init();
	void InitWIN();						//���ڳ�ʼ��
	void InitD2D1();					//D2D��ʼ��
	void InitTime();					//��ʼ����ʱ��
	void InitCtrlPage();				//���ƴ��ڳ�ʼ��
	void InitD2D1Factory();
	void InitD2D1HwndRenderTarget();
	void InitD2D1SolidColorBrush();
	void InitD2D1StrokeStyle();
	//����Ϊ�ͷŸ�����Դ
	void Release();
	void ReleaseWIN();					//�ͷŴ���
	void ReleaseD2D1();					//�ͷ�D2D1��Դ
	void ReleaseCtrlPage();				//�ͷſ��ƴ���
	void ReleaseD2D1Factory();
	void ReleaseD2D1HwndRenderTarget();
	void ReleaseD2D1SolidColorBrush();
	void ReleaseD2D1StrokeStyle();
	//�ͷ�D2D1��Դ��ģ�庯��
	template<typename T>
	void ReleaseD2D1Date(T _D2D1_Date);
protected:
	bool RegisterWIN();		//ע�ᴰ��
	void CreateWIN();		//��������
	void UpdateWIN();		//���´���
	void ShowWIN();			//��ʾ����
	void UnregisterWIN();	//���ٴ���
public:
	FireWorks(HINSTANCE _hInstance, int _CmdShow);
	~FireWorks();
public:
	void SetExit(bool _Exit) { Exit = _Exit; }


	ID2D1HwndRenderTarget* GetPRT()const { return pRT; }
	ID2D1SolidColorBrush* GetBrush()const { return pBrush; }
	ID2D1StrokeStyle* GetStyle()const { return pStyle; }
	CtrlPage* GetCtrlPage()const { return pCtrlPage; }
	RECT GetWindowRC()const { return WindowRc; }
public:
	static LRESULT CALLBACK WndProc(HWND _hwnd, UINT _message, WPARAM _wParam, LPARAM _lParam);	//���ڹ��̺���
	void Run();
	void Draw();		//����
	void AddBullet(D2D1_POINT_2F& _End);		//���û����ʱ	���һ���ڵ�
private:
	void RandUpDateBullet();		//����ʱ����������ڵ�
};

#endif 