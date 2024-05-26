#include "slidersetting.h"
SliderSetting::SliderSetting(const QString& name, QObject* parent)
	:AbstractAppSetting(name, parent)
	,_min(0)
	,_max(1)
	,_content(nullptr)
	,_engine(new QQmlEngine(this))
{}
bool SliderSetting::setValue(const QVariant& other)
{
	qDebug() << other;
	if (!other.canConvert<double>() || _value == other.value<double>())
		return false;
	if(_value != other.value<double>()){
		_value = other.value<double>();
		emit valueChanged();
	}

}
QVariant SliderSetting::value() const
{
	return _value;
}
int SliderSetting::min() const
{
	return _min;
}
int SliderSetting::max() const
{
	return _max;
}
void SliderSetting::setMin(int other)
{
	if(other != _min){
		_min = other;
		_content->setProperty("from", _min);
		emit minChanged();
	}
}
void SliderSetting::setMax(int other)
{
	_max = other;
	_content->setProperty("to", _max);
	emit maxChanged();
}
QQuickItem* SliderSetting::getContent()
{
	if (!_content)
	{
		ContentBuilder builder(QUrl("qrc:/ui/UISlider.qml"), _engine);
		builder.addContextPointer("listSetting", (QObject*)this);
		_content = builder.build();
		_content->setProperty("value", _value);
		_content->setProperty("min", _min);
		_content->setProperty("max", _max);
		connect(_content, SIGNAL(valueChanged()), this, SLOT(handleValueChange()));
	}
	return _content;
}
void SliderSetting::handleValueChange()
{
	setValue(_content->property("value").toDouble());
}
