#include "contentbuilder.h"
Q_LOGGING_CATEGORY(LC_CONTENT_BUILDER,"Content Builder")
ContentBuilder::ContentBuilder(QQmlEngine* e)
	:_context(new QQmlContext(e,e))
	,_engine(e)
{
}
void ContentBuilder::addContextPointer(const QString& name, QObject* p)
{
	_context->setContextProperty(name, p);
}
void ContentBuilder::setSource(const QUrl& url)
{
	_engine->setBaseUrl(url);
}
void ContentBuilder::setEngine(QQmlEngine* engine)
{
	_engine = engine;
}
void  ContentBuilder::setParent(QObject* parent)
{
	_parent = parent;
}
QQuickItem* ContentBuilder::build()
{
	QQmlComponent comp(_engine, _source,
		QQmlComponent::PreferSynchronous);
	QObject* obj = comp.create(_context);
	if (comp.isError())
	{
		qCritical(LC_CONTENT_BUILDER) << "Error while creating content" << ": " << comp.errors();
		return nullptr;
	}
	else
		return (QQuickItem*)obj;
}