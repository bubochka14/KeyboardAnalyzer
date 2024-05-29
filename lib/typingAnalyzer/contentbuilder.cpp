#include "contentbuilder.h"
Q_LOGGING_CATEGORY(LC_CONTENT_BUILDER,"Content Builder")

AContentBuilder::AContentBuilder(QQmlEngine* e)
	:_engine(e)
	,_contentParent(nullptr)
{
}
void AContentBuilder::setEngine(QQmlEngine* engine)
{
	_engine = engine;
}
void AContentBuilder::setContentParent(QObject* parent)
{
	_contentParent = parent;
}

void ModuleContentBuilder::setModule(const QString& other)
{
	_module = other;
}
QString ModuleContentBuilder::module() const
{
	return _module;
}

QFuture<QQuickItem*> ModuleContentBuilder::build(const QString& name, QQmlComponent::CompilationMode mode)
{
	QQmlComponent* comp = new QQmlComponent(engine());
	QPromise<QQuickItem*> pr;
	std::move(pr);
	QFuture<QQuickItem*> out = pr.future();
	comp->loadFromModule(module(), name);
	if (comp->isLoading()) {
		QObject::connect(comp, &QQmlComponent::statusChanged,
			this, [this,comp,pr = std::move(pr)]() mutable {
				continueLoading(comp, std::move(pr));
			});
	}
	else {
		continueLoading(comp,std::move(pr));
	}
}
void AContentBuilder::continueLoading(QQmlComponent* comp, QPromise<QQuickItem*>&& p)
{
	if (comp->isError()) {
		p.setException(std::make_exception_ptr(comp->errorString().toStdString().c_str()));
	}
	else {
		p.addResult(qobject_cast<QQuickItem*>(comp->create()));
	}
}
QString SourceContentBuilder::prefix() const
{
	return _prefix;
}
void SourceContentBuilder::setPrefix(const QString& other)
{
	_prefix = other;
}
QFuture<QQuickItem*> SourceContentBuilder::build(const QString& name, QQmlComponent::CompilationMode mode)
{
	QQmlComponent* comp = new QQmlComponent(engine(),prefix()+name+".qml");
	QPromise<QQuickItem*> pr;
	QFuture<QQuickItem*> out = pr.future();
	if (comp->isLoading()) {
		QObject::connect(comp, &QQmlComponent::statusChanged,
			this, [this, comp, pr = std::move(pr)]() mutable {
				continueLoading(comp, std::move(pr));
			});
	}
	else {
		continueLoading(comp, std::move(pr));
	}
}