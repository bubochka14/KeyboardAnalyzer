#include "customkbproducer.h"
uint qHash(const KeyInfo& item)
{
	return qHash(item.key) + qHash(item.type);
}
inline bool operator==(const KeyInfo& i1, const KeyInfo& i2)
{
	return i1.type == i2.type;
}
KeyInfo::KeyInfo(const KeyEvent& e) : key(e.key), type(e.type) {}

CustomKBProducer::CustomKBProducer(QObject* parent)
	:QObject(parent)
	,_vol(1)
{
}
void CustomKBProducer::setConfig(Config*)
{

}
void CustomKBProducer::setVolume(double other)
{
	if (other == _vol)
		return;
	_vol = other;
	for (auto& i : _specKeys)
		i->setVolume(_vol);
	for (auto& i : _random)
		i->setVolume(_vol);
	emit volumeChanged();
}
double CustomKBProducer::volume() const
{
	return _vol;
}
bool CustomKBProducer::produceSound(const KeyEvent& e)
{
	if (_specKeys.contains(e))
		_specKeys[e]->play();
	else if(_random.length() && e.type == KeyEvent::Press && !e.isRepeating)
		_random[(QRandomGenerator::global()->generate() % _random.length())]->play();
	return true;

}
//QList<Qt::Key> CustomKBProducer::availableKeys() const
//{
//	return QList<Qt::Key>();
//}
void CustomKBProducer::setKeyEffect(const KeyInfo& e, const QUrl& url)
{
	QSoundEffect* ef = new QSoundEffect(this);
	ef->setSource(url);
	_specKeys[e] = ef;
}
void CustomKBProducer::setRandomEffects(const QList<QUrl> other)
{
	for (auto& i : _random)
		i->deleteLater();
	_random.resize(other.length());
	for (int i=0; i< _random.length();++i)
	{
		QSoundEffect* ef = new QSoundEffect(this);
		ef->setSource(other[i]);
		_random[i] = ef;
	}
}
Config* CustomKBProducer::config() const
{
	return _config;

}
