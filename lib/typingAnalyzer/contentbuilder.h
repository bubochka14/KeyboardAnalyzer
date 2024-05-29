#pragma once
#include <qobject.h>
#include <qquickitem.h>
#include <qqmlincubator.h>
#include <qfuture.h>
#include <qqmlengine.h>
#include <qqmlcontext.h>
#include <qloggingcategory.h>
Q_DECLARE_LOGGING_CATEGORY(LC_CONTENT_BUILDER)

class AContentBuilder : public QObject
{
	Q_OBJECT;
public:
	void setContentParent(QObject* parent);
	void setEngine(QQmlEngine* en);
	virtual QFuture<QQuickItem*> build(const QString& name, QQmlComponent::CompilationMode mode = QQmlComponent::PreferSynchronous) = 0;
	QQmlEngine* engine() const;
	QObject* contentParent() const;
signals:
	void statusChanged();
protected:
	explicit AContentBuilder(QQmlEngine* engine);
	virtual ~AContentBuilder() = default;
	virtual void continueLoading(QQmlComponent* comp, QPromise<QQuickItem*>&& promise);
private:
	Q_PROPERTY(QQmlComponent::Status status READ status NOTIFY statusChanged);
	QObject* _contentParent;
	QQmlEngine* _engine;
};
class SourceContentBuilder : public AContentBuilder
{
public:
	explicit SourceContentBuilder(QQmlEngine* e, const QString& prefix);
	QFuture<QQuickItem*> build(const QString& name, QQmlComponent::CompilationMode mode) override;
	void setPrefix(const QString& other);
	QString prefix() const;
private:
	QString _prefix;
};	
class ModuleContentBuilder : public AContentBuilder
{
public:
	explicit ModuleContentBuilder(QQmlEngine* e, const QString& module = "TypingAnalyzer");
	void setModule(const QString& other);
	QString module() const;
	QFuture<QQuickItem*> build(const QString& name, QQmlComponent::CompilationMode mode) override;
private:
	QString _module;

};
