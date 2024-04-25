#include "pageapplication.h"
Q_LOGGING_CATEGORY(LC_APP, "app");
PageApplication::PageApplication(int argc, char**argv)
	:_qApp(argc, argv)
	,_engine(new QQmlApplicationEngine(this))
{
	setKbProd(qobject_cast<IKBSoundProducer*>(new TypeWriterSP(this)));
    addPage(new TimeFocusPage(this, _engine,this));
    addPage(new FreeModePage(this, _engine, this));
	setupSettings();
	_qApp.setQuitOnLastWindowClosed(false);
	_engine->rootContext()->setContextProperty("app", this);
}
void PageApplication::addPage(AppPage* other)
{
	_pages.append(other);
	emit pagesChanged(); 
}
void PageApplication::setupSettings()
{

	SettingsPage* sPage = new SettingsPage(_engine, this);
	ListSetting* kbSett = new ListSetting(tr("Keyboard sounds"), this);
	kbSett->addOption(tr("Typewriter"), QVariant::fromValue((IKBSoundProducer*)new TypeWriterSP(this)));
	connect(kbSett, &AbstractAppSetting::valueChanged, this, [=]() {
		setKbProd((IKBSoundProducer*)kbSett->value().value<IKBSoundProducer*>());
		});
	sPage->addSetting(kbSett, "General");

	SliderSetting* sliderSett = new SliderSetting("Keyboard sounds volume", this);
	sliderSett->setValue(kbProd()->volume() * sliderSett->max());
	connect(sliderSett, &SliderSetting::valueChanged, this, [=]()
	{
		if (sliderSett->value().canConvert<double>())
			kbProd()->setVolume(sliderSett->value().value<double>());
	});
	sPage->addSetting(sliderSett, "General");
	for (auto& p : _pages)
	{
		for (auto& s : p->settings())
		{
			sPage->addSetting(s,p->name());
		}
	}
	addPage(sPage);
}
QList<AppPage*> PageApplication::pages() const
{
	return _pages;
}

int PageApplication::exec()
{
	//todo: qmlengine error handling 
	_engine->load(":/components/Main.qml");
	return _qApp.exec();
}
