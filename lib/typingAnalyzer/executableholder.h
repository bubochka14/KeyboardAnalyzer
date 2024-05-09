#pragma once 
#include <qobject.h>
#include "executable.h"
//holds one active executable
class ExecutableHolder : public QObject
{
	Q_OBJECT;
	Q_PROPERTY(Executable* activeExecutable READ activeExecutable WRITE setActiveExecutable NOTIFY activeExecutableChanged);
public:
	//takes a new executable to hold and changes the state of the previous one to newState
	void setActiveExecutable(Executable* other, Executable::State newState = Executable::Finished);
	Executable* activeExecutable() const;
	static ExecutableHolder* instance();
signals:
	void activeExecutableChanged();
protected:
	ExecutableHolder();
private:
	Executable* _activeExe;
	inline static ExecutableHolder* _pInst = nullptr;
};
#define executableHolder ExecutableHolder::instance()