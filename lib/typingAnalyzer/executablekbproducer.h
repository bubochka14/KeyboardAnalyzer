#pragma once
#include <qobject.h>
#include "soundinterfaces.h"
#include "akeyboardinterceptor.h"
#include "executable.h"
#include "keyboardinterceptor.h"
class ExecutableKBProducer : public Executable 
{
	Q_OBJECT;
public:
	explicit ExecutableKBProducer(IKBSoundProducer* kbProd, QObject* parent = nullptr);
	explicit ExecutableKBProducer(IKBSoundProducer* kbProd, AKeyBoardInterceptor* inter, QObject* parent = nullptr);
	void setKBSoundProducer(IKBSoundProducer* kbProd);
private:
	IKBSoundProducer* _kbProd;
	AKeyBoardInterceptor* _kbInter;
};