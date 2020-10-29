#include "Base.h"

//��̬������ʼ��
int Base::s_Accel = 1;
double Base::s_Width = 4.0f;


Base::Base(const D2D1_POINT_2F& _Begin, const double _SpeedX, const double _SpeedY, const double _AccelX, const double _AccelY) :
	//�������һ��	ΪʲôAccelX, AccelyҪʹ��_X, _Y����ʼ��
	//��Ϊ�����õĲ�����#define STEPSIZE	100	Ҳ���Ǻ������������귽����ٶȲ���Ϊ(End.x - Begin.x)/STEPSIZE
	//��AccelX, AccelYΪ���귽���ϵļ��ٶ���Ҳͬ������Ϊ���ٶ�һ��	�������ǵķ�Χ��[1, 10]
	Begin(_Begin), SpeedX(_SpeedX), SpeedY(_SpeedY), AccelX(_AccelX), AccelY(_AccelY), Width(s_Width), UnitTime(0)
{
	UpDateEnd();
}

		//�������캯��ֻ��������߿���һ����	���������
Base::Base(const Base& _Base) : Begin(_Base.GetBegin()), Width(_Base.GetWidth())
{
}

void Base::UpDate() {
	Begin = End;				//�ȸ������
	if (UnitTime == UNITTIME) {
		UpDateSpeedX(AccelX);
		UpDateSpeedY(AccelY);
		InitStep();
	}
	UpDateEnd();				//�������յ�
	UpStep();
}

void Base::UpDateEnd() {
	End.x = Begin.x + FLOAT(SpeedX);
	End.y = Begin.y + FLOAT(SpeedY);
}
