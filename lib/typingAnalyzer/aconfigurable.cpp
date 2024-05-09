#include "aconfigurable.h"
void Config::setValue(const QString& key, const QVariant& val)
{
	_hash[key] = val;
}
QVariant Config::value(const QString& key, const QVariant& def) const
{
	return _hash.contains(key) ? _hash[key] : def;
}
//IConfigurable::IConfigurable(/*QObject* parent*/)
//	//:QObject(parent)
//{}

//Config* AConfigurable::config() const { return _config; }
//void AConfigurable::setConfig(Config* other)
//{
//	if(other != _config)
//	{
//		_config = other;
//		emit configChanged();
//	}
//}