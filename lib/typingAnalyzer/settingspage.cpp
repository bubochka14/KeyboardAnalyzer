#include "settingspage.h"
SettingsPage::SettingsPage(QQmlEngine* e, QObject* parent)
	:AppPage("Settings",parent)
	,_engine(e)
	,_content(nullptr)
{
	setIconSource(QUrl("qrc:/components/icons/settings"));
}
QStringList SettingsPage::headers() const
{
	return _headers;
}

QQuickItem* SettingsPage::getContent()
{
	if (!_content)
	{
		ContentBuilder builder(QUrl("qrc:/components/SettingsPage.qml"), _engine);
		builder.addContextPointer("settingsPage", (QObject*)this);
		_content = builder.build();
	}
	return _content;
}
void SettingsPage::addSetting(AbstractAppSetting* s, const QString& header)
{
	if(!_addedSettings.contains(header))
	{
		_addedSettings[header].append(s);
		_headers.append(header);
		emit headersChanged();
	}else 
		_addedSettings[header].append(s);
}
QList<AbstractAppSetting*> SettingsPage::addedSettings(const QString& header) const
{
	return _addedSettings[header];
}