#pragma once
#include <QObject>
#include <qkeysequence.h>
#include "keyevent.h"
#include <qqmlengine.h>
#include <AKeyBoardInterceptor.h>
#include "keyboardwatcher_include.h"
class KeyboardInterceptorPrivate;
class KW_EXPORT KeyboardInterceptor : public AKeyBoardInterceptor
{
	Q_OBJECT;
	QML_ELEMENT;
public:
//	static KeyboardInterceptor* instance();
	explicit KeyboardInterceptor(QObject* parent = nullptr);

	~KeyboardInterceptor();
public slots:
	 void startWatching();
	 void stopWatching();
private:
	QScopedPointer<KeyboardInterceptorPrivate> _d_p;
};	 