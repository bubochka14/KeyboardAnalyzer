#pragma once
//#include "configprototype.h"
//#include <qsoundeffect.h>
//#include <QMetaEnum>
//#include <qregularexpression.h>
//#include <qkeysequence.h>
//using QUrlList = QList<QUrl>;
//struct KeyInfo
//{
//	Q_GADGET;
//public:
//	enum InteractionType
//	{
//		Press,
//		Release
//	}; Q_ENUM(InteractionType);
//	Qt::Key key;
//	InteractionType type;
//};
//inline size_t qHash(const KeyInfo& info, size_t seed){ return qHashMulti(seed, info.key, info.type);}
//inline bool operator==(const KeyInfo& i1, const KeyInfo& i2)
//{
//	return i1.type == i2.type
//		&& i1.key == i2.key;
//}
//struct  PeriodInfo
//{
//	Q_GADGET;
//public:
//	enum PeriodType
//	{
//		Break,
//		Work,
//		Final,
//		Stopped
//	}; Q_ENUM(PeriodType)
//		PeriodType type;
//};
//inline size_t qHash(const PeriodInfo& info, size_t seed){ return qHashMulti(seed, info.type);}
//
//inline bool operator==(const PeriodInfo& i1, const PeriodInfo& i2) { return i1.type == i2.type;}
//
//class KeyboardSoundConfig : public ConfigPrototype
//{
//	Q_OBJECT;
//	Q_PROPERTY(QList<QUrl> randomEffects READ randomEffects WRITE setRandomEffects NOTIFY randomEffectsChanged);
//
//public:
//	explicit KeyboardSoundConfig(QObject* parent = nullptr);
//	ConfigPrototype* clone() override;
//	QUrlList randomEffects() const;
//	QUrl keyEffect(const KeyInfo&) const;
//	void setKeyEffect(const KeyInfo&, const QUrl&);
//	void setRandomEffects(const QUrlList&);
//	QVariantHash serialize() override;
//	void deserialize(const QVariantHash&) override;
//signals:
//	void randomEffectsChanged();
//private:
//	QUrlList _random;
//	QHash<KeyInfo, QUrl> _special;
//};
//class PeriodSoundConfig : public ConfigPrototype
//{
//	Q_OBJECT;
//public:
//	explicit PeriodSoundConfig(QObject* parent = nullptr);
//	ConfigPrototype* clone() override;
//	QUrlList periodEffects(const PeriodInfo& info);
//	void setPeriodEffect(const PeriodInfo& info, const QUrlList& url);
//	QVariantHash serialize() override;
//	void deserialize(const QVariantHash&) override;
//private:
//	QHash<PeriodInfo, QUrlList> _periods;
//};
