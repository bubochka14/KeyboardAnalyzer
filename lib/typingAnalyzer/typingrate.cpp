#include "typingrate.h"
typingRate::typingRate()
{
	reset();
}
void typingRate::reset()
{
	wpm = 0; cpm = 0; avgWPM = 0; avgCPM = 0; wordCount = 0; charCount = 0;
}