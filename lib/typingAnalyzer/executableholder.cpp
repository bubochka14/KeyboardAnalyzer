#include "executableholder.h"
void ExecutableHolder::setActiveExecutable(Executable* other, Executable::State newState)
{
	if (other == _activeExe)
		return;
	if (_activeExe->state() == Executable::Started)
		_activeExe->stop();

	_activeExe = other;
	emit activeExecutableChanged();
}
Executable* ExecutableHolder::activeExecutable() const
{
	return _activeExe;
}
ExecutableHolder* ExecutableHolder::instance()
{
	if (_pInst == nullptr)
	{
		_pInst = new ExecutableHolder;
		std::atexit([]() {delete _pInst; });
	}
	return _pInst;
}
ExecutableHolder::ExecutableHolder()
	:_activeExe(nullptr)
{

}