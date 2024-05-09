#pragma once
#include "namedobject.h"
#include "Applicationsettings.h"
#include "qqmlcontext.h"
#include <qqmlengine.h>
#include <qquickitem.h>
#include "executable.h"
#include "appsetting.h"
#include <qloggingcategory.h>
Q_DECLARE_LOGGING_CATEGORY(LC_AAPPAGE);

class AppPage : public NamedObject
{
	Q_OBJECT;	
	QML_ELEMENT;
	QML_UNCREATABLE("");
	Q_PROPERTY(QUrl iconSource READ iconSource WRITE setIconSource NOTIFY iconSourceChanged);
public:
	explicit AppPage(const QString& name, QObject * parent = nullptr);
	void setIconSource(const QUrl& other);

	QUrl iconSource();
	Q_INVOKABLE virtual QQuickItem* getContent() = 0;
	Q_INVOKABLE virtual QList<AbstractAppSetting*> settings() const;//Empty list
signals:
	void iconSourceChanged();
private:
	QUrl _iconSource;
};
class ExecutableAppPage : public AppPage
{
	Q_OBJECT;
	QML_ELEMENT;
	QML_UNCREATABLE("");
	Q_PROPERTY(Executable* executable READ executable NOTIFY executableChanged)
public:
	explicit ExecutableAppPage(const QString& name, QObject* parent = nullptr);
	virtual Executable* executable() const = 0;
signals:
	void executableChanged();
};
