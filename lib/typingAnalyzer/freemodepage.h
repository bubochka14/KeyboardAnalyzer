#pragma once
#include "apppage.h"
#include "application.h"
#include "typewritersp.h"
#include <qqmlcomponent.h>
#include <contentbuilder.h>
#include "keyboardinterceptor.h"
#include <qqmlcontext.h>
#include "typingmeter.h"
#include "executablekbproducer.h"
class FreeModePage : public ExecutableAppPage
{
	Q_OBJECT;
	Q_PROPERTY(QList<typingRate> rates READ rates NOTIFY ratesChanged);
public:
    explicit FreeModePage(Application* a, QQmlEngine* e, QObject* parent = nullptr);
	QList<typingRate> rates() const;
	Executable* executable() const override;
	QQuickItem* getContent() override;
signals:
	void ratesChanged();
private:
	QQuickItem* _content;
    TypingMeter* _typingMeter;
    ExecutableKBProducer* _eKbProd;
    ComplexExecutable* _freeModeExecutable; // _typingMeter and _eKbProd for a single launch
    Application* _app; //for IKBSoundProducer pointer
    QQmlEngine *_engine;
};
