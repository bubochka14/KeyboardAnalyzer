#pragma once
#include <functional>
#include <qobject.h>
#include <keyevent.h>
#include <keyboardwatcher_include.h>
//Interface for platform-specific keyboard capture classes
class KW_EXPORT AKeyBoardInterceptor : public QObject
{
	Q_OBJECT
public:
	virtual ~AKeyBoardInterceptor() {}
signals:
	void keyInteracted(const KeyEvent& e);
protected:
	explicit AKeyBoardInterceptor(QObject* parent = nullptr);
};