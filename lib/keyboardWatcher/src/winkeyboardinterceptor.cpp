#include "winkeyboardinterceptor.h"
WinKeyboardInterceptor* WinKeyboardInterceptor::_pInst = nullptr;
WinKeyboardInterceptor* WinKeyboardInterceptor::instance()
{
	if (!_pInst)
	{
		_pInst = new WinKeyboardInterceptor();
		std::atexit([]() {delete _pInst; });
	}
	return _pInst;
}
typedef std::basic_string<TCHAR> tstring;
void WinKeyboardInterceptor::produceEvent(KeyEvent::InteractionType type, std::wstring text, bool isRepeating) {
	QString keyText = QString::fromStdWString(text);
	QKeySequence sq(keyText);
	KeyEvent ev = {type, sq[0].key(), keyText, isRepeating };
	emit keyInteracted(ev);
}
void WinKeyboardInterceptor::handleKey(int ccode, WPARAM wParam, LPARAM lParam)
{
	KBDLLHOOKSTRUCT* pLLHKey = (KBDLLHOOKSTRUCT*)lParam;
	DWORD VKey = pLLHKey->vkCode;
	static WCHAR name[32] = L"";
	//хранит прошлое состояние кнопки по виртуальному ключу 0 - была нажата, 1 - отпущена
	static BYTE lastKbState[256] = { 0 };
	static WCHAR Text[64] = { 0 };
	GetKeyNameText(pLLHKey->scanCode << 16, Text, 64);
	switch (wParam)
	{
	case WM_KEYDOWN:
		produceEvent(KeyEvent::Press, Text, lastKbState[VKey]);
		break;
	case WM_KEYUP:
		produceEvent(KeyEvent::Release, Text, false);
		break;
	default:
		break;
	}
	lastKbState[VKey] = !(wParam&1);
}

LRESULT CALLBACK LLKBHookProc(int code, WPARAM wParam, LPARAM lParam) {
	if (code < 0)
		return CallNextHookEx(0, code,
			wParam, lParam);
	WinKeyboardInterceptor::instance()->handleKey(code, wParam, lParam);
	return CallNextHookEx(0, code, wParam, lParam);

}
WinKeyboardInterceptor::WinKeyboardInterceptor()
{
	installHook();
}
void  WinKeyboardInterceptor::installHook()
{
	_hhk = SetWindowsHookEx(WH_KEYBOARD_LL, LLKBHookProc, NULL, NULL);
}
void  WinKeyboardInterceptor::uninstallHook()
{
	UnhookWindowsHookEx(_hhk);
}
WinKeyboardInterceptor::~WinKeyboardInterceptor()
{
	uninstallHook();
}
