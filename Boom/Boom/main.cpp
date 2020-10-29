#include "CtrlPage.h"
#include "Fireworks.h"
using namespace Lin;

static FireWorks* s_pFireWorks = NULL;
using std::to_wstring;


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
					  _In_opt_ HINSTANCE hPrevInstance,
					  _In_ LPWSTR lpCmdLine,
					  _In_ int nCmdShow) 
{
	srand(UINT(time(0)));
	s_pFireWorks = new FireWorks(hInstance, nCmdShow);
	s_pFireWorks->Run();
	delete s_pFireWorks;

	return 0;
}

LRESULT CALLBACK CtrlPage::WndProc(HWND _hwnd, UINT _message, WPARAM _wParam, LPARAM _lParam) {
	switch (_message)
	{
	case WM_HSCROLL: {	//滑块改变位置时响应
		//在此消息中 若发送消息的是滚动条控件 则lParam是该控件的HWND
		OnUpdateChlidWindow(HWND(_lParam), s_pFireWorks->GetCtrlPage());
		}
		break;
	case WM_COMMAND:{ 	
			s_pFireWorks->GetCtrlPage()->HandleWM_COMMAND(_wParam, _lParam);
		}
		break;
	case WM_PAINT: {
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(_hwnd, &ps);
			// TODO: 在此处添加使用 hdc 的任何绘图代码...
			EndPaint(_hwnd, &ps);
			DeleteDC(hdc);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CREATE: {	//创建控件
			CreateChlidWindow(_hwnd, true);	//子类窗口的创建	true代表创建
		}
		break;
	default:
		return DefWindowProc(_hwnd, _message, _wParam, _lParam);
	}
	return 0;
}

LRESULT CALLBACK FireWorks::WndProc(HWND _hwnd, UINT _message, WPARAM _wParam, LPARAM _lParam) {
	switch (_message) {
		case WM_LBUTTONDOWN: {	//左键按下
			D2D1_POINT_2F _End = { FLOAT(LOWORD(_lParam)), FLOAT(HIWORD(_lParam)) };
			s_pFireWorks->AddBullet(_End);
		}
		 break;
		case WM_MOUSEMOVE: {		//鼠标移动
			switch (_wParam) {
				case MK_LBUTTON: {		//若鼠标左键按下
					D2D1_POINT_2F _End = { FLOAT(LOWORD(_lParam)), FLOAT(HIWORD(_lParam)) };
					s_pFireWorks->AddBullet(_End);
				}
				break;
			}
		}
		break;
		case WM_CLOSE:			//当点击了“X"按钮
			s_pFireWorks->SetExit(false);
			break;
		case WM_DESTROY:		//销毁窗口
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(_hwnd, _message, _wParam, _lParam);
	}
	return 0;
}