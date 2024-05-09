#include "executable.h"
Executable::Executable(QObject* parent) :QObject(parent),_state(NotStarted) {}
Executable::State Executable::state() const { return _state; }
void Executable::start() { setState(Started); }
void Executable::stop() { setState(Stopped); }
void Executable::finish() { setState(Finished); }

void Executable::setState(State other)
{
	if (other == _state)
		return;
	_state = other;
	emit stateChanged();
}
ComplexExecutable::ComplexExecutable(QObject* parent)
    :Executable(parent)
{
}
QString Executable::stateToString() const
{
   return QMetaEnum::fromType<Executable::State>().valueToKey(_state);
}
void ComplexExecutable::addComponent(Executable* other)
{
    _components.append(other);
    emit componentsChanged();
}
QList<Executable*> ComplexExecutable::components() const
{
    return _components;
}
void ComplexExecutable::start()
{
    for(auto i: _components)
    {
        i->start();
    }
}
void ComplexExecutable::stop()
{
    for(auto i: _components)
    {
        i->stop();
    }
}
void ComplexExecutable::finish()
{
    for(auto i: _components)
    {
        i->finish();
    }
}
