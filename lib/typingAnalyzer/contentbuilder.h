#pragma once
#include <qobject.h>
#include <qquickitem.h>
#include <qqmlengine.h>
#include <qqmlcontext.h>
#include <qloggingcategory.h>
Q_DECLARE_LOGGING_CATEGORY(LC_CONTENT_BUILDER)
class ContentBuilder
{
public:
	explicit ContentBuilder(const QUrl& source,QQmlEngine* e);
	void addContextPointer(const QString& name, QObject* p);
	void setSource(const QUrl& url);
	void setEngine(QQmlEngine* engine);
	void setParent(QObject* parent);
	QQuickItem* build();
private:
	QQmlContext* _context;
	QQmlEngine* _engine;
	QUrl _source;
	QObject* _parent;
};