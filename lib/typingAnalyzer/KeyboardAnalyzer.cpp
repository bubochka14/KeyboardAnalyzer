#include "KeyboardAnalyzer.h"
KeyboardAnalyzer::KeyboardAnalyzer(QObject *parent)
	:QObject(parent)
{
	QQmlApplicationEngine e(":/components/Main.qml");
}