#pragma once
 #include <QObject>
 #include "namedobject.h"
 #include <qqmlengine.h>
 #include "iqmlcontent.h"
class AbstractAppSetting  :public NamedObject
{
	Q_OBJECT;
	QML_ELEMENT;
	QML_UNCREATABLE("");
	Q_PROPERTY(QVariant value READ value WRITE setValue NOTIFY valueChanged);
public:
	virtual bool setValue(const QVariant& other) = 0;
	virtual QVariant value() const = 0;
	virtual Q_INVOKABLE QQuickItem* getContent()=0;

signals:
	void valueChanged();
protected:
	explicit AbstractAppSetting(const QString& name,  QObject* parent = nullptr);
};
