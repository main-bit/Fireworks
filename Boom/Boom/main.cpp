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
	case WM_HSCROLL: {	//����ı�λ��ʱ��Ӧ
		//�ڴ���Ϣ�� ��������Ϣ���ǹ������ؼ� ��lParam�Ǹÿؼ���HWND
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
			// TODO: �ڴ˴����ʹ�� hdc ���κλ�ͼ����...
			EndPaint(_hwnd, &ps);
			DeleteDC(hdc);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CREATE: {	//�����ؼ�
			CreateChlidWindow(_hwnd, true);	//���ര�ڵĴ���	true������
		}
		break;
	default:
		return DefWindowProc(_hwnd, _message, _wParam, _lParam);
	}
	return 0;
}

LRESULT CALLBACK FireWorks::WndProc(HWND _hwnd, UINT _message, WPARAM _wParam, LPARAM _lParam) {
	switch (_message) {
		case WM_LBUTTONDOWN: {	//�������
			D2D1_POINT_2F _End = { FLOAT(LOWORD(_lParam)), FLOAT(HIWORD(_lParam)) };
			s_pFireWorks->AddBullet(_End);
		}
		 break;
		case WM_MOUSEMOVE: {		//����ƶ�
			switch (_wParam) {
				case MK_LBUTTON: {		//������������
					D2D1_POINT_2F _End = { FLOAT(LOWORD(_lParam)), FLOAT(HIWORD(_lParam)) };
					s_pFireWorks->AddBullet(_End);
				}
				break;
			}
		}
		break;
		case WM_CLOSE:			//������ˡ�X"��ť
			s_pFireWorks->SetExit(false);
			break;
		case WM_DESTROY:		//���ٴ���
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(_hwnd, _message, _wParam, _lParam);
	}
	return 0;
}