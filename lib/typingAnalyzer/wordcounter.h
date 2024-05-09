#pragma once
#include <QObject>
#include <QQmlEngine>
#include "KeyboardInterceptor.h"
#include <QObjectBindableProperty>

class WordCounter : public QObject
{
	Q_OBJECT;
	QML_UNCREATABLE("")
public:
	enum State
	{
		NoLast,
		LastIsLetter,
		LastIsSeparator,
	};
	explicit WordCounter(QObject *parent = nullptr);
	Q_INVOKABLE virtual void clear();
	quint64 charCount() const;
	quint64 wordCount() const;
	State state() const;
public slots:
	virtual void push_text(const QString&);
	virtual void push_char(const QChar&);
signals:
	void wordCountChanged();
	void charCountChanged();
	void stateChanged();
protected:
	inline virtual bool checkSeparator(const QChar&);
	void setWordCount(quint64);
	void setCharCount(quint64);
	void setState(State);
private:
	Q_PROPERTY(quint64 wordCount READ wordCount NOTIFY wordCountChanged);
	Q_PROPERTY(quint64 charCount READ charCount NOTIFY charCountChanged);
	Q_PROPERTY(State state READ state NOTIFY stateChanged);

	State _state;
	quint64 _wordCount, _charCount;
};
