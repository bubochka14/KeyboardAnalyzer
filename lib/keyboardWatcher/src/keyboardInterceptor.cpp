#include "KeyboardInterceptor.h"
#include "KeyboardInterceptor_private.h"
//KeyEvent::KeyEvent(Type t, Qt::Key k, Qt::KeyboardModifier m,
//	QString tt, bool r)
//	:key(k)
//	,type(t)
//	,modifiers(m)
//	,text(tt)
//	,isRepeating(r)
//{
//}
KeyboardInterceptor::KeyboardInterceptor(QObject* parent)
	:AKeyBoardInterceptor(parent)
	,_d_p(new KeyboardInterceptorPrivate(this))
{
}
void KeyboardInterceptor::startWatching()
{
	_d_p->_isWatching = true;
}
void KeyboardInterceptor::stopWatching()
{
	_d_p->_isWatching = false;
}
//KeyboardInterceptor* KeyboardInterceptor::instance()
//{
//#ifdef WIN32    
//	//std::atexit(destroyInterceptor);
//	KeyboardInterceptor* inst = WinKeyboardInterceptor::instance();
//#else
//#error "Keyboard interceptor doesn't support current system"
//#endif
//}
KeyboardInterceptor::~KeyboardInterceptor()
{

}