#pragma once
#include <qobject.h>
#include <qquickitem.h>
#include <qqmlincubator.h>
#include <qqmlengine.h>
#include <qqmlcontext.h>
#include <qloggingcategory.h>
Q_DECLARE_LOGGING_CATEGORY(LC_CONTENT_BUILDER)
class AContentBuilder : public QObject
{
	Q_OBJECT;
public:
	enum BuildStatus
	{
		notBuilt,
		Built,
		Error
	}; Q_ENUM(BuildStatus);
	BuildStatus status() const;
	explicit AContentBuilder(QQmlEngine* engine);
	void setContentParent(QObject* parent);
	void setEngine(QQmlEngine* en);
	virtual bool build() = 0;
	virtual QQuickItem* content() const;
	QQmlEngine* engine() const;
	QObject* contentParent() const;
signals:
	void statusChanged();
protected:
	void setStatus(BuildStatus other);
	virtual ~AContentBuilder() = default;
	virtual void setContent(QQuickItem* other);
private:
	Q_PROPERTY(BuildStatus status READ status NOTIFY statusChanged);

	QObject* _contentParent;
	QQmlEngine* _engine;
	QQuickItem* _content;
	BuildStatus _status;
};
class ContentBuilder : public AContentBuilder
{
public:
	explicit ContentBuilder(QQmlEngine* e, const QUrl& url);
//	void addContextPointer(const QString& name, QObject* p);
	bool build() override;
	void setSource(const QUrl& url);
private:
//	QQmlContext* _context;
	QUrl _source;
};	
class ModuleContentBuilder : public AContentBuilder
{
public:
	explicit ModuleContentBuilder(QQmlEngine* e, const QString& name, const QString& module = "TypingAnalyzer");
//	void addContextPointer(const QString& name, QObject* p);
	void setModule(const QString& other);
	QString module() const;
	QString name() const;
	void setName(const QString& name);
	bool build() override;
private:
	QString _module;
	QString _name;
//	QQmlContext _context;

};
class AsynchModuleContentBuilder: public ModuleContentBuilder, public QQmlIncubator
{
public:
	using ModuleContentBuilder::ModuleContentBuilder;
	bool build() override;
protected:
	void statusChanged(QQmlIncubator::Status status) override;
};