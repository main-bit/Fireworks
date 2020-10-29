#include "Bullet.h"

//初始化类全局变量
UINT Bullet::s_Default_Partcle_Num = 128;	//默认new的粒子数	
double Bullet::s_Speed = 10.0f;
double Bullet::s_Transparent = 0.2f;		//默认透明率
bool Bullet::s_AutoBullet = true;



	//调用此构造函数	说明此炮弹的终点是随机生成的	也就是非用户鼠标点击
Bullet::Bullet(D2D1_POINT_2F _Begin, RECT& _Rc) : pBullet(NULL), pListPartcle(NULL),
													Num(Bullet::s_Default_Partcle_Num), Boom(false)
{
	InitRandEnd(_Rc);
	Init(_Begin);
}

	//调用此构造函数	说明是终点确定的炮弹	并不是随机而来的	也就是通过用户鼠标单击得来的
Bullet::Bullet(D2D1_POINT_2F _Begin, D2D1_POINT_2F _End) :pBullet(NULL), pListPartcle(NULL), End(_End),
															Num(Bullet::s_Default_Partcle_Num), Boom(false)
{
	Init(_Begin);
}

void Bullet::Init(const D2D1_POINT_2F& _Begin) {
	InitEllipse();
	InitBullet(_Begin);
	InitListParget();
}

void Bullet::InitEllipse() {
	pEllipse = new BoomEllipse(End, STYLE_RAND);
}

void Bullet::InitBullet(const D2D1_POINT_2F& _Begin) {
	double Long = sqrt(pow(End.x - _Begin.x, 2) + pow(End.y - _Begin.y, 2));
	double Cos = (End.x - _Begin.x) / Long;
	double Sin = (End.y - _Begin.y) / Long;
	int Accel = Base::GetStaticAccel();
	pBullet = new BoomLine(_Begin, Cos * STEPSIZE * s_Speed, Sin * STEPSIZE * s_Speed, Cos * Accel, Sin * Accel);
}

void Bullet::InitListParget() {
	pListPartcle = new list<Partcle*>;
	for (int _i = 0; _i < Num; ++_i) {
		pListPartcle->push_back(new Partcle(End, STYLE_RAND));
	}
}

void Bullet::InitRandEnd(RECT& _Rc) {
	//随机设置炮弹的终点
	End.x = Lin::Rand(_Rc.left+ 100, _Rc.right - 100);
	End.y = Lin::Rand(_Rc.top + 100, _Rc.bottom - 100);
}

void Bullet::Release() {
	ReleaseEllipse();
	ReleaseBullet();
	ReleaseListPartcle();
}

void Bullet::ReleaseListPartcle() {
	list<Partcle*>::iterator ListIteratorPartcle = pListPartcle->begin();
	for ( ; ListIteratorPartcle != pListPartcle->end(); ++ListIteratorPartcle) {
		delete *ListIteratorPartcle;
	}
}

Bullet::~Bullet() {
	Release();	//释放指针资源
}

void Bullet::Draw(ID2D1HwndRenderTarget* pRT, ID2D1SolidColorBrush* pBrush, ID2D1StrokeStyle* pStyle, RECT& _Rc) {
	if (!Boom) {
		//未爆炸
		//先绘制终点处的圆
		pEllipse->Draw(pRT, pBrush);
		//绘制炮弹
		pBrush->SetColor(D2D1::ColorF(pBullet->GetColor()->GetR(), 
									  pBullet->GetColor()->GetG(), 
									  pBullet->GetColor()->GetB()));		//设置画刷颜色
		pRT->DrawLine(pBullet->GetBase()->GetBegin(), pBullet->GetBase()->GetEnd(), pBrush, pBullet->GetBase()->GetWidth(), pStyle);
		UpDate();		//更新炮弹位置
	}
	else {
		//已爆炸		//绘画粒子
		list<Partcle*>::iterator _iter = pListPartcle->begin();
		for (; _iter != pListPartcle->end(); ++_iter) {
			if ((*_iter)->OutDate(_iter, _Rc)) {	//先判断对象是否过期
				delete *_iter;
				_iter = pListPartcle->erase(_iter);
			}
			//若此时_iter已经指向end执行break
			if (_iter == pListPartcle->end())	break;
			(*_iter)->Draw(pRT, pBrush, pStyle);	//绘制
			(*_iter)->UpDate();						//更新
		}
	}
}

void Bullet::UpDate() {
	//判断炮弹是否到达终点
	if (!Boom) {
		pBullet->GetBase()->UpDate();		//只需更新Base部分的数据	因为他是不受物理因素影响的对象
		if (fabs(pBullet->GetBase()->GetEnd().x - End.x) <= fabs(pBullet->GetBase()->GetSpeedX())
			&& fabs(pBullet->GetBase()->GetEnd().y - End.y) <= fabs(pBullet->GetBase()->GetSpeedY())) {
			Boom = true;
			//播放声音
			PlaySound(L"Boom.WAV", NULL, SND_ASYNC);
		}
	}
}

bool Bullet::OutDate() {
	if (pListPartcle->size() == 0)	//当粒子数为0时  说明此对象即将过时
		return true;
	return false;
}