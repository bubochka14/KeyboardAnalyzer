#include "freemodepage.h"
FreeModePage::FreeModePage(Application* a, QQmlEngine* e, QObject* parent)
    :ExecutableAppPage("Free Mode", parent)
    ,_app(a)
    ,_freeModeExecutable(new ComplexExecutable(this))
    ,_content(nullptr)
    ,_engine(e)
{
    AKeyBoardInterceptor* kInter = new KeyboardInterceptor(this);
    _eKbProd = new ExecutableKBProducer(a->kbProd(),kInter,this);
    _typingMeter = new TypingMeter(kInter,this);
    _freeModeExecutable->addComponent(_eKbProd);
    _freeModeExecutable->addComponent(_typingMeter);

	setIconSource(QUrl("qrc:/components/icons/chart"));
    connect(_typingMeter, &TypingMeter::ratesChanged,this, &FreeModePage::ratesChanged);
    connect(_app, &Application::kbProdChanged, this, [=]() {_eKbProd->setKBSoundProducer(_app->kbProd()); });
}
QList<typingRate> FreeModePage::rates() const {return _typingMeter->rates(); }
Executable* FreeModePage::executable() const { return _freeModeExecutable; }
QQuickItem* FreeModePage::getContent()
{
    if(_content==nullptr)
    {
        ContentBuilder builder(QUrl("qrc:/components/FreeModePage.qml"),_engine);
        builder.addContextPointer("freeModePage",(QObject*)this);
        _content = builder.build();
    }
	return _content;
}
