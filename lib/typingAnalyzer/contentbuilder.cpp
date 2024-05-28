#include "contentbuilder.h"
Q_LOGGING_CATEGORY(LC_CONTENT_BUILDER,"Content Builder")
AContentBuilder::AContentBuilder(QQmlEngine* e)
	:_engine(e)
	,_contentParent(nullptr)
	,_content(nullptr)
{
}
void AContentBuilder::setEngine(QQmlEngine* engine)
{
	_engine = engine;
}
void AContentBuilder::setStatus(BuildStatus other)
{
	if (_status == other)
		return;
	_status = other;
	emit statusChanged();
}
AContentBuilder::BuildStatus AContentBuilder::status() const
{
	return _status;
}

void AContentBuilder::setContentParent(QObject* parent)
{
	_contentParent = parent;
}
bool ContentBuilder::build()
{
	QQmlComponent comp(engine(), _source,
		QQmlComponent::PreferSynchronous);
	QObject* obj = comp.create(/*_context*/);
	obj->setParent(parent());
	if (comp.isError())
	{
		qCritical(LC_CONTENT_BUILDER) << "Error while creating content" << ": " << comp.errors();
		return false;
	}
	setContent((QQuickItem*)obj);
	return true;
}
//void ContentBuilder::addContextPointer(const QString& name, QObject* p)
//{
//	_context->setContextProperty(name, p);
//}
void ContentBuilder::setSource(const QUrl& url)
{
	engine()->setBaseUrl(url);
}
void ModuleContentBuilder::setModule(const QString& other)
{
	_module = other;
}
QString ModuleContentBuilder::module() const
{
	return _module;
}
QString ModuleContentBuilder::name() const
{
	return _name;
}
void ModuleContentBuilder::setName(const QString& name)
{
	_name = name;
}
//void ModuleContentBuilder::addContextPointer(const QString& name, QObject* p)
//{
//	_context.setContextProperty(name, p);
//}

bool ModuleContentBuilder::build()
{
	QQmlComponent comp(engine());
	comp.loadFromModule(module(), name());
	QObject* obj = comp.create(/*&_context*/);
	obj->setParent(parent());
	if (comp.isError())
	{
		qCritical(LC_CONTENT_BUILDER) << "Error while creating content" << ": " << comp.errors();
		return false;
	}
	setContent((QQuickItem*)obj);
	return true;
}
bool AsynchModuleContentBuilder::build() 
{
	QQmlComponent comp(engine());
	comp.loadFromModule(module(), name());
	comp.create(*this);
	return true;
}
void AsynchModuleContentBuilder::statusChanged(QQmlIncubator::Status status)
{
	switch (status)
	{
	case QQmlIncubator::Null:
		break;
	case QQmlIncubator::Ready:
		setContent((QQuickItem*)object());
		setStatus(Built);
		break;
	case QQmlIncubator::Loading:
		setStatus(notBuilt);
		break;
	case QQmlIncubator::Error:
		setStatus(BuildStatus::Error);
		qCritical(LC_CONTENT_BUILDER) << "Error while creating content" << ": " << errors();
		break;
	default:
		break;
	}
}