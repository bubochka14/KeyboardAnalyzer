#pragma once
#include <qobject.h>
#include "applicationsettings.h"
#include "executable.h"
#include "soundinterfaces.h"
class Application: public QObject
{
    Q_OBJECT;
    Q_PROPERTY(IKBSoundProducer* kbProd READ kbProd WRITE setKbProd NOTIFY kbProdChanged);

public:
    virtual Q_INVOKABLE ApplicationSettings* settings();
    virtual int exec() = 0;
    IKBSoundProducer* kbProd() const;
    void setKbProd(IKBSoundProducer* other);
signals:
    void kbProdChanged();
protected:
    Application() = default;
private:
    IKBSoundProducer* _kbProd;
    ApplicationSettings *_settings;
};
