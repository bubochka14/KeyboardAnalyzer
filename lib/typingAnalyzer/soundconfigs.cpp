#include "soundconfigs.h"
//
//KeyboardSoundConfig::KeyboardSoundConfig(QObject* parent)
//	:ConfigPrototype(parent)
//{}
//
//QUrlList KeyboardSoundConfig::randomEffects() const { return _random;}
//
//void KeyboardSoundConfig::setKeyEffect(const KeyInfo& info, const QUrl& url){ _special[info] = url;}
//
//void KeyboardSoundConfig::setRandomEffects(const QUrlList& list) { _random = list; }
//
//
//ConfigPrototype* KeyboardSoundConfig::clone() 
//{
//	KeyboardSoundConfig* conf = new KeyboardSoundConfig;
//	conf->setRandomEffects(randomEffects());
//	for(auto& i : _special.keys()){
//		conf->setKeyEffect(i, _special[i]);
//	}
//	return conf;
//}
//QUrl KeyboardSoundConfig::keyEffect(const KeyInfo& info) const
//{
//	return _special.value(info);
//}
//QVariantHash KeyboardSoundConfig::serialize()
//{
//	QVariantHash out; QHash<QString, QString> specialHash; QStringList randomList;
//	for (auto& i : _random){
//		randomList.append(i.toString(QUrl::FullyEncoded));
//	}
//	QMetaEnum metaEnum = QMetaEnum::fromType<KeyInfo::InteractionType>();
//	for (auto& info : _special.keys()) {
//		QString tp = metaEnum.valueToKey(info.type);
//		specialHash[QKeySequence(info.key).toString()+tp] = _special[info].toString(QUrl::FullyEncoded);
//	}
//	out["Random"] = randomList;
//	out["Special"] = QVariant::fromValue(specialHash);
//	out["Name"] = name();
//	return out;
//}
//void KeyboardSoundConfig::deserialize(const QVariantHash& in)
//{
//	if (in.contains("Name"))
//		setName(in["Name"].toString());
//	_random = QUrlList(); _special = QHash<KeyInfo, QUrl>();
//	if (in.contains("Random"))
//		for (auto& i : in.value("Random").value<QStringList>())
//			_random.append(QUrl(i));
//	if (in.contains("Special"))
//	{
//		auto metaEnum = QMetaEnum::fromType<KeyInfo::InteractionType>();
//		QHash<QString, QString> inputHash = in.value("Special").value<QHash<QString, QString>>();
//		QRegularExpression regexp("[A-Z][^A-Z]*");
//		for (auto& key : inputHash.keys())
//		{
//			QRegularExpressionMatchIterator  match = regexp.globalMatch(key);
//			QString kbkey, type;
//			if(match.hasNext())
//				kbkey= match.next().capturedTexts()[0];
//			if(match.hasNext())
//				type = match.next().capturedTexts()[0];
//			QKeySequence sq(kbkey);
//			if (sq.count() >= 1)
//				_special.insert(KeyInfo(
//					sq[0].key(),
//					static_cast<KeyInfo::InteractionType>(metaEnum.keyToValue(type.toStdString().c_str()))),
//					inputHash[key]);
//		}
//		}
//	}
//PeriodSoundConfig::PeriodSoundConfig(QObject* parent)
//	:ConfigPrototype(parent) {}
//QUrlList PeriodSoundConfig::periodEffects(const PeriodInfo& info)
//{
//	return _periods.value(info);
//}
//void PeriodSoundConfig::setPeriodEffect(const PeriodInfo& info, const QUrlList& url)
//{
//	_periods[info] = url;
//}
//QVariantHash PeriodSoundConfig::serialize()
//{
//	return QVariantHash();
//}
//void PeriodSoundConfig::deserialize(const QVariantHash&)
//{
//	return;
//}
//ConfigPrototype* PeriodSoundConfig::clone()
//{
//	PeriodSoundConfig* conf = new PeriodSoundConfig;
//	for (auto& i : _periods.keys())
//	{
//		conf->setPeriodEffect(i, _periods[i]);
//	}
//	return conf;
//}