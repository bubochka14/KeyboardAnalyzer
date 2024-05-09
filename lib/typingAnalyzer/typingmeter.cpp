#include "typingmeter.h"
TypingMeter::TypingMeter(AKeyBoardInterceptor* interceptor, QObject* parent)
    :Executable(parent)
    ,_interceptor(interceptor)
    ,_wc(new WordCounter(this))
    , _updateTimer(new QTimer(this))
{
    _updateTimer->setTimerType(Qt::VeryCoarseTimer);
    setUpdatingInterval(3000);
    connect(_updateTimer, &QTimer::timeout, this, &TypingMeter::update);
    connect(_interceptor, &AKeyBoardInterceptor::keyInteracted, this, &TypingMeter::handleKeyEvent);
}

TypingMeter::TypingMeter(QObject* parent)
    :TypingMeter(new KeyboardInterceptor(parent))
{
}
quint64 TypingMeter::updatingInterval() const { return _updatingInterval; }
void TypingMeter::setUpdatingInterval(quint64 other)
{
	if (other == _updatingInterval)
		return;
	_updatingInterval = other;
	_updateTimer->setInterval(_updatingInterval);
	emit updatingIntervalChanged();
}
QList<typingRate> TypingMeter::rates() const { return _rates; }
void TypingMeter::start()
{
	if(state() != Started)
	{
		if (state() == Finished)	
		{
			_rates.clear();
			_wc->clear();
            emit ratesChanged();
		}
		_updateTimer->start();
		setState(Started);
	}
}
void TypingMeter::stop()
{
	if (state() == Started)
	{
		_updateTimer->stop();
		setState(Stopped);
	}
}
void TypingMeter::finish()
{
	if (state() != Finished)
	{
		_updateTimer->stop();
		setState(Finished);
	}
}
typingRate TypingMeter::calcRate()
{
	typingRate newRate;
	newRate.time = QDateTime::currentDateTime().toMSecsSinceEpoch();
	if(_rates.size())
	{
		newRate.wpm = (_wc->wordCount() - _rates.last().wordCount) * 60000 / _updatingInterval;
		newRate.cpm = (_wc->charCount() - _rates.last().charCount) * 60000 / _updatingInterval;
		newRate.avgCPM = _wc->charCount() * 60000 / (newRate.time - _rates.first().time);
		newRate.avgWPM = _wc->wordCount()* 60000 / (newRate.time -  _rates.first().time);
	}
	else
	{
		newRate.wpm = _wc->wordCount() * 60000 / _updatingInterval;
		newRate.cpm = _wc->charCount() * 60000 / _updatingInterval;
		newRate.avgCPM = newRate.cpm;
		newRate.avgWPM = newRate.wpm;
	}
	newRate.wordCount = (int)_wc->wordCount();
	newRate.charCount = (int)_wc->charCount();
	return newRate;
}
void TypingMeter::update()
{
	_rates.append(calcRate());
	emit ratesChanged();
}
void  TypingMeter::handleKeyEvent(const KeyEvent& e)
{
	if (state() == Started)
	{
		if (e.type != KeyEvent::Release) // counting only key release interactions
			return;
		switch (e.key)
		{
		case Qt::Key_Space:_wc->push_char(' '); break;
		case Qt::Key_Tab:_wc->push_char('\t'); break;
		case Qt::Key_Enter:_wc->push_char('\n'); break;
		default:_wc->push_char(e.text[0]); break;
		}
	}
}