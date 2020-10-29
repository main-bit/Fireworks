#include "Partcle.h"
using namespace Lin;


//��ʼ����̬����
double Partcle::s_Gravity = DEFAULT_GRAVITY;
double Partcle::s_FrictionX = DEFAULT_FRICTION;
double Partcle::s_Speed = DEFAULT_SPEED;
double Partcle::s_Die = DEFAULT_DIE;					//������ʧ����

Partcle::Partcle(const D2D1_POINT_2F& _Begin, const int _ColorStyle) :pLine(NULL), Gravity(s_Gravity){
	Init(_Begin, _ColorStyle);
}

Partcle::Partcle(const Partcle& _Partcle) : pLine(NULL), Gravity(s_Gravity){
	Init(_Partcle.GetBoomLine()->GetBase()->GetBegin(), STYLE_RAND);
}

inline void Partcle::Init(const D2D1_POINT_2F& _Begin, const int _ColorStyle) {
	double _Angle = Lin::Rand(0, 360);	//��[0, 359]�����ѡȡһ��ֵ�����Ƕ�
	_Angle = PI / PAI * _Angle;			//ת���ɻ���ֵ
	double _Speed = Lin::Rand((s_Speed) * 100, (s_Speed * 2 + 1) * 100) / 100.0;
	pLine = new BoomLine(_Begin, _Speed * cos(_Angle), _Speed * sin(_Angle), 0, 0, _ColorStyle);
	InitFactionX();
}

inline void Partcle::InitFactionX() {
	FrictionX = s_FrictionX;
	if (Lin::opposite(pLine->GetBase()->GetSpeedX(), FrictionX))
		FrictionX *= -1;
}

void Partcle::Draw(ID2D1HwndRenderTarget* pRT, ID2D1SolidColorBrush* pBrush, ID2D1StrokeStyle* pStyle) {
	Color* _pColor = pLine->GetColor();
	Base* _pBase = pLine->GetBase();
	pBrush->SetColor(D2D1::ColorF(_pColor->GetR(), _pColor->GetG(), _pColor->GetB(), _pColor->GetAlpha()));
	pRT->DrawLine(_pBase->GetBegin(), _pBase->GetEnd(), pBrush, _pBase->GetWidth(), pStyle);
}

void Partcle::UpDate() {
	pLine->GetBase()->UpDateSpeedY(Gravity);
	pLine->GetBase()->UpDateSpeedX(FrictionX);
	//���ŵ���Base���ֵ�UpDate()
	pLine->GetBase()->UpDate();
	if (Lin::opposite(GetBoomLine()->GetBase()->GetSpeedX(), FrictionX)) {
		FrictionX = 0;
	}
	GetBoomLine()->GetColor()->AddAlpha(s_Die);
}

			//�ж϶����Ƿ����
bool Partcle::OutDate(list<Partcle*>::iterator& _iter, RECT& _rc) {
	//������͸����Ϊ0ʱ ����true
	if ((*_iter)->GetBoomLine()->GetColor()->GetAlpha() <= 0)
		return true;
	else if ((*_iter)->GetBoomLine()->GetBase()->GetBegin().x <= _rc.left || (*_iter)->GetBoomLine()->GetBase()->GetBegin().x >= _rc.right)
		return true;
	else if ((*_iter)->GetBoomLine()->GetBase()->GetBegin().y <= _rc.top || (*_iter)->GetBoomLine()->GetBase()->GetBegin().y >= _rc.bottom)
		return true;
	return false;
}