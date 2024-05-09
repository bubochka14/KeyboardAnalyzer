#pragma once
#include <qobject.h>
#include <qqmlengine.h>
class NamedObject : public QObject
{
	Q_OBJECT;
	QML_ELEMENT;
	Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged);
public:
	NamedObject(const QString& name = "",QObject * parent = nullptr);
	QString name() const;
	void setName(const QString& other);
signals:
	void nameChanged();
private:
	QString _name;

};