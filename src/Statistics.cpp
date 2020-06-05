#include "Blackout.hpp"

void Blackout::Statistics::resetStatistics()
{
	mParagraphs = mBlackedOutWords = mWords = 0;
}

void Blackout::Statistics::add(bool blackedOut)
{
	mWords++;

	if (blackedOut) {
		mBlackedOutWords++;
	}
}

void Blackout::Statistics::addParagraph()
{
	mParagraphs++;
}
