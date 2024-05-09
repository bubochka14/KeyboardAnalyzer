#pragma once	
#include "apppage.h"
#include "appsetting.h"
#include <qqmlengine.h>
#include "contentbuilder.h"
class SettingsPage : public AppPage
{
	Q_OBJECT;
	Q_PROPERTY(QStringList headers READ headers NOTIFY headersChanged);

public:
	explicit SettingsPage(QQmlEngine* e, QObject* parent = nullptr);
	QQuickItem* getContent() override;
	void addSetting(AbstractAppSetting* s, const QString& header);
	Q_INVOKABLE QList<AbstractAppSetting*> addedSettings(const QString& header) const;//AppPage settings() name conflict
	QStringList headers() const;
signals:
//	void addedSettingsChanged();
	void headersChanged();
private:
	QQuickItem* _content;
	QQmlEngine* _engine;
	QStringList _headers;
	QHash<QString,QList<AbstractAppSetting*>> _addedSettings;
};
