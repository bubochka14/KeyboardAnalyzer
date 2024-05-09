#pragma once
#include <QObject>
#include "timefocusmodel.h"
#include "executable.h"
#include "soundinterfaces.h"
#include "typingmeter.h"
#include "executablekbproducer.h"
class TimeFocusExecutable : public Executable
{
	Q_OBJECT;
	Q_PROPERTY(quint32 decrementInterval READ decrementInterval WRITE setDecrementInterval NOTIFY decrementIntervalChanged);
	Q_PROPERTY(IPeriodSoundProducer* periodProducer READ periodProducer WRITE setPeriodProducer NOTIFY periodProducerChanged)
	Q_PROPERTY(quint16 topIndex READ topIndex  NOTIFY topIndexChanged)
public:
	explicit TimeFocusExecutable(TimeFocusModel* model,IKBSoundProducer* kbProd, 
		IPeriodSoundProducer* perProd,QObject* parent = nullptr);
	uint decrementInterval() const;
	quint32 topIndex() const;
	void setKbProd(IKBSoundProducer* other);
	void setDecrementInterval(uint other);
	void setPeriodProducer(IPeriodSoundProducer* other);
	IPeriodSoundProducer* periodProducer() const;
	void resetModel();
public slots:
	void start() override;
	void finish() override;
	void stop() override;
signals:
	void decrementIntervalChanged();
	void periodProducerChanged();
	void topIndexChanged();
protected slots:
	void decrement();
protected:
	void setTopIndex(quint16 other);
private:
	QTimer _timer;
	IPeriodSoundProducer* _periodProd;
	TypingMeter* _tMeter;
	ExecutableKBProducer* _eKbProd;
	ComplexExecutable* _eKbProdAndMeter;
	quint32 _interval;
	TimeFocusModel* _model;
	quint16 _topIndex;
};