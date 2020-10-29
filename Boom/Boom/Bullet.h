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


	//�ڵ�
class Bullet{
private:
	//���
	BoomEllipse* pEllipse;						//�����ڵ��յ��ԲȦ
	BoomLine* pBullet;							//�����ڵ�
	list<Partcle*>* pListPartcle;				//�ڵ���ը�������
	/**********************************************************/
	D2D1_POINT_2F End;							//�ڵ����յ�
	UINT Num;									//��ǰ����ı�ը������
	bool Boom;									//�Ƿ�����ը
	static UINT s_Default_Partcle_Num;			//��������ʱ��������
	static double s_Speed;						//�ڵ��ٶ�
	static double s_Transparent;				//͸����
	static bool s_AutoBullet;					//�Ƿ��Զ����̻�
private:
	void Init(const D2D1_POINT_2F& _Begin);
	void InitEllipse();
	void InitBullet(const D2D1_POINT_2F& _Begin);
	void InitListParget();
	void InitRandEnd(RECT& _Rc);							//�����ڵ������������յ�
	Bullet& operator=(const D2D1_POINT_2F& _Bullet) {}		//��ֹ��ֵ
	Bullet(const Bullet& _Bullet) {}						//��ֹ���ÿ������캯��
	void Release();
	void ReleaseEllipse() { delete pEllipse; }
	void ReleaseBullet() { delete pBullet; }
	void ReleaseListPartcle();
public:
	Bullet(D2D1_POINT_2F _Begin, RECT& _Rc);				//����յ������
	Bullet(D2D1_POINT_2F _Begin, D2D1_POINT_2F _End);		//�û�ʹ�����������ȷ���յ������	
	~Bullet();
public:
	void Draw(ID2D1HwndRenderTarget* pRT, ID2D1SolidColorBrush* pBrush, ID2D1StrokeStyle* pStyle, RECT& _Rc);
	void UpDate();						//�����ڵ�λ��
	bool OutDate();						//�ж������Ƿ��ѹ���
public:
	static void SetDefaultPartcleNum(double _Num) {	//�޸ı�ը������
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