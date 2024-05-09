#include "apppage.h"
Q_LOGGING_CATEGORY(LC_AAPPAGE, "AppPage");

AppPage::AppPage(const QString& name, QObject* parent)
	:NamedObject(name,parent)
{}

QUrl AppPage::iconSource() { return _iconSource; }
void AppPage::setIconSource(const QUrl& other)
{
	if (other != _iconSource)
	{
		_iconSource = other;
		emit iconSourceChanged();
	}
}
ExecutableAppPage::ExecutableAppPage(const QString& name, QObject* parent)
	:AppPage(name,parent)
{
}
QList<AbstractAppSetting*> AppPage::settings() const
{
	return  QList<AbstractAppSetting*>();
}
