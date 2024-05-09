#pragma once
#include <qobject.h>
#include <qqmlengine.h>
struct typingRate
{
	explicit typingRate();
	void reset();
	int wpm, cpm;
	int avgWPM, avgCPM;
	int	wordCount, charCount;
	long long time;
private:
	Q_GADGET;
	QML_ELEMENT;
	Q_PROPERTY(int wpm MEMBER wpm);
	Q_PROPERTY(int cpm MEMBER cpm);
	Q_PROPERTY(int wordCount MEMBER wordCount);
	Q_PROPERTY(int avgCpm MEMBER avgCPM);
	Q_PROPERTY(int avgWpm MEMBER avgWPM);
	Q_PROPERTY(int charCount MEMBER charCount);
	Q_PROPERTY(long long time MEMBER time);
};
using RateList = QList<typingRate>;
Q_DECLARE_METATYPE(RateList);