#pragma once
#include <QObject>
#include "apppage.h"
Q_DECLARE_LOGGING_CATEGORY(LC_PAGE_MANAGER);	

class PageManager : public QObject
{
	Q_OBJECT;
	QML_UNCREATABLE("");
	QML_ELEMENT;
	Q_PROPERTY(QList<AppPage*> pages READ pages NOTIFY pagesChanged)
public:
    explicit PageManager(QObject* parent = nullptr);
	Q_INVOKABLE void addPage(AppPage* other);
	Q_INVOKABLE bool removePage(size_t index);
	QList<AppPage*> pages() const;
signals:
	void pagesChanged();
//protected:
//	void setupSettings();
private:
	QList<AppPage*> _pages;
};
