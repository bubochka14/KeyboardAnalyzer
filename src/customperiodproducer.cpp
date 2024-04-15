#include "customperiodproducer.h"
CustomPeriodProducer::CustomPeriodProducer(QObject* parent)
	:QObject(parent)
{
}
bool CustomPeriodProducer::produceSound(const PeriodInfo& info)
{
	if (_sounds.contains(info))
		_sounds[info][QRandomGenerator::global()->generate() % _sounds[info].length()]->play();
	return true;
}
Config* CustomPeriodProducer::config() const
{
	return new Config();
}
void CustomPeriodProducer::setConfig(Config*)
{

}
void CustomPeriodProducer::addUniversalSound(const QList<QUrl>& list)
{
	for (int i = 0; i < list.size(); ++i)
	{
		QSoundEffect* ef = new QSoundEffect(this);
		ef->setSource(list[i]);
		_sounds[PeriodInfo::Break].append(ef);
		_sounds[PeriodInfo::Work].append(ef);
		_sounds[PeriodInfo::Final].append(ef);//���������
	}
}
void CustomPeriodProducer::setSounds(const PeriodInfo& info, const QList<QUrl>& url)
{
	for (auto& i : _sounds[info])
		i->deleteLater();
	_sounds[info].resize(url.size());
	for(int i=0; i<url.size(); ++i)
	{
		QSoundEffect* ef = new QSoundEffect(this);
		ef->setSource(url[i]);
		_sounds[info][i]=ef;
	}

}