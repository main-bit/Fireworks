#include "Bullet.h"

//��ʼ����ȫ�ֱ���
UINT Bullet::s_Default_Partcle_Num = 128;	//Ĭ��new��������	
double Bullet::s_Speed = 10.0f;
double Bullet::s_Transparent = 0.2f;		//Ĭ��͸����
bool Bullet::s_AutoBullet = true;



	//���ô˹��캯��	˵�����ڵ����յ���������ɵ�	Ҳ���Ƿ��û������
Bullet::Bullet(D2D1_POINT_2F _Begin, RECT& _Rc) : pBullet(NULL), pListPartcle(NULL),
													Num(Bullet::s_Default_Partcle_Num), Boom(false)
{
	InitRandEnd(_Rc);
	Init(_Begin);
}

	//���ô˹��캯��	˵�����յ�ȷ�����ڵ�	���������������	Ҳ����ͨ���û���굥��������
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
	//��������ڵ����յ�
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
	Release();	//�ͷ�ָ����Դ
}

void Bullet::Draw(ID2D1HwndRenderTarget* pRT, ID2D1SolidColorBrush* pBrush, ID2D1StrokeStyle* pStyle, RECT& _Rc) {
	if (!Boom) {
		//δ��ը
		//�Ȼ����յ㴦��Բ
		pEllipse->Draw(pRT, pBrush);
		//�����ڵ�
		pBrush->SetColor(D2D1::ColorF(pBullet->GetColor()->GetR(), 
									  pBullet->GetColor()->GetG(), 
									  pBullet->GetColor()->GetB()));		//���û�ˢ��ɫ
		pRT->DrawLine(pBullet->GetBase()->GetBegin(), pBullet->GetBase()->GetEnd(), pBrush, pBullet->GetBase()->GetWidth(), pStyle);
		UpDate();		//�����ڵ�λ��
	}
	else {
		//�ѱ�ը		//�滭����
		list<Partcle*>::iterator _iter = pListPartcle->begin();
		for (; _iter != pListPartcle->end(); ++_iter) {
			if ((*_iter)->OutDate(_iter, _Rc)) {	//���ж϶����Ƿ����
				delete *_iter;
				_iter = pListPartcle->erase(_iter);
			}
			//����ʱ_iter�Ѿ�ָ��endִ��break
			if (_iter == pListPartcle->end())	break;
			(*_iter)->Draw(pRT, pBrush, pStyle);	//����
			(*_iter)->UpDate();						//����
		}
	}
}

void Bullet::UpDate() {
	//�ж��ڵ��Ƿ񵽴��յ�
	if (!Boom) {
		pBullet->GetBase()->UpDate();		//ֻ�����Base���ֵ�����	��Ϊ���ǲ�����������Ӱ��Ķ���
		if (fabs(pBullet->GetBase()->GetEnd().x - End.x) <= fabs(pBullet->GetBase()->GetSpeedX())
			&& fabs(pBullet->GetBase()->GetEnd().y - End.y) <= fabs(pBullet->GetBase()->GetSpeedY())) {
			Boom = true;
			//��������
			PlaySound(L"Boom.WAV", NULL, SND_ASYNC);
		}
	}
}

bool Bullet::OutDate() {
	if (pListPartcle->size() == 0)	//��������Ϊ0ʱ  ˵���˶��󼴽���ʱ
		return true;
	return false;
}