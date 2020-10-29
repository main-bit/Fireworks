#include "Base.h"

//静态变量初始化
int Base::s_Accel = 1;
double Base::s_Width = 4.0f;


Base::Base(const D2D1_POINT_2F& _Begin, const double _SpeedX, const double _SpeedY, const double _AccelX, const double _AccelY) :
	//这里解释一下	为什么AccelX, Accely要使用_X, _Y来初始化
	//因为我设置的步长是#define STEPSIZE	100	也就是横坐标与纵坐标方向的速度步长为(End.x - Begin.x)/STEPSIZE
	//而AccelX, AccelY为坐标方向上的加速度我也同样设置为与速度一样	所以他们的范围是[1, 10]
	Begin(_Begin), SpeedX(_SpeedX), SpeedY(_SpeedY), AccelX(_AccelX), AccelY(_AccelY), Width(s_Width), UnitTime(0)
{
	UpDateEnd();
}

		//拷贝构造函数只有起点与线宽是一样的	其他都随机
Base::Base(const Base& _Base) : Begin(_Base.GetBegin()), Width(_Base.GetWidth())
{
}

void Base::UpDate() {
	Begin = End;				//先更新起点
	if (UnitTime == UNITTIME) {
		UpDateSpeedX(AccelX);
		UpDateSpeedY(AccelY);
		InitStep();
	}
	UpDateEnd();				//最后更新终点
	UpStep();
}

void Base::UpDateEnd() {
	End.x = Begin.x + FLOAT(SpeedX);
	End.y = Begin.y + FLOAT(SpeedY);
}
