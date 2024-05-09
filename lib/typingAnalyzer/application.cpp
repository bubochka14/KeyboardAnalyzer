#include "application.h"
ApplicationSettings* Application::settings()
{
    return _settings;
}
IKBSoundProducer* Application::kbProd() const
{
    return _kbProd;
}
void Application::setKbProd(IKBSoundProducer* other)
{
    if(other==_kbProd)
        return;
    _kbProd= other;
    emit kbProdChanged();
}
