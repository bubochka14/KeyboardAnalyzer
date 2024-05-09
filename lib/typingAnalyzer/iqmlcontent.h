#pragma once
#include <qqmlengine.h>
#include <QObject>
#include <qquickitem.h>
class IQmlContent
{
public:

	virtual ~IQmlContent() = default;
	virtual QQuickItem* getContent() = 0;
};
