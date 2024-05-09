#pragma once
#include <QObject>
#include <QSettings>
#include <QStandardPaths>
#include "namedobject.h"
#include "functional"
#include <QQuickItem>
// class AppSetting: public QObject
// {
// 	Q_OBJECT;
// 	Q_PROPERTY(QVariant value READ value WRITE setValue NOTIFY valueChanged);
// public:
// 	virtual QString toString() const = 0;
// 	virtual QVariant value() const = 0;
// 	virtual void setValue(const QVariant& other) =0;
// 	Q_INVOKABLE virtual QQuickItem* getContent();
// signals:
// 	void valueChanged();
// protected:
// 	explicit AppSetting(QObject* parent = nullptr);
// };
class ApplicationSettings : public QSettings
{
	Q_OBJECT;
	Q_PROPERTY(QString language READ language WRITE setLanguage NOTIFY languageChanged);
	Q_PROPERTY(QString KBSoundProducerName READ KBSoundProducerName WRITE setKBSoundProducerName NOTIFY KBSoundProducerNameChanged);
	//Q_PROPERTY(QString periodSPName READ periodSPName WRITE setPeriodSPName NOTIFY periodSPNameChanged);
public:
	// APP_NAME, ORG_NAME - CMake definitions
	explicit ApplicationSettings(const QString& appName = APP_NAME, const QString& orgName = ORG_NAME);
	QString language() const;
	QString defaultLanguage() const;
	void setLanguage(const QString& other);

	QString KBSoundProducerName() const;
	QString defaultKBSoundProducerName() const;
	void setKBSoundProducerName(const QString& other);

	QString periodSoundProducerName() const;
	QString defaultPeriodSoundProducerName() const;
	void setPeriodSoundProducerName(const QString& other);

	void addSettingsContent(const QString& name, QQuickItem* content);
	QStringList settingsNames() const;
	QQuickItem* settingsContent(const QString& name) const;

signals:
	void languageChanged();
	void KBSoundProducerNameChanged();
	void periodSoundProducerNameChanged();
private:
	QHash < QString, QQuickItem*> _settingsContent;
};
