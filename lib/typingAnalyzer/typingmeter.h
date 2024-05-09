#pragma once
#include "qobject.h"
#include "executable.h"
#include <QTimer>
#include "akeyboardinterceptor.h"
#include "wordcounter.h"
#include "keyboardinterceptor.h"
#include "typingrate.h"
class TypingMeter : public Executable
{
	Q_OBJECT;
	QML_ELEMENT;
	Q_PROPERTY(QList<typingRate> rates READ rates NOTIFY ratesChanged FINAL);
    Q_PROPERTY(quint64 updatingInterval READ updatingInterval WRITE setUpdatingInterval NOTIFY updatingIntervalChanged);
public:
    explicit TypingMeter(QObject* parent = nullptr);
    explicit TypingMeter(AKeyBoardInterceptor* interceptor, QObject* parent = nullptr);
    QList<typingRate> rates() const;
	quint64 updatingInterval() const;
	void setUpdatingInterval(quint64 other);

public slots:
	void start() override;
	void stop() override;
	void finish() override;
signals:
	void ratesChanged();
	void updatingIntervalChanged();
	void kbProducerChanged();
protected slots:
	virtual void handleKeyEvent(const KeyEvent&);
	virtual void update();
protected:
	virtual typingRate calcRate();
private:
	AKeyBoardInterceptor* _interceptor;
	QList<typingRate> _rates;
	quint64 _updatingInterval;
	WordCounter* _wc;
	QTimer* _updateTimer;
};
