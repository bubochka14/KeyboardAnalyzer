#include "soundinterfaces.h"
uint qHash(const PeriodInfo& item)
{
	return qHash(item.type);
}
bool operator==(const PeriodInfo& p1, const PeriodInfo& p2)
{
	return p1.type == p2.type;
}
PeriodInfo::PeriodInfo(PeriodType t) :type(t) {}