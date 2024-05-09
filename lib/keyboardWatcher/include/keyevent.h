#pragma once
#include <QString>
#include <QObject>
#include "keyboardwatcher_include.h"
//keyevent - struct for describing interaction with the keyboard; QKeyEvent is not suitable, because it cannot pass by value
class KeyInfo;
struct KW_EXPORT KeyEvent
{
	Q_GADGET;
	Q_PROPERTY(Qt::Key key MEMBER key);
	Q_PROPERTY(QString text MEMBER text);
	Q_PROPERTY(bool isRepeating MEMBER isRepeating);
public:

	enum  InteractionType
	{
		Press,
		Release
	} type; Q_ENUM(InteractionType);
	Qt::Key key;
	QString text;
	bool isRepeating;
};
