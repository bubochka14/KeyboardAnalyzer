#pragma once
#include <QObject>
#include <QMetaEnum>
#include <qvarianthash.h>
class Config 
{
	Q_GADGET;
public:
	Config() = default;
	virtual void setValue(const QString& key, const QVariant& val);
	virtual QVariant value(const QString& key, const QVariant& def = QVariant()) const;
private:
	QVariantHash _hash;
};
class IConfigurable
{
	//Q_OBJECT;
	//Q_PROPERTY(Config* config READ config WRITE setConfig NOTIFY configChanged)
public:
	//explicit IConfigurable(/*QObject* other = nullptr*/);
	virtual ~IConfigurable() {};
	virtual Config* config() const = 0;
	virtual void setConfig(Config*) = 0;
//signals:
//	void configChanged();
//private:
//	Config* _config;
};
Q_DECLARE_INTERFACE(IConfigurable,"Configurable interface")