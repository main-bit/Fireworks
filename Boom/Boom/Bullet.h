#pragma once
#ifndef BULLET_H
#define BULLET_H
#include "Base.h"
#include "Partcle.h"
#include "Color.h"
#include "BoomLine.h"
#include "BoomEllipse.h"
#include <list>
using std::list;
#pragma comment(lib, "WINMM.lib")


	//炮弹
class Bullet{
private:
	//组合
	BoomEllipse* pEllipse;						//这是炮弹终点的圆圈
	BoomLine* pBullet;							//这是炮弹
	list<Partcle*>* pListPartcle;				//炮弹爆炸后的粒子
	/**********************************************************/
	D2D1_POINT_2F End;							//炮弹的终点
	UINT Num;									//当前对象的爆炸粒子数
	bool Boom;									//是否发生爆炸
	static UINT s_Default_Partcle_Num;			//创建对象时的粒子数
	static double s_Speed;						//炮弹速度
	static double s_Transparent;				//透明度
	static bool s_AutoBullet;					//是否自动放烟花
private:
	void Init(const D2D1_POINT_2F& _Begin);
	void InitEllipse();
	void InitBullet(const D2D1_POINT_2F& _Begin);
	void InitListParget();
	void InitRandEnd(RECT& _Rc);							//根据炮弹的数据设置终点
	Bullet& operator=(const D2D1_POINT_2F& _Bullet) {}		//禁止赋值
	Bullet(const Bullet& _Bullet) {}						//禁止调用拷贝构造函数
	void Release();
	void ReleaseEllipse() { delete pEllipse; }
	void ReleaseBullet() { delete pBullet; }
	void ReleaseListPartcle();
public:
	Bullet(D2D1_POINT_2F _Begin, RECT& _Rc);				//随机终点的粒子
	Bullet(D2D1_POINT_2F _Begin, D2D1_POINT_2F _End);		//用户使用鼠标点击后有确认终点的粒子	
	~Bullet();
public:
	void Draw(ID2D1HwndRenderTarget* pRT, ID2D1SolidColorBrush* pBrush, ID2D1StrokeStyle* pStyle, RECT& _Rc);
	void UpDate();						//更新炮弹位置
	bool OutDate();						//判断自身是否已过期
public:
	static void SetDefaultPartcleNum(double _Num) {	//修改爆炸粒子数
		Bullet::s_Default_Partcle_Num = UINT(_Num);
	}
	static void SetStaticSpeed(double _Speed) { s_Speed = _Speed; }
	void SetEnd(D2D1_POINT_2F& _End) { End = _End; }
	static void SetStaticTransparent(const double _Transparent) { s_Transparent = _Transparent / 100.f; }
	static void SetStaticAutoBullet(const bool _AutoBullet) { s_AutoBullet = _AutoBullet; }


	static const int GetDefaultPartcleNum() { return int(s_Default_Partcle_Num); }
	static const double GetStaticSpeed() { return int(s_Speed); }
	const D2D1_POINT_2F GetEnd() const { return End; }
	const int GetNum() const { return Num; }
	const bool GetBoom() const { return Boom; }
	BoomLine* GetBullet() const { return pBullet; }
	static int GetStaticTransparent() { return int(s_Transparent * 100); }
	static bool GetStaticAutoBullet() { return s_AutoBullet; }
};

#endif