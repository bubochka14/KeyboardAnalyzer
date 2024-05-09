#include "wordcounter.h"
WordCounter::WordCounter(QObject* parent)
	:QObject(parent)
{
	clear();
}
void WordCounter::clear()
{
	setWordCount(0);
	setCharCount(0);
	setState(NoLast);
}
quint64 WordCounter::charCount() const
{
	return _charCount;
}
quint64 WordCounter::wordCount() const
{
	return _wordCount; 
}
void WordCounter::setWordCount(quint64 other)
{
	if (other == _wordCount)
		return;
	_wordCount = other;
	emit wordCountChanged();
}
void WordCounter::setCharCount(quint64 other)   
{
	if (other == _charCount)
		return;
	_charCount = other;
	emit charCountChanged();
}
void WordCounter::push_text(const QString& str)
{
	for (auto& i : str)
		push_char(i);
}
void WordCounter::push_char(const QChar& c)
{
	setCharCount(charCount() + 1);
	switch (state())
	{
	case WordCounter::NoLast:
		setWordCount(wordCount() + 1);
	case WordCounter::LastIsLetter: 
		if (checkSeparator(c))
			if (state() == LastIsLetter)
			{
				setWordCount(wordCount()+1);
				setState(LastIsSeparator);
			}
			else
				setState(LastIsLetter);
		break;
	}
}
bool WordCounter::checkSeparator(const QChar& other)
{
	return other.isSpace() || other == '\t' || other == '\n';
}
void WordCounter::setState(State other)
{
	if (_state == other)
		return;
	_state = other;
	emit stateChanged();
}
WordCounter::State WordCounter::state() const
{
	return _state;
}