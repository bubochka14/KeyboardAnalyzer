#pragma once
#include <soundinterfaces.h>
#include <QSoundEffect>
#include <QFile>
#include <qrandom.h>
#include <QDebug>
#include <qqmlengine.h>
class TypeWriterSP : public QObject, IKBSoundProducer
{
	QML_ELEMENT;
	Q_OBJECT;
	Q_INTERFACES(IKBSoundProducer);

	Q_PROPERTY(double volume READ volume WRITE setVolume NOTIFY volumeChanged);

	QVector<QSoundEffect*> _keySounds;
	QSoundEffect*          _spaceSound;
	QSoundEffect*          _enterSound;

public:
	explicit TypeWriterSP(QObject* parent= nullptr);
	double volume() const override;
	void setVolume(double other) override;
 //   QList<Qt::Key> availableKeys() const override;
public slots:
	bool produceSound(const KeyEvent&) override;
signals:
	void volumeChanged();
private:
	double _vol;
};