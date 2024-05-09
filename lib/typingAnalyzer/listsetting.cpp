#include "listsetting.h"
ListSetting::ListSetting(const QString& name, QObject* parent)
	:AbstractAppSetting(name,parent)
	,_engine(new QQmlEngine(this))
	,_content(nullptr)
{
}
bool ListSetting::setValue(const QVariant& other)
{
	QString key;
	if (other.canConvert<QString>())
	{
		key = other.toString();
		if (_varHash.contains(key))
		{
			_currentObjectName = key;
			emit valueChanged();
			return true;
		}
	}
	return false;

}
void ListSetting::handleTextChange()
{
	setValue(_content->property("currentText"));
}
QVariant ListSetting::value() const
{
	return _varHash.contains(_currentObjectName)?QVariant::fromValue(_varHash[_currentObjectName]):QVariant();
}
QQuickItem* ListSetting::getContent()
{
	if (!_content)
	{
		ContentBuilder builder(QUrl("qrc:/components/ui/UIComboBox.qml"), _engine);
		builder.addContextPointer("listSetting", (QObject*)this);
		_content = builder.build();
		_content->setProperty("model", _varHash.keys());
		connect(_content, SIGNAL(currentTextChanged()), this, SLOT(handleTextChange()));
	}
	return _content;
}
void ListSetting::addOption(const QString& optionName, const QVariant& var)
{
	_varHash[optionName] = var;
	if (_varHash.size() == 1)
		_currentObjectName = optionName;
}
void ListSetting::addOption(NamedObject* obj)
{
	addOption(obj->name(), QVariant::fromValue(obj));
}
