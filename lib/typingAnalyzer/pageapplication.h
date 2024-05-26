#pragma once
#include <QObject>
#include "slidersetting.h"
#include <qapplication.h>
#include <qqmlapplicationengine.h>
#include "timefocuspage.h"
#include "qloggingcategory.h"
#include "customkbproducer.h"
#include "application.h"
#include "settingspage.h"
#include <qqmlcontext.h>
#include "qproperty.h"
#include "listsetting.h"
#include "freemodepage.h"
Q_DECLARE_LOGGING_CATEGORY(LC_PAGE_APP);	
#include "apppage.h"
class PageApplication : public Application	:
{
	Q_OBJECT;
	QML_UNCREATABLE("");
	QML_ELEMENT;
	Q_PROPERTY(QList<AppPage*> pages READ pages NOTIFY pagesChanged)
public:
    explicit PageApplication(int argc, char** argv);
    int exec() override;
	void addPage(AppPage* other);
	bool removePage(size_t index);
	QList<AppPage*> pages() const;
signals:
	void pagesChanged();
protected:
	void setupSettings();
private:
	QApplication _qApp;
	QList<AppPage*> _pages;
	QQmlApplicationEngine* _engine;
};
