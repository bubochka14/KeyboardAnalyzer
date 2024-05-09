#pragma once
#include "soundinterfaces.h"
#include "aconfigurable.h"
#include <QUrl>
#include <qsoundeffect.h>
#include <qrandom.h>

struct KeyInfo
{
	Q_GADGET;
public:
	enum InteractionType
	{
		Press,
		Release
	}; Q_ENUM(InteractionType);
	Qt::Key key;
	KeyEvent::InteractionType type;
	KeyInfo(const KeyEvent& e);
};
uint qHash(const KeyInfo& item);
inline bool operator==(const KeyInfo& i1, const KeyInfo& i2);
class CustomKBProducer : public QObject, IConfigurable, IKBSoundProducer
{
	Q_OBJECT;
	Q_PROPERTY(double volume READ volume WRITE setVolume NOTIFY volumeChanged);
	Q_INTERFACES(IKBSoundProducer);
	Q_INTERFACES(IConfigurable);

public:
	explicit CustomKBProducer(QObject* parent = nullptr);
	void setVolume(double other) override;
	void setConfig(Config*) override;
	double volume() const override;
	void setKeyEffect(const KeyInfo&, const QUrl&);
	Config* config() const override;
	void setRandomEffects(const QList<QUrl>);
	bool produceSound(const KeyEvent&) override;
signals:
	void volumeChanged();
//	QList<Qt::Key> availableKeys() const override;s
private:
	Config* _config;
	QHash<KeyInfo, QSoundEffect*> _specKeys;
	QVector<QSoundEffect*> _random;
	double _vol;
};