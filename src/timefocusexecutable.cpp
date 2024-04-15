#include "TimeFocusExecutable.h"
TimeFocusExecutable::TimeFocusExecutable(TimeFocusModel* model,IKBSoundProducer* kbProd, IPeriodSoundProducer* perProd, QObject* parent)
	:Executable(parent)
	,_interval(1000)
	,_model(model)
	,_topIndex(0)
	,_eKbProd(new ExecutableKBProducer(kbProd,this))
	,_tMeter(new TypingMeter(this))
	,_eKbProdAndMeter(new ComplexExecutable(this))
	,_periodProd(perProd)
{
	_eKbProdAndMeter->addComponent(_eKbProd);
	_eKbProdAndMeter->addComponent(_tMeter);
	connect(&_timer, &QTimer::timeout, this, &TimeFocusExecutable::decrement);
}
uint TimeFocusExecutable::decrementInterval() const { return _interval; }
void TimeFocusExecutable::setKbProd(IKBSoundProducer* other)
{
	_eKbProd->setKBSoundProducer(other);
}
void TimeFocusExecutable::setDecrementInterval(uint other)
{
	if (_interval == other)
		return;
	_interval = other;
	emit decrementIntervalChanged();
	if (state() == Started)
	{
		_timer.stop();
		_timer.start(_interval);
	}
}
void TimeFocusExecutable::setPeriodProducer(IPeriodSoundProducer* other)
{
	if (other == _periodProd)
		return;
	_periodProd = other;
	emit periodProducerChanged();
}
IPeriodSoundProducer* TimeFocusExecutable::periodProducer() const
{
	return _periodProd;
}
void TimeFocusExecutable::start()
{
	if (state() == Started)
		return;
	_timer.start(_interval);
	_eKbProdAndMeter->start();
	setState(Started);

}
void TimeFocusExecutable::stop()
{
	if (state()!= Started)
		return;
	_timer.stop();
	_eKbProdAndMeter->stop();
	setState(Stopped);

}
quint32 TimeFocusExecutable::topIndex() const
{
	return _topIndex;
}
void TimeFocusExecutable::resetModel() {
	for (size_t i = 0; i < _model->rowCount(); i++)
	{
		_model->setData(_model->index(i, 0), 0, TimeFocusModel::Completed);
		qDebug() << _model->data(_model->index(i, 0), TimeFocusModel::Duration);
		_model->setData(_model->index(i, 0), _model->data(_model->index(i,0),TimeFocusModel::Duration), TimeFocusModel::RemainingTime);
	}
}
void TimeFocusExecutable::decrement()
{
	int64_t remTime;
	do
	{
		remTime = _model->data(_model->index(_topIndex), TimeFocusModel::RemainingTime).toLongLong();
		if (remTime > 0)
			break;

	} while (_topIndex < _model->rowCount());
		
		remTime = ((remTime >= _interval) ? (remTime - _interval) : 0);
	_model->setData(_model->index(_topIndex), remTime, TimeFocusModel::RemainingTime);
	if(remTime == 0) // if current section has just closed
	{
		if (_model->data(_model->index(_topIndex), TimeFocusModel::Type) == PeriodInfo::Work)// setup rates to model
		{
			_model->setData(_model->index(_topIndex), QVariant::fromValue(_tMeter->rates()), TimeFocusModel::Rates);
			_eKbProdAndMeter->finish();
		}
		_model->setData(_model->index(_topIndex), true, TimeFocusModel::Completed);//setup completed flag to model
		++_topIndex;//move to next section
		auto newPeriod = _model->data(_model->index(_topIndex), TimeFocusModel::Type).value<PeriodInfo::PeriodType>();
		if (newPeriod == PeriodInfo::Work)
			_eKbProdAndMeter->start();
		if (_topIndex == _model->rowCount()-1)
		{
			_timer.stop();// all sections completed but not finished yet
			_periodProd->produceSound(PeriodInfo::Final);
		}else
			_periodProd->produceSound(newPeriod);
	}

}
void TimeFocusExecutable::finish()
{
	if (state() == Finished)
		return;
	_eKbProdAndMeter->finish();
	_topIndex = 0;
	_timer.stop();
	resetModel();
	setState(Finished);


}