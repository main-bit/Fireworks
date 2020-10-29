#pragma once
#ifndef FIREWORKS_H
#define FIREWORKS_H
#include "Partcle.h"
#include "Bullet.h"
#include "CtrlPage.h"
#include "resource.h"
using std::list;
using Lin::CtrlPage;

#define RAND_BULLET_TIME	1	//每经过RAND_BULLET_TIME秒随机生成一个炮弹
#define TRANSPARENT			0.2	//清除透明度

class FireWorks {		//烟花
private:
	//D2D声明
	ID2D1Factory* pFactory;
	ID2D1HwndRenderTarget* pRT;
	ID2D1SolidColorBrush* pBrush;
	ID2D1StrokeStyle* pStyle;		//线条风格
private:
	//炮弹
	list<Bullet*> pBullet;
	UINT BulletNum;		//炮弹数量
	DWORD NowTime;
private:
	//窗口属性
	HWND FireWorksHwnd;
	RECT WindowRc;
	WNDCLASSEX WndClass;
	HINSTANCE* hInstance;
	int CmdShow;
private:
	//控制页
	CtrlPage* pCtrlPage;
private:
	HANDLE phWait;			//创建一个定时器
	LARGE_INTEGER liDueTime;
	DWORD dwRet;
	bool Exit;				//是否退出
private:
	//以下为初始化各种资源
	void Init();
	void InitWIN();						//窗口初始化
	void InitD2D1();					//D2D初始化
	void InitTime();					//初始化定时器
	void InitCtrlPage();				//控制窗口初始化
	void InitD2D1Factory();
	void InitD2D1HwndRenderTarget();
	void InitD2D1SolidColorBrush();
	void InitD2D1StrokeStyle();
	//以下为释放各种资源
	void Release();
	void ReleaseWIN();					//释放窗口
	void ReleaseD2D1();					//释放D2D1资源
	void ReleaseCtrlPage();				//释放控制窗口
	void ReleaseD2D1Factory();
	void ReleaseD2D1HwndRenderTarget();
	void ReleaseD2D1SolidColorBrush();
	void ReleaseD2D1StrokeStyle();
	//释放D2D1资源的模板函数
	template<typename T>
	void ReleaseD2D1Date(T _D2D1_Date);
protected:
	bool RegisterWIN();		//注册窗口
	void CreateWIN();		//创建窗口
	void UpdateWIN();		//更新窗口
	void ShowWIN();			//显示窗口
	void UnregisterWIN();	//销毁窗口
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
	static LRESULT CALLBACK WndProc(HWND _hwnd, UINT _message, WPARAM _wParam, LPARAM _lParam);	//窗口过程函数
	void Run();
	void Draw();		//绘制
	void AddBullet(D2D1_POINT_2F& _End);		//当用户点击时	添加一个炮弹
private:
	void RandUpDateBullet();		//根据时间随机生成炮弹
};

#endif 