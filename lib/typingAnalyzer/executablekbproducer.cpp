#include "executablekbproducer.h"
ExecutableKBProducer::ExecutableKBProducer(IKBSoundProducer* kbProd, QObject* parent)
	:ExecutableKBProducer(kbProd, new KeyboardInterceptor(parent),parent)
{}
ExecutableKBProducer::ExecutableKBProducer(IKBSoundProducer* kbProd,
	AKeyBoardInterceptor* inter, QObject* parent)
	:Executable(parent)
	,_kbInter(inter)
	,_kbProd(kbProd)
{
	connect(inter, &AKeyBoardInterceptor::keyInteracted, this, [this](const KeyEvent& e) {if (state() == Started) { _kbProd->produceSound(e); }});
}

void ExecutableKBProducer::setKBSoundProducer(IKBSoundProducer* kbProd)
{
	_kbProd = kbProd;
}
