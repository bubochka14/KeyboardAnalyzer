#include "namedobject.h"
//NamedObject::NamedObject(const QString& name, QObject* parent)
//	:QObject(parent), _name(name) {}
NamedObject::NamedObject(const QString& name,QObject * parent) : QObject(parent), _name(name) {}

QString NamedObject::name() const { return _name; }
void NamedObject::setName(const QString& other) { if (other != name()) { _name = other; emit nameChanged(); } }