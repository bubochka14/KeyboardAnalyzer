#pragma once 
#include <QObject>
#include <cstdlib>
#include "KeyboardInterceptor.h"
#include "winkeyboardinterceptor.h"
#include "AKeyBoardInterceptor.h"
class KeyboardInterceptorPrivate :public QObject
{
	Q_OBJECT;
public:
	explicit KeyboardInterceptorPrivate(KeyboardInterceptor* q)
		:_api_ptr(q)
		,QObject(q)
		//,_isWatching(false)
		,_internal(createInterceptor())
	{
        QObject::connect(_internal, &AKeyBoardInterceptor::keyInteracted, _api_ptr, &KeyboardInterceptor::keyInteracted);
	}

	KeyboardInterceptor* _api_ptr;
	bool _isWatching;
	AKeyBoardInterceptor* _internal;
	/*static void destroyInterceptor()
	{
		delete _interceptor;
		_interceptor = nullptr;
	}*/
	AKeyBoardInterceptor* getInstance()
	{
		return _internal;
	}
	[[nodiscard]] AKeyBoardInterceptor* createInterceptor()
	{
#ifdef WIN32    
		//std::atexit(destroyInterceptor);
	return  WinKeyboardInterceptor::instance();
#else
#error "Keyboard interceptor doesn't support current system"
#endif
	}
};
